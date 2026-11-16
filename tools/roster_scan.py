#!/usr/bin/env python3
"""Roster-expansion scanner (phase 6, .agent/roster_expansion.md).

Lists every instruction in the game's own code (DOL game units and the three RELs, from the
dtk-split asm in build/GYQE01) that uses the character count 54 (0x36) or the last charID 53
(0x35) as a compare, loop count, sentinel or size, and writes them to a CSV with the
per-character tables the same function references as evidence.

    python3 tools/roster_scan.py                 # writes .agent/roster_expansion_sites.csv
    python3 tools/roster_scan.py --tables        # also prints data symbols sized 54 x N whose
                                                 # colour-variant rows equal their base's row
    python3 tools/roster_scan.py --derived       # also prints what each compare decides, the
                                                 # immediates derived from 54 (432, 486, 0x21C0,
                                                 # 1026, x19) and switches bounded at 47/51/53
    python3 tools/roster_scan.py --refs          # also writes .agent/roster_expansion_refs.csv:
                                                 # every instruction that forms the address of a
                                                 # per-character table, by name or anchor + offset

Needs a configured build (`python3 configure.py && ninja`) for the asm, and orig/GYQE01.
A site is a candidate, not proof: 0x36 is also an ordinary number. `evidence` lists the known
per-character symbols the function names. It is a lower bound: the compiler addresses a unit's
data from one anchor symbol plus an offset, so a function can read a table without naming it.
"""
import argparse
import collections
import csv
import glob
import re
import struct

MODULES = {
    'dol': (['build/GYQE01/asm/Unknown/*.s', 'build/GYQE01/asm/auto_*.s'], 'config/GYQE01/symbols.txt'),
    'game': (['build/GYQE01/game/asm/**/*.s'], 'config/GYQE01/game/symbols.txt'),
    'menus': (['build/GYQE01/menus/asm/**/*.s'], 'config/GYQE01/menus/symbols.txt'),
    'challenge': (['build/GYQE01/challenge/asm/**/*.s'], 'config/GYQE01/challenge/symbols.txt'),
}

# Symbols that hold per-character (charID-indexed) data or the roster built from it.
CHAR_TABLES = {
    'lbl_800EFBE8',  # .data anchor of gap_8001E460: its readers reach the descriptor tables by offset
    'charSizeMultipliers', 'lbl_800E8558', 'lbl_800EEAAC', 'lbl_800EEB18', 'lbl_800EFD38',
    'lbl_800F1D78', 'lbl_800F5D98', 'lbl_800F73B8', 'lbl_800F743C', 'lbl_80108EDC',
    'lbl_80108DB8', 'lbl_80108DDC', 'lbl_800FDE84', 'lbl_800E869C', 'lbl_80108DF4',
    'lbl_8034E9A0', 'lbl_803C6724', 'starMissionCompletionTracker',
    'lbl_800FC494',
    'lbl_3_data_37AC', 'lbl_3_data_3B4C', 'BatterHitbox', 'lbl_3_data_7690', 'lbl_3_data_7870',
    'lbl_3_data_79B4', 'lbl_3_data_7E34', 'lbl_3_data_7F10', 'lbl_3_data_8168',
    'lbl_3_data_111C8', 'lbl_3_data_17000', 'lbl_3_data_285A8', 'lbl_1_data_FC0',
    'lbl_1_data_A978', 'lbl_2_data_241C',
} | {'lbl_%08X' % a for a in range(0x800FB798, 0x800FBD81, 0x6C)}

SYM_RE = re.compile(r'^(\S+) = (\.?\w+):0x([0-9A-Fa-f]+); // (.*)$')
INSN_RE = re.compile(r'^/\* (\w+) \w+\s+(?:\w\w ){3}\w\w \*/\t(\S+)\s*(.*)$')
IDENT_RE = re.compile(r'[A-Za-z_][\w$]*')
BOUND_RE = re.compile(r', 0x3[56]$')
BOUND_OPS = ('cmpwi', 'cmplwi', 'li', 'subfic')
# Numbers derived from 54 that the code may use as immediates (candidates; they are common values).
DERIVED_OPS = ('li', 'addi', 'cmpwi', 'cmplwi', 'subfic')
DERIVED_IMMS = {'0x1b0': '432 (master tier: track-15 bank base)', '0x1e6': '486 (master tier: script base)',
                '0x21c0': '0x21C0 (54 stats rows)', '0x402': '1026 (54 x 19 subfiles)'}

