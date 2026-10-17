import sys,re
s=open(sys.argv[1]).read().split('\n')
n=int(sys.argv[2]) if len(sys.argv)>2 else 12
fn=None; body=[]
def flush():
    if fn:
        print('=== '+fn)
        for i in body[-n:]: print('   ',i)
for l in s:
    m=re.match(r'\.fn (\S+),',l)
    if m: flush(); fn=m.group(1); body=[]; continue
    if l.startswith('.endfn'): flush(); fn=None; body=[]; continue
    if fn and '*/' in l: body.append(l.split('*/',1)[1].strip())
