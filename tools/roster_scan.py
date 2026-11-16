#!/usr/bin/env python3
"""Roster-expansion scanner (phase 6, .agent/roster_expansion.md).

Lists every instruction in the game's own code (DOL game units and the three RELs, from the
dtk-split asm in build/GYQE01) that uses the character count 54 (0x36) or the last charID 53
(0x35) as a compare, loop count, sentinel or size, and writes them to a CSV with the
per-character tables the same function references as evidence.

    python3 tools/roster_scan.py                 # writes .agent/roster_expansion_sites.csv
    python3 tools/roster_scan.py --tables        # also prints data symbols sized 54 x N whose
                                                 # colour-variant rows equal their base's row

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
    sites = {}                                   # (mod, addr) -> (fn, text)
    evidence = collections.defaultdict(set)      # (mod, fn) -> char tables referenced
    for mod, (patterns, _) in MODULES.items():
        for pattern in patterns:
            for path in glob.glob(pattern, recursive=True):
                fn = None
                for line in open(path, errors='replace'):
                    if line.startswith('.fn '):
                        fn = line.split()[1].rstrip(',')
                    elif line.startswith('.endfn'):
                        fn = None
                    elif fn:
                        m = INSN_RE.match(line)
                        if not m:
                            continue
                        addr, op, args = m.groups()
                        if op in BOUND_OPS and BOUND_RE.search(args):
                            sites[(mod, addr)] = (fn, op + ' ' + args)
                        evidence[(mod, fn)].update(CHAR_TABLES.intersection(IDENT_RE.findall(args)))
    return sites, evidence


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
    args = ap.parse_args()
    sites, evidence = scan_sites()
    assert sites, 'no asm found: run `python3 configure.py && ninja` first'
    with open(args.out, 'w', newline='') as f:
        w = csv.writer(f, lineterminator='\n')
        w.writerow(['module', 'function', 'address', 'instruction', 'evidence'])
        for (mod, addr), (fn, text) in sorted(sites.items(), key=lambda kv: (kv[0][0], kv[1][0], kv[0][1])):
            w.writerow([mod, fn, addr, text, ' '.join(sorted(evidence[(mod, fn)]))])
    per_mod = collections.Counter(mod for mod, _ in sites)
    print('%d sites in %d functions -> %s  (%s)' % (
        len(sites), len({(m, fn) for (m, _), (fn, _) in sites.items()}), args.out,
        ', '.join('%s %d' % kv for kv in sorted(per_mod.items()))))
    if args.tables:
        print_tables(load_symbols())


if __name__ == '__main__':
    main()
