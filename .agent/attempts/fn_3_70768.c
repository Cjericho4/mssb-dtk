// Best non-matching tail: 6 mismatched lines (in-tree version: 7). Only the tail differs from the target.
// Target defines dz=z-prevZ first (f4), then z-targetZ (f1), then x-prevX into a fresh f0, fdivs f1,f1,f4,
// fsubs 1-, fmuls f0,f0,f1, fadds. Ours always evaluates z-targetZ first and reuses x's register for x-prevX.
// Tried: every local/temp arrangement, dz/dx as statements, inline ratio/lerp/scale helpers, (f32) casts,
// 0.0f+ tricks, reusing vx/newVz as dz, decl-order moves, for(;;)/while(1)/while(z>=targetZ) loop forms.
// Tail used for the 6-line version (replace the in-tree tail with this):
//    dx = (x - prevX) * (1.0f - (z - targetZ) / (f32)(z - prevZ));
//    *outX = prevX + dx;
