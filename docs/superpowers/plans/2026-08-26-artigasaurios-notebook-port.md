# Artigasaurios Notebook Port — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build `Noborita9/Artigasaurios` by porting the ~73 code snippets of `Noborita9/Dividimos-y-no-Conquistamos` onto KACTL's organization and build architecture, producing a 3-column PDF where every snippet carries a description, time complexity, and a content hash.

**Architecture:** A LaTeX document (`content/notebook.tex`) includes one `chapter.tex` per topic directory. Each `chapter.tex` calls `\nbimport{File.h}`, which invokes a Python preprocessor via `\write18` that parses the file's `/** ... */` doc header, strips internal comments, hashes the code, and emits the LaTeX listing. `make` drives it; GitHub Actions builds it on push.

**Tech Stack:** LaTeX (`pdflatex -shell-escape`, `extreport` class), Python 3 (preprocessor), GNU Make, `g++ -std=c++20`, GitHub Actions.

**Spec:** `docs/superpowers/specs/2026-08-26-artigasaurios-notebook-design.md`

**Source repo (read-only):** `/Users/noborita/workspace/github.com/Noborita9/Dividimos-y-no-Conquistamos`
**KACTL reference clone (read-only):** `/private/tmp/claude-501/-Users-noborita-workspace-github-com-Noborita9/e8182e8e-8334-406f-be01-6d5609f0feee/scratchpad/kactl`

If the KACTL clone is missing, recreate it:
```bash
git clone --depth 1 https://github.com/kth-competitive-programming/kactl.git <scratchpad>/kactl
```

---

## Global Constraints

Every task's requirements implicitly include this section.

