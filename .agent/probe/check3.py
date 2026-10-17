import sys,re,difflib,collections
target="""fsubs f4, f2, f9
lis
fsubs f1, f2, f1
lfs f2
fsubs f0, f3, f8
fdivs f1, f1, f4
fsubs f1, f2, f1
fmuls f0, f0, f1
fadds f0, f8, f0
stfs f0, 0x0(r3)""".split('\n')
def norm(i):
    if i.startswith('lis'): return 'lis'
    if i.startswith('lfs') and '@' in i: return 'lfs '+i.split(',')[0].split()[1]
    return i
s=open(sys.argv[1]).read().split('\n')
fn=None; body=[]
groups=collections.defaultdict(list)
def flush():
    if fn:
        # tail = everything after the last 'bge' up to stfs
        idx=max(i for i,b in enumerate(body) if b.startswith('bge') or b.startswith('blt') or b.startswith('b .'))
        tail=[norm(b) for b in body[idx+1:] if not b.startswith(('mr r3','blr'))]
        sm=difflib.SequenceMatcher(a=tail,b=target)
        d=sum(max(i2-i1,j2-j1) for tag,i1,i2,j1,j2 in sm.get_opcodes() if tag!='equal')
        groups[(d,tuple(tail))].append(fn)
for l in s:
    m=re.match(r'\.fn (\S+),',l)
    if m: flush(); fn=m.group(1); body=[]; continue
    if l.startswith('.endfn'): flush(); fn=None; body=[]; continue
    if fn and '*/' in l: body.append(l.split('*/',1)[1].strip())
keys=sorted(groups)
print(len(keys),'distinct tails')
for k in keys[:int(sys.argv[2]) if len(sys.argv)>2 else 6]:
    print('--- diff',k[0],'count',len(groups[k]),'e.g.',groups[k][:4])
    for t in k[1]: print('   ',t)
