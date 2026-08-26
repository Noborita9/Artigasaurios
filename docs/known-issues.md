# Known issues

Everything here was found while porting the notebook from
`Noborita9/Dividimos-y-no-Conquistamos`. **Nothing was fixed during the port** — the
port copies code bodies unchanged, by design. This file is the starting point for
the deferred correctness pass.

## Snippets do not compile standalone

KACTL's headers are self-contained translation units that `#include` one another.
Ours are **fragments** meant to be pasted into a solution file, so most reference
things that only exist there. Measured during planning: **32 of 70** source
snippets fail a standalone syntax check. That is expected, not a defect, and no
build step gates on it.

Four categories:

| Category | Examples |
|---|---|
| Missing shared context — globals and constants assumed from the solution | `N`, `g`, `oo`, `MD`, `BS`, `BLOCK_SIZE`, `inverse`, `my_clock`, `rng` |
| Missing type aliases not in the template | `pii`, `pll`, `vi` |
| Geometry files needing `pt` from `Point.h` | `ConvexHull`, `PolygonArea`, `RayCasting`, `PlanarFaces` |
| True fragments — a loop or capturing lambda at file scope, not a function | `FloydWarshall`, `MoQueries`, `DivideAndConquerDP`, `SimpsonIntegration`, and the trailing example blocks in `MatrixExponentiation` and `SimpsonIntegration` |

CI runs a non-blocking standalone-compile report on every push, so the current
numbers are always in the job summary.

## Genuine bugs

These are not missing context — the code is wrong as written. Compiler output and,
where noted, direct testing. **Unverified beyond what is stated; nothing here has
been fixed.**

| File | Problem | Fails how | Was it in the old printed notebook? |
|---|---|---|---|
| `strings/Eertree.h` | `add_char` declares `cur` but its loops use `curr` | does not compile | **yes** |
| `data-structures/FenwickTree2d.h` | constructor initialises a member `sz` that does not exist | does not compile | **yes** |
| `numerical/MatrixExponentiation.h` | calls `mult()`, declared nowhere | does not compile | **yes** |
| `numerical/NumberTheoreticTransform.h` | line 7 initialises `root_1` by calling `inverse()`, declared at line 10 | does not compile | **yes** |
| `graph/Dijkstra.h` | declares `pq`, then line 7 tests `q.empty()` | does not compile | no |
| `strings/Lps.h` | **wrong prefix function** — see below | **compiles, returns wrong answers** | no |

`Eertree.h`'s bug was introduced by commit `66cf9b9` ("Shorten eertree") in the
predecessor repo.

### `Lps.h` deserves separate attention

It is the only one that compiles and runs. On a mismatch it sets `lps[i] = 0` and
advances `i` without backtracking `len` through `lps[len-1]`, and never resets
`len`. Verified by compiling it against a correct prefix function:

```
aabaaab    getLps=[0102003]   correct=[0101223]   <-- differs
aaaa       getLps=[0123]      correct=[0123]      same
ababab     getLps=[001234]    correct=[001234]    same
abcabcabd  getLps=[000123450] correct=[000123450] same
```

It is correct on simple patterns and only breaks on patterns with overlapping
repeats — which is exactly what KMP exists for. That is why it survived unnoticed.

`Kmp.h` does **not** depend on it: `KMP` builds its own prefix array via `nxt()`.

## Smaller oddities

- `geometry/Point.h` and `geometry/PointOperations.h` are two **incompatible**
  point representations — a `pt` struct of doubles versus free functions over
  `pair<ll,ll>`. Both are ported; reconciling them is a team decision.
- `geometry/RayCasting.h` assigns a cross product to an `ll` while `pt` stores
  doubles, truncating. Safe for integral coordinates, lossy otherwise.
- `graph/EulerTour.h` carries a `TODO: Test implementation` from the predecessor.
- `data-structures/SqrtDecomposition.h` and `MoQueries.h` state bounds that assume
  `BLOCK_SIZE` is near `sqrt(N)`; it is supplied externally or hardcoded.
- `numerical/GaussElimination.h` takes `bitset<BS>`, so `BS` must be a
  compile-time constant defined by the caller. Expected, not a bug.
- `contest/template.java` is ported but intentionally not printed. `make
  showexcluded` listing it is correct.
- `OrderStatisticTree.h` and `NumberTheoreticTransform.h` do not display a content
  hash. They are the only two headers with `#include` lines, and
  `content/tex/notebook.sty` renders the include list and the hash on the same
  line, so in the narrow three-column layout the include path pushes the hash out.
  Those two snippets cannot be hash-verified while typing.

## Not addressed by the port

- Page count. The predecessor was 27 pages, already over the ICPC 25-page limit.
  Pruning is a team decision and no snippet was dropped.
- `stress-tests/` does not exist.
- Every snippet is marked `Status: untested`. Nothing here has been tested.