# Colour families: a variant's row equals its base's row in most per-character gameplay tables.
FAMILIES = [[13, 29, 30, 31, 32], [21, 22, 23], [24, 25, 26], [33, 34, 35, 36], [48, 49, 50, 51],
            [16, 44, 45, 46, 47], [12, 42], [20, 43], [27, 52, 53]]


def load_symbols():
    syms = {}
    for mod, (_, path) in MODULES.items():
        for line in open(path):
            m = SYM_RE.match(line)
            if not m:
                continue
            attrs = dict(x.split(':', 1) for x in m.group(4).split() if ':' in x)
            syms[(mod, m.group(1))] = (m.group(2), int(m.group(3), 16),
                                       int(attrs.get('size', '0'), 16), attrs.get('type', ''))
    return syms


def scan_sites():
    sites = {}                                   # (mod, addr) -> [fn, text, kind]
    derived = collections.defaultdict(set)       # label -> {(mod, fn, addr)}
    evidence = collections.defaultdict(set)      # (mod, fn) -> char tables referenced
    for mod, (patterns, _) in MODULES.items():
        for pattern in patterns:
            for path in glob.glob(pattern, recursive=True):
                fn = pending = None
                switch = []                      # [instructions left, bound] after a cmplwi 47/51/53
                for line in open(path, errors='replace'):
                    if line.startswith('.fn '):
                        fn, pending, switch = line.split()[1].rstrip(','), None, []
                    elif line.startswith('.endfn'):
                        fn = None
                    elif fn:
                        m = INSN_RE.match(line)
                        if not m:
                            continue
                        addr, op, args = m.groups()
                        imm = args.rsplit(', ', 1)[-1]
                        # what the compare decides: the first conditional branch after it
                        if pending and op.rstrip('+-')[:3] in ('beq', 'bne', 'blt', 'bge', 'ble', 'bgt'):
                            sites[pending][2] = 'equals' if op[:3] in ('beq', 'bne') else 'range'
                            pending = None
                        elif op.startswith('cmp'):
                            pending = None
                        if op in BOUND_OPS and BOUND_RE.search(args):
                            kind = {'li': 'load', 'subfic': 'count'}.get(op, 'compare')
                            sites[(mod, addr)] = [fn, op + ' ' + args, kind]
                            if kind == 'compare':
                                pending = (mod, addr)
                        if op in DERIVED_OPS and imm in DERIVED_IMMS:
                            derived[DERIVED_IMMS[imm]].add((mod, fn, addr))
                        if op == 'mulli' and imm == '0x13':
                            derived['mulli 19 (tracks per character)'].add((mod, fn, addr))
                        if switch and 'jumptable' in args:
                            name = re.search(r'jumptable\w+', args).group(0)
                            derived['switch up to %d: %s' % (int(switch[1], 16), name)].add((mod, fn, addr))
                            switch = []
                        if switch:
                            switch[0] -= 1
                            if not switch[0]:
                                switch = []
                        if op == 'cmplwi' and imm in ('0x2f', '0x33', '0x35'):
                            switch = [8, imm]
                        evidence[(mod, fn)].update(CHAR_TABLES.intersection(IDENT_RE.findall(args)))
    return sites, evidence, derived


