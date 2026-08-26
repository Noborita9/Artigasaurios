# Artigasaurios Notebook — Design

**Date:** 2026-08-26
**Status:** Approved, pending implementation plan

## Purpose

Create `github.com/Noborita9/Artigasaurios`, the ICPC team reference notebook for the
new ORT Uruguay team Artigasaurios, by porting the contents of the predecessor repo
`Noborita9/Dividimos-y-no-Conquistamos` onto KACTL's organizational and build
architecture.

The predecessor repo works but has three structural problems this design fixes:

1. Build artifacts are committed (`guide.pdf`, `guide.aux`, `guide.fls`,
   `guide.fdb_latexmk`, `guide.log`, `guide.toc`, `_minted-guide/`), so every build
   dirties the tree.
2. Snippets carry no metadata. The PDF shows code with no description, no complexity,
   and no way to verify what you typed during a contest.
3. `guide.tex` is a hand-maintained flat list of `\cppfile{}` calls with content
   commented in and out, and `README.md` is a separately hand-maintained index that has
   already drifted out of sync with `src/` (it lists a `5.6` twice, references files
   that moved, and covers 41 entries against ~80 files in `src/`).

Success criteria: `make notebook` produces a 3-column PDF where every snippet is
preceded by its description and time complexity and annotated with a content hash;
no generated file is tracked in git; and adding a snippet means adding one `.h` and one
`\nbimport` line.

## Non-goals

- Fixing or optimizing the algorithms themselves. This is a port. Code that is wrong
  today stays wrong today, marked `Status: untested`.
- Converting snippets to KACTL's macro dialect. See "Macro vocabulary" below.
- Meeting the 25-page limit in the first build. See "Page count" below.

## Decisions

| Decision | Choice | Rationale |
|---|---|---|
| Repo | New `Noborita9/Artigasaurios`, public, **fresh history** | Clean slate; old repo survives as the archive |
| Prose language | English | Matches KACTL and matches ICPC problem statements |
| Content scope | Port **all** ~80 snippets, including ones currently commented out of `guide.tex` | Prune from evidence after we can see a real page count |
| Machinery | Full port of `kactlpkg.sty` + `preprocessor.py` | User chose full fidelity in both organization and PDF output |
| Macro vocabulary | Keep the **team's** (`L`, `SZ`, `ALL`, `vec`, `pb`, `eb`) | See below |
| PDF in git | No. CI builds it and attaches to a release | Root cause of the dirty-tree problem |

### Macro vocabulary — deliberate divergence from KACTL

KACTL snippets are written against `rep(i,a,b)` / `sz(x)` / `all(x)` / `vi` / `pii`.
The team's are written against `L(i,j,n)` / `SZ(x)` / `ALL(x)` / `vec` / `pb` / `eb`.

We keep the team's. Rewriting ~80 working files into another team's dialect buys nothing
the reader can see, costs a full re-verification pass, and fights the muscle memory that
matters most under contest time pressure. We adopt KACTL's *machinery*, not its *idiom*.

Consequence: `content/contest/template.cpp` remains the team's existing template, since
it defines the macros every other file assumes. `make test-compiles` enforces that
contract — a snippet using an undefined macro fails the build.

### Licensing

KACTL's build tooling (`kactlpkg.sty`, `preprocessor.py`, `hash.sh`) is CC0, so porting
it is unencumbered. The new repo ships a CC0 `LICENSE`. Ported snippets keep a `Source:`
field where the provenance is known, per KACTL's own convention of tracing attribution
rather than asserting ownership.

## Architecture

```
Artigasaurios/
├── Makefile                      fast · notebook · clean · test-compiles · showexcluded
├── README.md                     English: what it is, how to build, how to add a snippet
├── LICENSE                       CC0
├── .gitignore                    build/, .DS_Store, *.aux *.log *.fls *.fdb_latexmk *.toc *.out
├── .github/workflows/build.yml   make notebook + make test-compiles on push
├── content/
│   ├── notebook.tex              document root; \university{ORT Uruguay} \team{Artigasaurios}{...}
│   ├── tex/
│   │   ├── notebook.sty          port of kactlpkg.sty
│   │   └── preprocessor.py       port of KACTL's preprocessor
│   ├── contest/
│   ├── data-structures/
│   ├── graph/
│   ├── trees/
│   ├── dp/
│   ├── strings/
│   ├── number-theory/
│   ├── numerical/
│   ├── combinatorial/
│   ├── geometry/
│   ├── various/
│   └── appendix/
├── stress-tests/
└── build/                        gitignored
```

