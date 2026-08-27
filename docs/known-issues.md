# Known issues

Status as of the self-contained pass. **Every snippet now compiles standalone**
(68/68 under GNU g++), which was not true when the notebook was first ported.

## What changed

Snippets used to be fragments that only compiled once pasted into a solution —
32 of 70 failed a standalone check. Each header now carries a short, clearly
marked deps block:

```cpp
// --- deps (drop what your solution already defines) ---
const int N = 2e5 + 5;
// ------------------------------------------------------
```

Delete those lines when your solution already declares them. `make
test-compiles` enforces that every header still builds on its own, and CI fails
the build if one stops.

## Bugs found and fixed

All of these were inherited from the predecessor repo. Four were in the
notebook the team was carrying to contests.

| File | Bug | In the old printed notebook? |
|---|---|---|
| `graph/Dijkstra.h` | declared `pq`, tested `q.empty()` | no |
| `strings/Eertree.h` | `add_char` declared `cur`, loops used `curr` (from commit `66cf9b9`) | **yes** |
| `data-structures/FenwickTree2d.h` | constructor initialised a nonexistent member `sz` | **yes** |
| `numerical/MatrixExponentiation.h` | called `mult()`, declared nowhere | **yes** |
| `numerical/NumberTheoreticTransform.h` | used `inverse()` three lines before declaring it | **yes** |
| `graph/LcaBinaryLifting.h` | `const int K;` left uninitialised | no |
| `dp/KnuthDP.h` | `max(ll, int)` type mismatch | no |
| `geometry/Point.h` | `operator==` not `const`, so `sort`/`unique` rejected it under libc++ | n/a |

`strings/Lps.h` was **removed**, not fixed: its prefix function was wrong (it
never backtracked `len` through `lps[len-1]`), `Kmp.h` builds its own and never
used it, and it did not earn the page space.

## Still open

- **Nothing is tested.** Every snippet is `Status: untested`. Compiling is not
  correctness — it means the code parses, nothing more. There are no stress
  tests.
- **Three snippets are GCC-only** and will not build under Apple clang:
  `OrderStatisticTree.h` (needs libstdc++'s `ext/pb_ds`), `SparseTable.h` and
  `LcaConstant.h` (both use `__lg`). ICPC judges run GCC, so this is fine for
  contests; on macOS use `brew install gcc` and `CXX=g++-16 make test-compiles`.
- **`EPS` is defined twice with different values** — `geometry/Point.h` uses
  `1e-7`, `numerical/GaussElimination.h` uses `1e-9`. They never share a
  translation unit today, so nothing breaks, but pasting both into one solution
  will collide.
- **`multiply(vector<ll> const&, vector<ll> const&)` has the same signature** in
  `FastFourierTransform.h` and `NumberTheoreticTransform.h`. Same caveat.
- **`ConvexHull.h` sorts with `pt::operator<`**, an EPS-based comparator that is
  not a strict weak ordering. `std::sort` on such a comparator is undefined
  behaviour, though it works in practice on contest-sized inputs.
- **`graph/EulerTour.h`** still carries a `TODO: Test implementation` from the
  predecessor.
- **`appendix/discrete-math.tex`** renders one line of Spanish (line 47) and
  carries a stray CP-1252 byte on line 67. Both inherited verbatim.
- **Page count is 20 of the ICPC limit of 25.** CI warns if a build exceeds 25.