# Per-character tables as (module, section, start, size, name). REL starts are section offsets.
TABLES = [
    ('dol', 'dol', 0x800E8300, 54 * 8, 'charSizeMultipliers'),
    ('dol', 'dol', 0x800E8558, 54 * 6, 'lbl_800E8558'),
    ('dol', 'dol', 0x800EEAAC, 108, 'lbl_800EEAAC'),
    ('dol', 'dol', 0x800EEB18, 108, 'lbl_800EEB18'),
    ('dol', 'dol', 0x800EFD38, 516 * 16, 'lbl_800EFD38 (master)'),
    ('dol', 'dol', 0x800F1D78, 54 * 19 * 16, 'lbl_800F1D78'),
    ('dol', 'dol', 0x800F5D98, 54 * 6 * 16, 'lbl_800F5D98'),
    ('dol', 'dol', 0x800F73B8, 108, 'lbl_800F73B8'),
    ('dol', 'dol', 0x800F743C, 54, 'lbl_800F743C'),
    ('dol', 'dol', 0x8034E9A0, 0x4C28, 'lbl_8034E9A0 (stats block)'),
    ('dol', 'dol', 0x800FC494, 54 * 12, 'lbl_800FC494'),
    ('game', '.data', 0x37AC, 216, 'game 0x37AC'),
    ('game', '.data', 0x3B4C, 216, 'game 0x3B4C'),
    ('game', '.data', 0x6EF8, 54 * 36, 'game 0x6EF8 BatterHitbox'),
    ('game', '.data', 0x7690, 108, 'game 0x7690'),
    ('game', '.data', 0x7870, 54 * 6, 'game 0x7870'),
    ('game', '.data', 0x79B4, 54 * 16, 'game 0x79B4'),
    ('game', '.data', 0x7E34, 216, 'game 0x7E34'),
    ('game', '.data', 0x7F10, 108, 'game 0x7F10'),
    ('game', '.data', 0x8148, 32, 'game 0x8148 (u8[32])'),
    ('game', '.data', 0x8168, 108, 'game 0x8168'),
    ('game', '.data', 0x111C8, 54 * 8, 'game 0x111C8'),
    ('game', '.data', 0x17000, 216, 'game 0x17000'),
    ('game', '.data', 0x285A8, 216, 'game 0x285A8'),
    ('challenge', '.data', 0xFC0, 32, 'challenge 0xFC0 (u8[32])'),
    ('challenge', '.data', 0xFE0, 108, 'challenge 0xFE0'),
    ('challenge', '.data', 0xA978, 108, 'challenge 0xA978'),
    ('menus', '.data', 0x241C, 54 * 16, 'menus 0x241C'),
    ('menus', '.data', 0x2FA60, 54 * 16, 'menus 0x2FA60'),
] + [('dol', 'dol', a, 108, 'lbl_%08X (window)' % a) for a in range(0x800FB798, 0x800FBD81, 0x6C)]

REG_RE = re.compile(r'^r(\d+)$')
MEM_RE = re.compile(r'^(-?(?:0x)?[0-9a-fA-F]+|[\w$]+@l)\((r\d+)\)$')
RELOC_RE = re.compile(r'^([A-Za-z_][\w$]*)(?:([+-])(0x[0-9a-fA-F]+|\d+))?@(ha|l)$')
NO_DEST = ('st', 'cmp', 'b', 'mt', 'tw', 'dcb', 'icb', 'sync', 'isync', 'nop', '.')


