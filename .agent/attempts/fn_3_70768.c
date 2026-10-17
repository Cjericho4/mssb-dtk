// Best non-matching tail: 1 mismatched line (was 6). In-tree now. Only the fmuls operand order differs:
//   target: fmuls f0, f0, f1      ours: fmuls f0, f1, f0
// Everything else in the tail already matches: dz in f4, z-targetZ in f1, 1.0f in f2, x-prevX in f0.
// What got us from 6 to 1 (mwcc GC/2.6 -O4,p behaviour, verified with a probe harness of ~10k variants):
//   * a single-def/single-use local (`dz = z - prevZ;`) is sunk/folded into its use and becomes an
//     expression temp -> it was evaluated first and took f0. Writing it as a two-step web
//     (`dz = z; dz -= prevZ;`) makes it a named web; webs are coloured AFTER the block's temps, so it
//     lands in f4 exactly like the target.
//   * with dz a leaf, `t = 1.0f - (z - targetZ) / dz; dx = (x - prevX) * t;` evaluates x-prevX first
//     (f0), then z-targetZ (f1), then the 1.0f load (f2) - the target's colouring.
//   * the remaining problem: for temp*temp the compiler emits the operand evaluated SECOND as the first
//     fmuls operand (and for web*temp it emits the web first). The target has x-prevX (f0, evaluated
//     first) as the first operand, which none of the forms below produce.
// Exhausted (all give either fmuls f0,f1,f0 with the right colours, or the right order with the wrong
// colours such as fmuls f2,f2,f0 / fmuls f0,f0,f1 with zt in f2): every placement/order of dx,dz,t as
// statements, `dx *= t`, `dx = dx * t`, `dx = t * dx`, two-step dx, accumulating the chain in targetZ or z,
// all-web forms (zt/one webs), declaration orders (incl. before z), block-scoped initialised declarations,
// dx/dz assigned inside `if (z < targetZ) { ...; break; }` (for(;;)/while(1)/do-while(1)), two-exit loops,
// inline helpers (lerp/interp/frac/remain/scale/dif/est* in ~20 shapes), a named -0.05f local,
// barriers/second uses to stop sinking. Probe harness: .scratch/probe/probe.sh + gen*.py + check3.py.
// Tail currently in tree:
//    dz = z;
//    dz -= prevZ;
//    t = 1.0f - (z - targetZ) / dz;
//    dx = (x - prevX) * t;
//    *outX = prevX + dx;
