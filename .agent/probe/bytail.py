import sys,re
exec(open('.agent/probe/check3.py').read().split("s=open(sys.argv[1])")[0])
src=open(sys.argv[1][:-2]+'.c').read()
bodies=dict(re.findall(r's32 (\S+)\(f32\* outX, BOOL curve, f32 targetZ\) \{ HEAD\([^)]*\)\n    (.*?) return frames;',src,re.S))
s=open(sys.argv[1]).read().split('\n'); fn=None; body=[]; res={}
def flush():
    if fn:
        idx=max(i for i,b in enumerate(body) if b.startswith(('bge','blt','b .')))
        res[fn]=tuple(norm(b) for b in body[idx+1:] if not b.startswith(('mr r3','blr','stfs')))
for l in s:
    m=re.match(r'\.fn (\S+),',l)
    if m: flush(); fn=m.group(1); body=[]; continue
    if l.startswith('.endfn'): flush(); fn=None; body=[]; continue
    if fn and '*/' in l: body.append(l.split('*/',1)[1].strip())
seen={}
for fn,t in res.items():
    base=fn.rsplit('_',1)[0]
    if base in seen and seen[base]==t: continue
    seen[base]=t
    print(fn,'|',bodies.get(fn,'?')[:140]); print('      ',' ; '.join(x for x in t if not x.startswith('lis')))