def scan_refs(syms):
    """Linear register tracking per function: which instructions form an address inside a table.

    Tracks `lis`/`addi`/`addis`/`mr` chains from a symbol and reports every instruction whose
    address operand (or result) lands inside a TABLES entry. Control flow is ignored (state runs
    straight through labels) and calls clear r0, r3-r12, so a site can be missed or, rarely,
    attributed wrongly; indexed forms (`lbzx`, `add`) are reported at the instruction that uses
    the tracked base.
    """
    def resolve(mod, name):
        for m in (mod, 'dol'):
            if (m, name) in syms:
                sect, addr, _, kind = syms[(m, name)]
                if kind != 'function':
                    return (m, 'dol' if m == 'dol' else sect, addr)
        return None

    def table_at(val):
        if val is None:
            return None
        for mod, sect, start, size, name in TABLES:
            if (val[0], val[1]) == (mod, sect) and start <= val[2] < start + size:
                return name, val[2] - start
        return None

    def imm(text):
        try:
            return int(text, 0)
        except ValueError:
            return None

    rows = {}
    for mod, (patterns, _) in MODULES.items():
        for pattern in patterns:
            for path in glob.glob(pattern, recursive=True):
                fn, regs = None, {}
                for line in open(path, errors='replace'):
                    if line.startswith('.fn '):
                        fn, regs = line.split()[1].rstrip(','), {}
                        continue
                    if line.startswith('.endfn'):
                        fn = None
                        continue
                    m = INSN_RE.match(line) if fn else None
                    if not m:
                        continue
                    addr, op, args = m.groups()
                    ops = [a.strip() for a in args.split(',')] if args else []
                    hit = None          # (value, how)
                    new = None          # value for the destination register
                    if op == 'lis' and len(ops) == 2:
                        r = RELOC_RE.match(ops[1])
                        if r and r.group(4) == 'ha':
                            new = ('ha', r.group(1))
                    elif op in ('addi', 'subi', 'addic', 'addic.', 'addis', 'subis') and len(ops) == 3:
                        src = regs.get(ops[1])
                        r = RELOC_RE.match(ops[2])
                        if r and r.group(4) == 'l' and src == ('ha', r.group(1)):
                            base = resolve(mod, r.group(1))
                            if base:
                                off = int(r.group(3), 0) * (-1 if r.group(2) == '-' else 1) if r.group(2) else 0
                                new = (base[0], base[1], base[2] + off, r.group(1))
                                hit = (new, 'named')
                        elif src and src[0] != 'ha' and imm(ops[2]) is not None:
                            k = imm(ops[2]) * (0x10000 if 'is' in op else 1) * (-1 if op.startswith('sub') else 1)
                            new = (src[0], src[1], src[2] + k, src[3])
                            hit = (new, 'anchor+offset')
                    elif op in ('mr', 'mr.') and len(ops) == 2:
                        new = regs.get(ops[1])
                    else:
                        for a in ops[1:]:
                            mm = MEM_RE.match(a)
                            if mm:
                                src = regs.get(mm.group(2))
                                r = RELOC_RE.match(mm.group(1))
                                if r and src == ('ha', r.group(1)):
                                    base = resolve(mod, r.group(1))
                                    if base:
                                        hit = (base + (r.group(1),), 'named')
                                elif src and src[0] != 'ha' and imm(mm.group(1)) is not None:
                                    hit = ((src[0], src[1], src[2] + imm(mm.group(1)), src[3]), 'anchor+offset')
                            elif REG_RE.match(a) and regs.get(a) and regs[a][0] != 'ha' and op != 'mr':
                                if table_at(regs[a]):
                                    hit = (regs[a], 'indexed')
                    if hit and table_at(hit[0]):
                        name, off = table_at(hit[0])
                        rows[(mod, addr)] = (fn, op + ' ' + args, name, off, hit[1], hit[0][3])
                    if op == 'bl':
                        for r in ['r0'] + ['r%d' % i for i in range(3, 13)]:
                            regs.pop(r, None)
                    elif ops and REG_RE.match(ops[0]) and not op.startswith(NO_DEST):
                        if new is not None:
                            regs[ops[0]] = new
                        else:
                            regs.pop(ops[0], None)
                    if op[-1] == 'u' or op.endswith('ux'):       # update forms write the base
                        for a in ops[1:]:
                            mm = MEM_RE.match(a)
                            if mm:
                                regs.pop(mm.group(2), None)
    return rows


def read_section(mod, sect, addr, size):
    if mod == 'dol':
        data = open('orig/GYQE01/sys/main.dol', 'rb').read()
        for i in range(18):
            off, base, length = (struct.unpack_from('>I', data, b + 4 * i)[0] for b in (0, 0x48, 0x90))
            if length and base <= addr < base + length:
                return data[off + addr - base:off + addr - base + size]
        return b''
    index = {'.rodata': 4, '.data': 5}.get(sect)
    if index is None:
        return b''
    data = open('orig/GYQE01/files/%s.rel' % mod, 'rb').read()
    table = struct.unpack_from('>I', data, 0x10)[0]
    off = struct.unpack_from('>I', data, table + 8 * index)[0] & ~3
    return data[off + addr:off + addr + size]