- **Prose language is English.** Descriptions, README, chapter titles, comments added by us. Existing Spanish inline comments inside snippet bodies may stay; do not mass-translate code comments.
- **Keep the team's macro dialect.** `L(i,j,n)`, `SZ(x)`, `ALL(x)`, `vec`, `pb`, `eb`, `ll`, `ld`. Do **not** convert to KACTL's `rep`/`sz`/`all`/`vi`/`pii`. `content/contest/template.cpp` defines these and every other file assumes them.
- **Every `.h` gets `#pragma once`** immediately after its doc header.
- **Every `.h` gets a doc header** with `Author`, `Date`, `License`, `Source`, `Description`, `Time`, `Status`. `Author` and `Description` are required by the preprocessor; a missing one is a build error.
- **`Status: untested`** on every ported file. Do not claim tested status for code we have not tested.
- **Author attribution mapping** (from `git log` on the source file):
  - `noborita`, `Noborita`, `Joaquin Bonora` → `Joaquin Bonora`
  - `Juan Manuel Duarte`, `Juan` → `Juan Manuel Duarte`
  - `nahuepera5` → `Joaquin Bonora` (former member, reattributed at the team's request)
- **Never commit generated files.** `build/`, `*.aux`, `*.log`, `*.fls`, `*.fdb_latexmk`, `*.toc`, `*.out`, `.DS_Store`. `notebook.pdf` is a CI artifact, not a tracked file.
- **Do not fix algorithms.** This is a port. Code that is wrong stays wrong, marked `untested`.
- **Compile checking is deferred.** Measurement during planning showed 32 of 70 snippets do
  not compile as standalone translation units — they are fragments meant to be pasted into a
  solution, unlike KACTL's self-contained headers. Making them standalone is real work the
  team has chosen to defer. **No task gates on compilation.** CI runs an advisory,
  non-blocking compile report so the data accumulates for that later pass.
- **No local compile checking.** Neither compiler on the team's macOS/arm64 machine can build
  the whole notebook (Apple clang lacks `__gnu_pbds`; homebrew GCC rejects the x86-only
  `#pragma GCC target("avx2")` in `template.cpp`). Compile checks run only in CI on Ubuntu
  x86-64.
- **Page count / the 25-page ICPC limit is out of scope.** Report the number; prune nothing.
- **`Time:` uses LaTeX math**, e.g. `O(N \log N)`. The preprocessor rewrites `O(...)` into `\bigo{...}`.
- **All `make` targets run from the repo root.** `preprocessor.py`'s path is hardcoded relative to CWD.
- **Commit author** for all commits: `Joaquin Bonora <joaquinbonora09@gmail.com>`.

---

## File Mapping Reference

The complete source→target mapping. Tasks 4–13 each implement one block.

### contest/ (Task 1, 2)
| Source | Target |
|---|---|
| `src/Details/template.cpp` | `content/contest/template.cpp` |
| `src/Details/cmd_setup.sh` | `content/contest/.bashrc` |
| `src/Details/Int128.cpp` | `content/contest/Int128.h` |
| `src/Details/RNG.cpp` | `content/contest/Rng.h` |
| `src/Details/template.py` | `content/contest/template.py` |
| `src/Details/template.java` | `content/contest/template.java` |
| — (new) | `content/contest/hash.sh` |
| — (new) | `content/contest/troubleshoot.txt` |

### data-structures/ (Task 3)
| Source | Target |
|---|---|
| `src/DataStructure/BIT.cpp` | `FenwickTree.h` |
| `src/DataStructure/BIT_2d.cpp` | `FenwickTree2d.h` |
| `src/DataStructure/ChullTrick.cpp` | `LineContainer.h` |
| `src/DataStructure/DSU.cpp` | `UnionFind.h` |
| `src/DataStructure/index_compression.cpp` | `IndexCompression.h` |
| `src/DataStructure/policy_based.cpp` | `OrderStatisticTree.h` |
| `src/DataStructure/SegmentTree.cpp` | `SegmentTree.h` |
| `src/DataStructure/SegmentTreeIterativo.cpp` | `SegmentTreeIterative.h` |
| `src/DataStructure/SegmentTreePersistente.cpp` | `SegmentTreePersistent.h` |
| `src/DataStructure/SparseTable.cpp` | `SparseTable.h` |
| `src/DataStructure/SQRTDecomp.cpp` | `SqrtDecomposition.h` |
| `src/Other/Mo.cpp` | `MoQueries.h` |

### graph/ (Task 4) — includes the former `Tree/` section
| Source | Target |
|---|---|
| `src/Graph/bellman.cpp` | `BellmanFord.h` |
| `src/Graph/dijkstra.cpp` | `Dijkstra.h` |
| `src/Graph/Dinic.cpp` | `Dinic.h` |
| `src/Graph/DirectedMST.cpp` | `DirectedMST.h` |
| `src/Graph/EulerTour.cpp` | `EulerTour.h` |
| `src/Graph/floyd.cpp` | `FloydWarshall.h` |
| `src/Graph/hopkarp.cpp` | `HopcroftKarp.h` |
| `src/Graph/hungarian.cpp` | `Hungarian.h` |
| `src/Graph/kuhn.cpp` | `Kuhn.h` |
| `src/Graph/MCMF.cpp` | `MinCostMaxFlow.h` |
| `src/Graph/SCC.cpp` | `Scc.h` |
| `src/Graph/tarjan.cpp` | `BridgesArticulation.h` |
| `src/Graph/TwoSat.cpp` | `TwoSat.h` |
| `src/Tree/Centroid.cpp` | `CentroidDecomposition.h` |
| `src/Tree/HLD.cpp` | `HeavyLightDecomposition.h` |
| `src/Tree/LCA_const.cpp` | `LcaConstant.h` |
| `src/Tree/LCA_log.cpp` | `LcaBinaryLifting.h` |

### dp/ (Task 5)
| Source | Target |
|---|---|
| `src/DP/coinChange.cpp` | `CoinChange.h` |
| `src/DP/DnCopt.cpp` | `DivideAndConquerDP.h` |
| `src/DP/editDistance.cpp` | `EditDistance.h` |
| `src/DP/kadane.cpp` | `Kadane.h` |
| `src/DP/knapsack.cpp` | `Knapsack.h` |
| `src/DP/KnuthOpt.cpp` | `KnuthDP.h` |
| `src/DP/LCS.cpp` | `Lcs.h` |
| `src/DP/LIS.cpp` | `Lis.h` |

### strings/ (Task 6)
| Source | Target |
|---|---|
| `src/String/AhoCorasick.cpp` | `AhoCorasick.h` |
| `src/String/eertree.cpp` | `Eertree.h` |
| `src/String/HASHING.cpp` | `Hashing.h` |
| `src/String/KMP.cpp` | `Kmp.h` |
| `src/String/LPS.cpp` | `Lps.h` |
| `src/String/Manacher.cpp` | `Manacher.h` |
| `src/String/SuffixArray.cpp` | `SuffixArray.h` |
| `src/String/SuffixAutomaton.cpp` | `SuffixAutomaton.h` |
| `src/String/TRIE.cpp` | `Trie.h` |
| `src/String/Z_FUNCTION.cpp` | `ZFunction.h` |

### number-theory/ (Task 7)
| Source | Target |
|---|---|
| `src/Math/EUCLIDEAN_EXTENDED.cpp` | `EuclidExtended.h` |
| `src/Math/EULER_TOTIENT.cpp` | `EulerTotient.h` |
| `src/Math/MOBIUS.cpp` | `Mobius.h` |
| `src/Math/RHO.cpp` | `PollardRho.h` |
| `src/Math/GetDivisors.cpp` | `GetDivisors.h` |
| `src/MathFormulas/Mobius.tex` | `mobius-formulas.tex` |

### numerical/ (Task 8)
| Source | Target |
|---|---|
| `src/Math/fft.cpp` | `FastFourierTransform.h` |
| `src/Math/NTT.cpp` | `NumberTheoreticTransform.h` |
| `src/Math/GAUSS.cpp` | `GaussElimination.h` |
| `src/Math/MAT_EXP.cpp` | `MatrixExponentiation.h` |
| `src/Math/SIMPLEX.cpp` | `Simplex.h` |
| `src/Math/SIMPSON.cpp` | `SimpsonIntegration.h` |

### combinatorial/ (Task 9)
| Source | Target |
|---|---|
| `src/Math/JOSEPHUS.cpp` | `Josephus.h` |
| `src/Math/num_catalanes.png` | `num_catalanes.png` (asset) |
| `src/MathFormulas/CatalanNumbers.tex` | `catalan-numbers.tex` |
| `src/MathFormulas/Combinatorias.tex` | `combinatorics.tex` |
| `src/MathFormulas/Burnside.tex` | `burnside.tex` |

### geometry/ (Task 10)
| Source | Target |
|---|---|
| `src/Geometry/CONVEX_HULL.cpp` | `ConvexHull.h` |
| `src/Geometry/OPERATIONS.cpp` | `PointOperations.h` |
| `src/Geometry/PLANAR_FACES.cpp` | `PlanarFaces.h` |
| `src/Geometry/Point.cpp` | `Point.h` |
| `src/Geometry/POLYGON_AREA.cpp` | `PolygonArea.h` |
| `src/Geometry/RAY_CASTING.cpp` | `RayCasting.h` |
| `src/Geometry/Geometry.tex` | `geometry-notes.tex` |
| `src/MathFormulas/GeometryAreas.tex` | `areas.tex` |
| `src/MathFormulas/Trigonometry.tex` | `trigonometry.tex` |

### various/ (Task 11)
| Source | Target |
|---|---|
| `src/Search/ternary.cpp` | `TernarySearch.h` |
| `src/Search/SimulatedAnnealing.cpp` | `SimulatedAnnealing.h` |

### appendix/ (Task 12)
| Source | Target |
|---|---|
| `src/MathFormulas/Discreta.tex` | `discrete-math.tex` |
| `src/MathFormulas/UsefulMath.tex` | `useful-math.tex` |
| — (new) | `techniques.txt` |

---

## Task 1: Build pipeline end to end

Delivers a working `make fast` that renders one real snippet with description, complexity, and hash. This proves the entire ported machinery before any bulk content work.

**Files:**
- Create: `.gitignore`, `LICENSE`, `Makefile`
- Create: `content/notebook.tex`
- Create: `content/tex/notebook.sty` (ported), `content/tex/preprocessor.py` (ported)
- Create: `content/contest/chapter.tex`, `content/contest/template.cpp`, `content/contest/hash.sh`

**Interfaces:**
- Produces: `\nbimport[<preprocessor-flags>]{File.h}` — used by every `chapter.tex`.
- Produces: `\nbchapter{<dirname>}` — used by `content/notebook.tex`.
- Produces: `\nbcontentdir{content}` — sets the content root.
- Produces: `make fast`, `make notebook`, `make clean`, `make veryclean`.
- Produces: `content/contest/hash.sh`, invoked by `preprocessor.py` as `sh content/contest/hash.sh`.

- [ ] **Step 1: Create the directory skeleton and `.gitignore`**

```bash
cd /Users/noborita/workspace/github.com/Noborita9/Artigasaurios
mkdir -p content/tex content/contest build
cat > .gitignore <<'EOF'
build/
*.aux
*.log
*.out
*.toc
*.fls
*.fdb_latexmk
*.ptc
*.tmp
*.synctex.gz
.DS_Store
.vs/
notebook.pdf
EOF
```

- [ ] **Step 2: Add the CC0 LICENSE**

```bash
curl -sL https://creativecommons.org/publicdomain/zero/1.0/legalcode.txt -o LICENSE
# If offline, write the CC0 1.0 Universal header manually; the file must exist and name CC0.
test -s LICENSE && head -3 LICENSE
```

- [ ] **Step 3: Port the machinery with the rename**

The two-pass order matters: `kactlpkg` must be replaced before the bare `kactl`.

```bash
KACTL=/private/tmp/claude-501/-Users-noborita-workspace-github-com-Noborita9/e8182e8e-8334-406f-be01-6d5609f0feee/scratchpad/kactl
sed 's/kactlpkg/notebook/g; s/kactl/nb/g' "$KACTL/content/tex/kactlpkg.sty"    > content/tex/notebook.sty
sed 's/kactlpkg/notebook/g; s/kactl/nb/g' "$KACTL/content/tex/preprocessor.py" > content/tex/preprocessor.py
cp "$KACTL/content/contest/hash.sh" content/contest/hash.sh
```

- [ ] **Step 4: Verify the rename left no `kactl` behind and the cross-file contract matches**

The `.sty` defines `\nbref`/`\nberror`/`\nbwarning`; `preprocessor.py` emits them. If these disagree the build produces wrong headers *without erroring*, so check explicitly.

Run:
```bash
grep -c kactl content/tex/notebook.sty content/tex/preprocessor.py   # expect 0 and 0
grep -oE '\\\\nb[a-z]+' content/tex/preprocessor.py | sort -u        # emitted by .py
grep -oE '\\newcommand\{\\nb[a-z]+' content/tex/notebook.sty | sort -u  # defined by .sty
```
Expected: zero `kactl` matches. Every macro the `.py` emits (`\nbref`, `\nberror`, `\nbwarning`) appears in the `.sty` definitions.

- [ ] **Step 5: Port the team template unchanged**

```bash
cp ../Dividimos-y-no-Conquistamos/src/Details/template.cpp content/contest/template.cpp
```

Do not edit it. It defines the macro dialect every other file depends on.

- [ ] **Step 6: Write `content/contest/chapter.tex`**

```latex
\chapter{Contest}

\nbimport[-l rawcpp]{template.cpp}
\nbimport[-l raw]{hash.sh}
```

- [ ] **Step 7: Write `content/notebook.tex`**

`\maketeampage` is deliberately commented out: it calls `\includegraphics{\@unilogo}` and we have no ORT logo asset. Add one later as `content/tex/ort.pdf` and swap the two lines.

```latex
\documentclass[9pt, a4paper, notitlepage]{extreport}
\usepackage{notebook}
\nbcontentdir{content}

\university{ORT}{ORT Uruguay}{ort}
\team{Artigasaurios}{Joaquin Bonora, Juan Manuel Duarte, Nahuel Zeballos}
\contest{\ }{\today}

\begin{document}
	% \maketeampage   % needs content/tex/ort.pdf
	\maketitle{Artigasaurios}{\today}
	\begin{multicols*}{3}
	\thispagestyle{fancy}
	\setcounter{tocdepth}{0}
	\tableofcontents

	\nbchapter{contest}
	\end{multicols*}
\end{document}
```

- [ ] **Step 8: Write the `Makefile`**

```makefile
LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "Artigasaurios ICPC notebook"
	@echo ""
	@echo "	make fast		- build once (quick iteration)"
	@echo "	make notebook		- build properly (two passes)"
	@echo "	make showexcluded	- list headers no chapter.tex imports"
	@echo "	make clean		- remove build intermediates"
	@echo "	make veryclean		- also remove notebook.pdf"

fast: | build
	$(LATEXCMD) content/notebook.tex </dev/null
	cp build/notebook.pdf notebook.pdf

notebook: | build
	$(LATEXCMD) content/notebook.tex && $(LATEXCMD) content/notebook.tex
	cp build/notebook.pdf notebook.pdf

clean:
	cd build && rm -f notebook.aux notebook.log notebook.tmp notebook.toc notebook.ptc notebook.pdf

veryclean: clean
	rm -f notebook.pdf

build:
	mkdir -p build/

showexcluded: | build
	grep -Rho '\\nbimport[^{]*{[^}]*}' content/ | sed 's/.*{//; s/}//' > build/headers_included
	find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included || true

.PHONY: help fast notebook clean veryclean showexcluded
```

The Task 1 Makefile ends at the `.PHONY` line. There is no `test-compiles` target; compile
checking lives only in CI (see Global Constraints).

Portability note: `showexcluded` deliberately avoids `grep -P`, which BSD/macOS grep does not support.

- [ ] **Step 9: Run the build — this is the real test of the port**

Run: `make fast`
Expected: exits 0, `notebook.pdf` is created. If it fails, read `build/notebook.log` — the most likely causes are (a) `-shell-escape` disabled in your TeX distribution, (b) `extreport` missing (install `texlive-latex-extra`), (c) a rename mismatch from Step 4.

- [ ] **Step 10: Verify the pipeline actually did its job**

A PDF that builds is not proof the preprocessor ran. Check the rendered text:

```bash
pdftotext notebook.pdf - | head -60
```
Expected: the template's source appears, preceded by its section entry, and a 6-character hex hash appears near it. If code renders but no hash appears, `hash.sh` is not being found — check the path in `preprocessor.py`.

- [ ] **Step 11: Commit**

```bash
git add -A
git commit -m "Add build pipeline ported from KACTL

Ports kactlpkg.sty and preprocessor.py with kactl->nb rename, adds
Makefile, CC0 license, and the contest chapter with the team template.

Co-Authored-By: Claude Opus 5 <noreply@anthropic.com>"
```

---

## Task 2: Complete the contest chapter

**Files:**
- Create: `content/contest/.bashrc`, `content/contest/Int128.h`, `content/contest/Rng.h`, `content/contest/template.py`, `content/contest/template.java`, `content/contest/troubleshoot.txt`
- Modify: `content/contest/chapter.tex`

**Interfaces:**
- Consumes: `\nbimport` from Task 1.
- Produces: nothing later tasks depend on.

- [ ] **Step 1: Port the shell setup as `.bashrc`**

Source `src/Details/cmd_setup.sh` is a set of shell helpers. Copy it, then append a comment line naming what it does, since it renders in the PDF without a doc header (`-l raw` files are not preprocessed for metadata).

```bash
cp ../Dividimos-y-no-Conquistamos/src/Details/cmd_setup.sh content/contest/.bashrc
```

- [ ] **Step 2: Port `Int128.h` and `Rng.h` with doc headers**

Read each source file first to write an accurate `Description` and `Time`. Example for `Rng.h`:

```cpp
/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Seeded 64-bit Mersenne Twister with a helper for uniform
 * integers in a range. Use instead of rand() to avoid anti-hash tests.
 * Time: O(1) per draw.
 * Status: untested
 */
#pragma once
```

Confirm each file's actual author with:
```bash
cd ../Dividimos-y-no-Conquistamos && git log --format='%an' -- src/Details/RNG.cpp | sort -u
```
then apply the attribution mapping from Global Constraints.

- [ ] **Step 3: Port the Python and Java templates**

```bash
cp ../Dividimos-y-no-Conquistamos/src/Details/template.py   content/contest/template.py
cp ../Dividimos-y-no-Conquistamos/src/Details/template.java content/contest/template.java
```

`template.java` was commented out of the predecessor's `guide.tex`. Port the file but do **not** add a `\nbimport` for it — it stays available and unprinted. `make showexcluded` will list it; that is correct and expected.

- [ ] **Step 4: Write `content/contest/troubleshoot.txt`**

A contest debugging checklist. This is new content, not a port. Write it in English, plain text, no LaTeX:

```
Pre-submit checklist
	Read the full problem statement again.
	Is the output format exactly right? Trailing newline, case, spacing.
	Integer overflow? Are you using ll where the bound needs it?
	Array bounds: is MAXN big enough? Off by one in 0- vs 1-indexing?
	Did you reset global state between test cases?
	Multiple test cases: did you clear vectors/maps/adjacency lists?

Wrong answer
	Test the sample by hand, then n=1, n=0, and the maximum bound.
	Write a brute force and stress test against it.
	Are you printing a double with enough precision? setprecision.
	Is the comparator strict-weak-ordering? (a<b, never a<=b)

Runtime error
	Out of bounds, or recursion too deep for the stack.
	Division by zero, including modulo by zero.
	Reading past EOF.

Time limit exceeded
	What is the real complexity? Count the nested loops again.
	Are you copying a large structure by value into a function?
	endl flushes; use "\n".
	Is cin untied? cin.tie(0)->sync_with_stdio(0).

Memory limit exceeded
	Is the array bound larger than it needs to be?
	Are you storing what you could recompute?
```

- [ ] **Step 5: Update `content/contest/chapter.tex`**

```latex
\chapter{Contest}

\nbimport[-l rawcpp]{template.cpp}
\nbimport[-l sh]{.bashrc}
\nbimport[-l raw]{hash.sh}
\nbimport{Int128.h}
\nbimport{Rng.h}
\nbimport[-l py]{template.py}
\nbimport[-l raw]{troubleshoot.txt}
```

- [ ] **Step 6: Build and verify**

Run: `make fast`
Expected: exits 0.

Run: `pdftotext notebook.pdf - | grep -i "troubleshoot\|Pre-submit"`
Expected: the troubleshooting content appears in the PDF.

- [ ] **Step 7: Commit**

```bash
git add -A
git commit -m "Complete the contest chapter

Adds shell setup, Int128, RNG, Python/Java templates, and a
troubleshooting checklist.

Co-Authored-By: Claude Opus 5 <noreply@anthropic.com>"
```

---

## Tasks 3–12: Chapter ports

**Tasks 3–12 all follow the identical cycle below.** The only differences are the directory, the file list (see File Mapping Reference), and the chapter title. The cycle is written out once here in full; each task section then states only its specifics.

### The chapter port cycle

- [ ] **Step 1: Read every source file in the block.** You cannot write an accurate `Description` or `Time` without reading the implementation. Do not guess complexities from the filename.

- [ ] **Step 2: Determine each file's author.**
```bash
cd ../Dividimos-y-no-Conquistamos && git log --format='%an' -- <source-path> | sort -u; cd -
```
Apply the attribution mapping from Global Constraints.

- [ ] **Step 3: Create each target `.h`** — doc header, `#pragma once`, then the original body **unchanged**. Worked example (`data-structures/FenwickTree.h`, ported from `BIT.cpp`):

```cpp
/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Fenwick tree over a 1-indexed array. Point update, prefix-sum
 * query, and range sum. Built from an existing vector in linear time.
 * Time: O(\log N) per update and query, O(N) construction.
 * Status: untested
 */
#pragma once
#define LSO(S) (S & -S) // LeastSignificantOne
struct FT { // 1-Index
    vec<int> ft; int n;
    // ... body copied verbatim from src/DataStructure/BIT.cpp ...
};
```

- [ ] **Step 4: Write `content/<dir>/chapter.tex`** with a `\chapter{<Title>}` line and one `\nbimport{File.h}` per file, in a sensible reading order (simplest first).

- [ ] **Step 5: Register the chapter** in `content/notebook.tex` by adding `\nbchapter{<dir>}` inside the `multicols*` block, in print order.

- [ ] **Step 6: Run the exclusion check.**
Run: `make showexcluded`
Expected: lists only `content/contest/template.java` (intentionally unprinted). Any other file listed means you created a `.h` and forgot its `\nbimport`.

- [ ] **Step 7: Build.**
Run: `make fast`
Expected: exit 0.

- [ ] **Step 8: Verify the chapter rendered.**
Run: `pdftotext notebook.pdf - | grep -c "<a distinctive identifier from one of the new files>"`
Expected: at least 1.

- [ ] **Step 9: Commit.**
```bash
git add -A
git commit -m "Port the <chapter> chapter

<N> snippets ported from src/<Source>/ with doc headers. All marked
untested; no algorithm changes.

Co-Authored-By: Claude Opus 5 <noreply@anthropic.com>"
```

### Task 3: data-structures
Directory `content/data-structures/`, title `Data structures`, 12 files (see mapping).
`OrderStatisticTree.h` needs `#include <ext/pb_ds/assoc_container.hpp>` and `using namespace __gnu_pbds;` retained from the source — keep them inside the header.
Suggested `chapter.tex` order: UnionFind, IndexCompression, SparseTable, FenwickTree, FenwickTree2d, SegmentTree, SegmentTreeIterative, SegmentTreePersistent, SqrtDecomposition, LineContainer, OrderStatisticTree, MoQueries.

### Task 4: graph
Directory `content/graph/`, title `Graph`, 17 files (see mapping — includes the former `Tree/`).
Note `EulerTour.h` is flagged `% TODO: Test implementation` in the predecessor. Port as-is with `Status: untested`; do not attempt a fix.
Suggested order: Dijkstra, BellmanFord, FloydWarshall, Scc, BridgesArticulation, TwoSat, EulerTour, DirectedMST, Kuhn, HopcroftKarp, Hungarian, Dinic, MinCostMaxFlow, LcaBinaryLifting, LcaConstant, HeavyLightDecomposition, CentroidDecomposition.

### Task 5: dp
Directory `content/dp/`, title `Dynamic Programming`, 8 files.
Suggested order: Kadane, CoinChange, Knapsack, Lcs, EditDistance, Lis, DivideAndConquerDP, KnuthDP.

### Task 6: strings
Directory `content/strings/`, title `Strings`, 10 files.
Suggested order: Hashing, Lps, Kmp, ZFunction, Manacher, Trie, AhoCorasick, SuffixArray, SuffixAutomaton, Eertree.

### Task 7: number-theory
Directory `content/number-theory/`, title `Number theory`, 5 headers + 1 `.tex`.
`chapter.tex` ends with a raw include for the formulas: `\input{content/number-theory/mobius-formulas.tex}`.
Suggested order: EuclidExtended, EulerTotient, GetDivisors, Mobius, PollardRho, then the formulas.

### Task 8: numerical
Directory `content/numerical/`, title `Numerical`, 6 files.
Suggested order: GaussElimination, MatrixExponentiation, SimpsonIntegration, Simplex, FastFourierTransform, NumberTheoreticTransform.

### Task 9: combinatorial
Directory `content/combinatorial/`, title `Combinatorial`, 1 header + 3 `.tex` + 1 image asset.
Copy `num_catalanes.png` alongside; `catalan-numbers.tex` references it — verify the `\includegraphics` path still resolves after the move, and fix the path if not.
`chapter.tex`: `\nbimport{Josephus.h}` then `\input{}` for combinatorics.tex, catalan-numbers.tex, burnside.tex.

### Task 10: geometry
Directory `content/geometry/`, title `Geometry`, 6 headers + 3 `.tex`.
`Point.h` and `PointOperations.h` are two incompatible point representations (a `pt` struct vs. free functions over `pair<ll,ll>`). Port both unchanged; reconciliation is the team's, explicitly out of scope.
Both were measured during planning to fail standalone compilation (they need `pt` from `Point.h`); that is expected and not something to fix here.
Suggested order: Point, PointOperations, ConvexHull, PolygonArea, RayCasting, PlanarFaces, then the formula includes.

### Task 11: various
Directory `content/various/`, title `Various`, 2 files.
Suggested order: TernarySearch, SimulatedAnnealing.

### Task 12: appendix
Directory `content/appendix/`, title `Appendix`, 2 ported `.tex` + `techniques.txt` (new).
`techniques.txt` is a plain-text list of problem-solving techniques to scan when stuck (greedy, binary search on answer, small-to-large, bitmask DP, meet in the middle, sqrt decomposition, coordinate compression, two pointers, inclusion-exclusion, randomization). Write it in English, one technique per line, grouped by heading.
Register the appendix in `notebook.tex` in its own trailing `multicols*` block, matching KACTL:
```latex
	\begin{multicols*}{3}
	\nbchapter{appendix}
	\end{multicols*}
```

---

## Task 13: README, known issues, and CI

**Files:**
- Create: `README.md`, `docs/known-issues.md`, `.github/workflows/build.yml`

**Interfaces:**
- Consumes: `make notebook` from Task 1.

- [ ] **Step 1: Write `.github/workflows/build.yml`**

```yaml
name: build

on:
  push:
  pull_request:

jobs:
  notebook:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Install TeX Live and tools
        run: |
          sudo apt-get update
          sudo apt-get install -y --no-install-recommends \
            texlive-latex-recommended texlive-latex-extra \
            texlive-fonts-recommended poppler-utils

      - name: Advisory compile report (non-blocking)
        continue-on-error: true
        run: |
          # Snippets are fragments, not standalone TUs; this reports, never gates.
          # See docs/known-issues.md. Ubuntu x86-64 has both __gnu_pbds and avx2.
          TMP=$(mktemp -d)
          sed -e '/^#pragma GCC/d' -e '/^void solve/,$d' content/contest/template.cpp > "$TMP/prelude.h"
          pass=0; fail=0
          for h in $(find content -name '*.h' | sort); do
            { cat "$TMP/prelude.h"; echo "#include \"$PWD/$h\""; echo "int main(){}"; } > "$TMP/tu.cpp"
            if g++ -std=c++20 -fsyntax-only -w "$TMP/tu.cpp" 2>/dev/null; then
              pass=$((pass+1))
            else
              fail=$((fail+1)); echo "- \`$h\`" >> "$TMP/failing"
            fi
          done
          { echo "### Standalone compile report"; echo "$pass compile, $fail do not."; \
            echo; echo "<details><summary>Not standalone</summary>"; echo; \
            cat "$TMP/failing" 2>/dev/null; echo; echo "</details>"; } >> "$GITHUB_STEP_SUMMARY"

      - name: Build the notebook
        run: make notebook

      - name: Report page count
        run: |
          pages=$(pdfinfo notebook.pdf | awk '/^Pages:/{print $2}')
          echo "notebook.pdf is $pages pages" | tee -a "$GITHUB_STEP_SUMMARY"

      - uses: actions/upload-artifact@v4
        with:
          name: notebook
          path: notebook.pdf
```

Note `-shell-escape` is required by the build and is enabled by the Makefile, not by a TeX config; no extra CI setup is needed for it.

- [ ] **Step 2: Verify the workflow file parses**

Run: `python3 -c "import yaml,sys; yaml.safe_load(open('.github/workflows/build.yml')); print('valid')"`
Expected: `valid`. (If PyYAML is unavailable, skip — CI will report syntax errors on push.)

- [ ] **Step 3: Write `docs/known-issues.md`**

Record what planning measured, so the deferred compile pass has a starting point. Must state: that 32 of 70 snippets do not compile standalone and why (fragments, not translation units); the four categories (missing shared context such as `N`/`g`/`oo`/`MD`/`BS`/`BLOCK_SIZE`/`inverse`/`my_clock`; geometry files needing `pt` from `Point.h`; file-scope loops and capturing lambdas in `floyd`/`Mo`/`DnCopt`/`SIMPSON`; missing aliases `pii`/`pll`/`vi`); and the three that look like genuine bugs rather than missing context:

| File | Compiler says | Note |
|---|---|---|
| `strings/Eertree.h` | `'curr' was not declared; did you mean 'cur'?` | Likely introduced by commit `66cf9b9` "Shorten eertree". **This code is in the current printed PDF.** |
| `data-structures/FenwickTree2d.h` | `class 'BIT' does not have any field named 'sz'` | Constructor initialises a member that does not exist |
| `numerical/MatrixExponentiation.h` | `'mult' was not declared in this scope` | Helper function missing |

State plainly that these are unverified compiler output, not a confirmed diagnosis, and that nothing was fixed during the port.

- [ ] **Step 4: Write `README.md`**

Must cover, in English: what the repo is; the team; that it descends from Dividimos y no Conquistamos; how to build (`make notebook`); the `-shell-escape` requirement and what its failure looks like; how to add a snippet (create `content/<chapter>/Foo.h` with a doc header, add `\nbimport{Foo.h}` to that chapter's `chapter.tex`, run `make fast`); the doc-header field reference; that `notebook.pdf` is a CI artifact and is not committed; and credit to KACTL for the build machinery, with a link and a note that it is CC0.

Do not hand-maintain an index of snippets in the README. That is exactly the drift that made the predecessor's README wrong, and `chapter.tex` is now the single source of truth.

- [ ] **Step 5: Verify the documented workflow actually works**

Follow your own README from a clean state:
```bash
make veryclean && make notebook
```
Expected: succeeds. If a README step is wrong, fix the README.

- [ ] **Step 6: Commit**

```bash
git add -A
git commit -m "Add README, known issues, and CI

CI builds the notebook, reports page count, uploads the PDF, and runs a
non-blocking standalone-compile report. Known issues from planning are
recorded for the deferred compile pass.

Co-Authored-By: Claude Opus 5 <noreply@anthropic.com>"
```

---

## Task 14: Publish

**Files:** none

- [ ] **Step 1: Full clean verification before publishing**

Run:
```bash
make veryclean
make notebook
make showexcluded
git status --porcelain
```
Expected: build succeeds; `showexcluded` lists only `template.java`; **`git status` is empty** — if any generated file shows up, `.gitignore` is wrong. Fix before pushing.

- [ ] **Step 2: Report the page count**

Run: `pdfinfo notebook.pdf | grep Pages`
Record the number in the final report. Do not act on it — pruning is the team's decision.

- [ ] **Step 3: Create the GitHub repo and push**

This is the first outward-facing action in the plan. **Confirm with the user before running it.**

```bash
gh repo create Noborita9/Artigasaurios --public \
  --description "ICPC team notebook — Artigasaurios (ORT Uruguay)" \
  --source . --remote origin --push
```

- [ ] **Step 4: Verify CI went green**

Run: `gh run watch` (or `gh run list --limit 1`)
Expected: the `build` workflow succeeds. If TeX Live in CI lacks a package the local build has, add it to the install list and push a fix.

- [ ] **Step 5: Report to the user**

State: the repo URL, the page count, the count of snippets ported per chapter, the CI advisory compile numbers, and the fact that every snippet is marked `Status: untested` and nothing was compile-verified.

---

## Self-Review Notes

**Spec coverage:** every spec section maps to a task — repo/build architecture → Tasks 1, 13; chapter taxonomy → Tasks 3–12; snippet format → the chapter cycle Step 3; build and verification → Tasks 1, 13; risks (shell-escape, page count) → Tasks 1 Step 9, 13 Step 1, 14 Step 2. Out-of-scope items (stress tests, new KACTL staples, geometry reconciliation, pruning, org move) have deliberately **no** tasks.

**Naming consistency:** `\nbimport` / `\nbchapter` / `\nbcontentdir` / `\nbref` / `\nberror` / `\nbwarning` are the only macro names used, and Task 1 Step 4 verifies the `.sty` and `.py` agree on them. Make targets `fast` / `notebook` / `clean` / `veryclean` / `showexcluded` are consistent across Tasks 1, 13, 14. There is no `test-compiles` target by design.

**Known deferrals** (deliberate, not placeholders): the ORT logo asset (Task 1 Step 7 documents the swap); `stress-tests/` is not created, per the spec's follow-up list; standalone compilation of the 32 fragment snippets, recorded in `docs/known-issues.md` for a later pass at the team's direction.
