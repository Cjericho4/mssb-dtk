#!/usr/bin/env python3
"""Linear-scan dataflow over dtk asm: find every load/store/memcpy whose base derives from
a symbol (default inMemRoster) and report the in-entry offset (mod ENTRY) touched.
Usage: scan_roster.py <symbol> <entry_size_hex> <asm files...>"""
import re, sys

sym = sys.argv[1]
ENTRY = int(sys.argv[2], 16)
files = sys.argv[3:]

ins_re = re.compile(r'^/\* ([0-9A-F]+) [0-9A-F]+  [0-9A-F ]+ \*/\s+(\S+)\s*(.*)$')
mem_re = re.compile(r'^(r\d+|f\d+),\s*(-?0x[0-9a-f]+|-?\d+)\((r\d+)\)$')
memx_re = re.compile(r'^(r\d+|f\d+),\s*(r\d+),\s*(r\d+)$')

def imm(s):
    s = s.strip()
    return int(s, 16) if s.startswith(('0x', '-0x')) else int(s)

hits = []
for fn in files:
    func = None
    taint = {}   # reg -> known offset from symbol start, or None if unknown-but-tainted
    consts = {}  # reg -> small constant from li
    for line in open(fn, errors='ignore'):
        line = line.rstrip('\n')
        if line.startswith('.fn '):
            func = line.split()[1].rstrip(',')
            taint = {}
            consts = {}
            continue
        m = ins_re.match(line)
        if not m:
            continue
        addr, op, args = m.group(1), m.group(2), m.group(3).strip()
        a = [x.strip() for x in args.split(',')] if args else []
        # symbol address materialisation
        if op == 'addi' and len(a) == 3 and a[2] == sym + '@l':
            taint[a[0]] = 0
            continue
        if op == 'lis' and len(a) == 2 and a[1] == sym + '@ha':
            taint.pop(a[0], None)
            continue
        if op in ('lwz',) and len(a) == 2 and a[1].startswith(sym + '@sda21'):
            taint[a[0]] = None
            continue
        if op == 'li' and len(a) == 2:
            try: consts[a[0]] = imm(a[1])
            except ValueError: consts.pop(a[0], None)
            taint.pop(a[0], None); continue
        if op == 'mr' and len(a) == 2:
            if a[1] in taint:
                taint[a[0]] = taint[a[1]]
            else:
                taint.pop(a[0], None)
            if a[1] in consts: consts[a[0]] = consts[a[1]]
            else: consts.pop(a[0], None)
            continue
        if op in ('addi', 'subi') and len(a) == 3:
            consts.pop(a[0], None)
            if a[1] in taint:
                base = taint[a[1]]
                d = imm(a[2]) * (-1 if op == 'subi' else 1)
                if isinstance(base, tuple): taint[a[0]] = ('idx', base[1] + d)
                else: taint[a[0]] = None if base is None else base + d
            else:
                taint.pop(a[0], None)
            continue
        if op == 'add' and len(a) == 3:
            consts.pop(a[0], None)
            if a[1] in taint or a[2] in taint:
                t = taint.get(a[1], taint.get(a[2]))
                other = a[2] if a[1] in taint else a[1]
                if other in consts and t is not None and not isinstance(t, tuple):
                    taint[a[0]] = t + consts[other]
                else:
                    if isinstance(t, tuple): t = t[1]
                    taint[a[0]] = ('idx', t) if t is not None else None
            else:
                taint.pop(a[0], None)
            continue
        # memcpy / memset calls
        if op == 'bl' and a and a[0] in ('memcpy', 'memset', 'fn_800B0AA0'):
            for r in ('r3', 'r4'):
                if r in taint:
                    hits.append((fn, func, addr, a[0], r, taint[r], consts.get('r5')))
            taint = {k: v for k, v in taint.items() if k in ('r14','r15','r16','r17','r18','r19','r20','r21','r22','r23','r24','r25','r26','r27','r28','r29','r30','r31')}
            consts = {}
            continue
        if op in ('bl', 'blr', 'b', 'bctr'):
            if op == 'bl':
                for r in ('r3','r4','r5','r6','r7','r8'):
                    if r in taint:
                        hits.append((fn, func, addr, 'CALL:' + a[0], r, taint[r], None))
                taint = {k: v for k, v in taint.items() if int(k[1:]) >= 14}
                consts = {}
            continue
        mm = mem_re.match(args)
        if mm and mm.group(3) in taint:
            base = taint[mm.group(3)]
            d = imm(mm.group(2))
            if isinstance(base, tuple):
                known = base[1]
                off = (known + d) % ENTRY
                kind = 'idx'
            elif base is None:
                off = d % ENTRY; kind = '?'
            else:
                off = (base + d) % ENTRY; kind = 'abs'
            hits.append((fn, func, addr, op, mm.group(1), off, kind, d))
            if op.startswith('l') and not op.endswith('u'):
                taint.pop(mm.group(1), None); consts.pop(mm.group(1), None)
            if op.endswith('u'):
                taint[mm.group(3)] = None if base is None or isinstance(base, tuple) else base + d
            continue
        mx = memx_re.match(args)
        if mx and op.endswith('x') and (mx.group(2) in taint or mx.group(3) in taint):
            bt = taint.get(mx.group(2), taint.get(mx.group(3)))
            other = mx.group(3) if mx.group(2) in taint else mx.group(2)
            k = None if isinstance(bt, tuple) else bt
            if isinstance(bt, tuple): k = bt[1]
            if other in consts and k is not None:
                hits.append((fn, func, addr, op, mx.group(1), (k + consts[other]) % ENTRY, 'absx', consts[other]))
            else:
                hits.append((fn, func, addr, op, mx.group(1), (k % ENTRY) if k is not None else -1, 'idxx', None))
            if op.startswith('l'):
                taint.pop(mx.group(1), None); consts.pop(mx.group(1), None)
            continue
        # any other def of a register kills taint
        if a and re.match(r'^r\d+$', a[0]) and op not in ('cmpwi', 'cmplwi', 'cmpw', 'cmplw', 'stw', 'sth', 'stb', 'stfs', 'stfd', 'stwu', 'stwx', 'sthx', 'stbx', 'stmw', 'mtctr', 'mtlr'):
            taint.pop(a[0], None); consts.pop(a[0], None)

for h in hits:
    print('\t'.join(str(x) if not isinstance(x, int) else (hex(x) if x >= 0 else str(x)) for x in h))