def print_tables(syms):
    pairs = [(f[0], x) for f in FAMILIES for x in f[1:]]
    for (mod, name), (sect, addr, size, kind) in sorted(syms.items(), key=lambda kv: (kv[0][0], kv[1][1])):
        if kind != 'object' or not size or size % 54 or name.startswith('jumptable'):
            continue
        blob = read_section(mod, sect, addr, size)
        if len(blob) < size:
            continue
        es = size // 54
        rows = [blob[i * es:(i + 1) * es] for i in range(54)]
        equal = sum(rows[a] == rows[b] for a, b in pairs)
        if equal >= 17 and len(set(rows)) > 1:
            print('%-9s %-24s 0x%08X  54 x %-3d  family rows equal %d/%d, %d distinct'
                  % (mod, name, addr, es, equal, len(pairs), len(set(rows))))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--out', default='.agent/roster_expansion_sites.csv')
    ap.add_argument('--tables', action='store_true', help='print 54 x N data symbols with family-equal rows')
    ap.add_argument('--derived', action='store_true',
                    help='print the compare kinds, numbers derived from 54 and charID switch tables')
    ap.add_argument('--refs', action='store_true', help='write the table address-forming sites CSV')
    args = ap.parse_args()
    sites, evidence, derived = scan_sites()
    assert sites, 'no asm found: run `python3 configure.py && ninja` first'
    with open(args.out, 'w', newline='') as f:
        w = csv.writer(f, lineterminator='\n')
        w.writerow(['module', 'function', 'address', 'instruction', 'kind', 'evidence'])
        for (mod, addr), (fn, text, kind) in sorted(sites.items(), key=lambda kv: (kv[0][0], kv[1][0], kv[0][1])):
            w.writerow([mod, fn, addr, text, kind, ' '.join(sorted(evidence[(mod, fn)]))])
    per_mod = collections.Counter(mod for mod, _ in sites)
    print('%d sites in %d functions -> %s  (%s)' % (
        len(sites), len({(m, v[0]) for (m, _), v in sites.items()}), args.out,
        ', '.join('%s %d' % kv for kv in sorted(per_mod.items()))))
    if args.derived:
        kinds = collections.Counter((mod, v[2]) for (mod, _), v in sites.items())
        for mod in MODULES:
            print('  %-9s %s' % (mod, '  '.join('%s %d' % (k, kinds[(mod, k)])
                                               for k in ('range', 'equals', 'compare', 'load', 'count'))))
        for label in sorted(derived):
            fns = collections.Counter((mod, fn) for mod, fn, _ in derived[label])
            print('  %s: %d sites: %s' % (label, len(derived[label]),
                                         ' '.join('%s:%s(%d)' % (m, f, n) for (m, f), n in sorted(fns.items()))))
    if args.tables:
        print_tables(load_symbols())
    if args.refs:
        rows = scan_refs(load_symbols())
        out = args.out.replace('_sites.csv', '_refs.csv')
        with open(out, 'w', newline='') as f:
            w = csv.writer(f, lineterminator='\n')
            w.writerow(['table', 'module', 'function', 'address', 'instruction', 'table_offset', 'form', 'anchor'])
            for (mod, addr), (fn, text, name, off, how, anchor) in sorted(
                    rows.items(), key=lambda kv: (kv[1][2], kv[0][0], kv[1][0], kv[0][1])):
                w.writerow([name, mod, fn, addr, text, '0x%X' % off, how, anchor])
        per = collections.defaultdict(lambda: [collections.Counter(), set(), set()])
        for (mod, _), (fn, _, name, _, how, anchor) in rows.items():
            per[name][0][how] += 1
            per[name][1].add((mod, fn))
            per[name][2].add(anchor)
        print('%d address-forming sites -> %s' % (len(rows), out))
        for _, _, _, _, name in TABLES:
            c, fns, anchors = per[name]
            print('  %-28s %3d functions  named %3d  anchor+offset %3d  indexed %3d  via %s'
                  % (name, len(fns), c['named'], c['anchor+offset'], c['indexed'], ' '.join(sorted(anchors))))


if __name__ == '__main__':
    main()