Every chapter directory holds a `chapter.tex` of the form:

```latex
\chapter{Data structures}
\nbimport{FenwickTree.h}
\nbimport{SegmentTree.h}
```

`content/notebook.tex` lists the chapters in print order and owns nothing else.

### Naming the ported machinery

`kactl*` identifiers are renamed to `nb*`/`notebook*`:
`kactlpkg.sty` → `notebook.sty`, `\kactlimport` → `\nbimport`,
`\kactlchapter` → `\nbchapter`, `\kactlref` → `\nbref`, `\@kactldir` → `\@nbdir`,
`kactl.tmp` → `notebook.tmp`.

This is a mechanical rename, but `.sty` and `.py` communicate through a
filename-and-macro contract (the `header.tmp` / `header2.tmp` handshake driving running
headers, and the `\write18` invocation passing `-i`/`-o`). A rename that misses one side
of that contract fails silently by producing wrong page headers rather than an error.
**Verification is a successful build with correct running headers, not a reading of the
diff.**

### Data flow (per snippet, at build time)

```
content/graph/Dinic.h
   │  pdflatex hits \nbimport{Dinic.h}
   ▼
notebook.sty  ──\write18──▶  preprocessor.py -i content/graph/Dinic.h -o build/notebook.tmp
   │                              │
   │                              ├─ parse /** ... */ header → Description, Time, Source, Status
   │                              ├─ strip /// comments, exclude-line, resolve #include
   │                              ├─ pipe body through content/contest/hash.sh → 6-char hash
   │                              └─ emit \nbref + description + lstlisting
   ▼
\input{build/notebook.tmp}  →  rendered into the 3-column page
```

## Chapter taxonomy

The predecessor's 11 sections become 12. The only substantive regrouping is splitting
its overloaded `Math/` (13 files spanning three unrelated fields) three ways.

| Predecessor | New chapter | Note |
|---|---|---|
| `Details/` | `contest/` | + `hash.sh`, `troubleshoot.txt` (new) |
| `DataStructure/`, `Other/Mo.cpp` | `data-structures/` | Mo joins DS, as in KACTL |
| `Graph/` | `graph/` | |
| `Tree/` | `trees/` | Kept separate; KACTL folds these into graph, but the team already treats trees as its own section |
| `DP/` | `dp/` | Own chapter; the team carries more DP than KACTL, which files DP opts under `various` |
| `String/` | `strings/` | |
| `Math/` → | `number-theory/` | Euclid, Totient, Mobius, Rho, GetDivisors |
| | `numerical/` | FFT, NTT, Gauss, MatExp, Simplex, Simpson |
| | `combinatorial/` | Josephus, Catalan |
| `Geometry/` | `geometry/` | |
| `Search/` | `various/` | ternary, simulated annealing |
| `MathFormulas/*.tex` | folded into matching chapters | Replaces the trailing "Ecuations" dump |
| — | `appendix/` | `techniques.txt`, new |

### File renaming

`.cpp` → `.h`, SCREAMING_CASE and Spanish → KACTL-style PascalCase. Proposed mapping for
the non-obvious cases; exact names confirmed against file contents during implementation:

| Predecessor | New |
|---|---|
| `DataStructure/BIT.cpp` | `data-structures/FenwickTree.h` |
| `DataStructure/BIT_2d.cpp` | `data-structures/FenwickTree2d.h` |
| `DataStructure/ChullTrick.cpp` | `data-structures/LineContainer.h` |
| `DataStructure/DSU.cpp` | `data-structures/UnionFind.h` |
| `DataStructure/policy_based.cpp` | `data-structures/OrderStatisticTree.h` |
| `DataStructure/index_compression.cpp` | `data-structures/IndexCompression.h` |
| `DataStructure/SegmentTreeIterativo.cpp` | `data-structures/SegmentTreeIterative.h` |
| `DataStructure/SegmentTreePersistente.cpp` | `data-structures/SegmentTreePersistent.h` |
| `DataStructure/SQRTDecomp.cpp` | `data-structures/SqrtDecomposition.h` |
| `Other/Mo.cpp` | `data-structures/MoQueries.h` |
| `Details/cmd_setup.sh` | `contest/.bashrc` |
| `DP/DnCopt.cpp` | `dp/DivideAndConquerDP.h` |
| `DP/KnuthOpt.cpp` | `dp/KnuthDP.h` |
| `Geometry/OPERATIONS.cpp` | `geometry/PointOperations.h` (free functions over `pair<ll,ll>`) |
| `Geometry/Point.cpp` | `geometry/Point.h` (the `pt` struct) |
| `Math/EUCLIDEAN_EXTENDED.cpp` | `number-theory/EuclidExtended.h` |
| `Math/EULER_TOTIENT.cpp` | `number-theory/EulerTotient.h` |
| `Math/RHO.cpp` | `number-theory/PollardRho.h` |
| `Math/MAT_EXP.cpp` | `numerical/MatrixExponentiation.h` |
| `String/HASHING.cpp` | `strings/Hashing.h` |
| `String/Z_FUNCTION.cpp` | `strings/ZFunction.h` |
| `Tree/LCA_const.cpp` | `trees/LcaConstant.h` |
| `Tree/LCA_log.cpp` | `trees/LcaBinaryLifting.h` |

