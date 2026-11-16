#!/usr/bin/env python3
# usage: tools/put_stub.py <src.c> <function> <header.h or -> "<new prototype>" < body.c
# Replaces the empty stub of <function> ("... fn(void) { return; }") in <src.c> with the body read
# from stdin and, unless the header is "-", its "(void)" prototype in <header.h> with the new one.
# Fails loudly if the stub or prototype is not found, so nothing is half-edited.
import re,sys
src,fn,hdr,newproto=sys.argv[1:5]
body=sys.stdin.read()
s=open(src).read()
m=re.search(r"[\w \*]+\b%s\(void\) \{\n    return[^;]*;\n\}"%re.escape(fn),s)
assert m,'stub not found'
s=s[:m.start()]+body.rstrip()+s[m.end():]
open(src,'w').write(s)
if hdr!='-':
    h=open(hdr).read()
    m=re.search(r"^[\w \*]+\b%s\(void\);"%re.escape(fn),h,re.M)
    assert m,'proto not found'
    h=h[:m.start()]+newproto+h[m.end():]
    open(hdr,'w').write(h)