Note `Geometry/OPERATIONS.cpp` and `Geometry/Point.cpp` are two *incompatible* point
representations (`pair<ll,ll>` free functions vs. a `pt` struct with operators). Both are
ported; reconciling them is future pruning work, not port work.

## Snippet file format

```cpp
/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Point update, prefix-sum query over an array. 1-indexed.
 * Time: O(\log N) per operation, O(N) construction.
 * Status: untested
 */
#pragma once
```

`Author` is taken from `git log` on the predecessor file, applying this mapping:

- `noborita`, `Noborita`, `Joaquin Bonora` → **Joaquin Bonora**
- `Juan Manuel Duarte`, `Juan` → **Juan Manuel Duarte**
- `nahuepera5` → **Joaquin Bonora** (former member, reattributed at the user's request)

`Description` and `Time` are the fields that render beside the code and are therefore the
change that actually makes the output resemble KACTL. `Status` starts at `untested`
across the board — honest, and it doubles as the queue for what to stress-test later.

## Build and verification

| Target | Does |
|---|---|
| `make fast` | One `pdflatex -shell-escape` pass. Iteration loop. |
| `make notebook` | Two passes, so TOC and `\pageref{LastPage}` settle. |
| `make test-compiles` | Compiles every `.h` standalone against `template.cpp`. |
| `make showexcluded` | Lists `.h` files no `chapter.tex` imports. |
| `make clean` / `veryclean` | Remove build intermediates / also the PDF. |

`make test-compiles` is the real regression net: it is what catches the port silently
dropping a `#include`, or a snippet depending on a macro the template does not define.
It runs in CI on every push alongside `make notebook`.

The per-snippet content hash comes from `content/contest/hash.sh`:
`cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6`, matching KACTL's,
so a team member can verify mid-contest that what they typed matches the page.

## Risks

**Page count — pruning is mandatory, not optional.** Measured, not assumed: rebuilding
the predecessor from source yields **27 pages**, matching its committed `guide.pdf`. It is
already 2 pages over the ICPC 25-page limit, with ~60 of its ~80 snippets active. (Commit
`a789306`, "Remove Point Definition So Guide is 25 pages", no longer holds.)

The new build pulls in both directions: 3 columns is denser, but all ~80 snippets plus
per-snippet descriptions is less dense. The net is not predictable from here, and the
starting point is already over budget — so the port must be followed by a pruning pass
before the notebook is contest-legal. The first successful build reports the real number
and pruning decisions are made from it. Prune candidates, in order:
`coinChange`, `editDistance`, `kadane`, `knapsack`, `LCS`, `TRIE`, `LPS`, `LCA_log`,
`SQRTDecomp`, `SimulatedAnnealing`, `template.java`.

**`\write18` / shell-escape.** The whole preprocessor design depends on
`pdflatex -shell-escape`. If a team member's TeX distribution restricts it, the build
fails in a way whose error message does not name the cause. The README documents this,
and CI pins a distribution where it works.

**Known-untested code carried forward.** `EulerTour.cpp` is marked
`% TODO: Test implementation` in the predecessor's `guide.tex`; DSU rollback and dynamic
connectivity are marked missing. These port as-is with `Status: untested`. Fixing them is
explicitly out of scope.

## Out of scope (candidate follow-up work)

- Populating `stress-tests/` — the directory and Makefile target exist; tests do not.
- Adding KACTL staples the team lacks (CRT, Berlekamp-Massey, Li Chao, Treap, halfplane
  intersection, Edmonds blossom).
- Reconciling the two geometry point representations.
- Moving the repo to a team GitHub org.
