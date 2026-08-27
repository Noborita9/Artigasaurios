# Artigasaurios

The ICPC team reference notebook for **Artigasaurios** — Joaquin Bonora, Juan Manuel
Duarte and Nahuel Zeballos, ORT Uruguay.

It succeeds [Dividimos y no Conquistamos](https://github.com/Noborita9/Dividimos-y-no-Conquistamos),
rebuilt on [KACTL](https://github.com/kth-competitive-programming/kactl)'s organization
and build system. Every snippet is printed with a description, a time complexity, and a
six-character content hash you can check against what you typed during a contest.

## Building

```sh
make notebook        # two passes, so the table of contents settles
make fast            # one pass, for quick iteration
make test-compiles   # every snippet must compile standalone
make showexcluded    # headers no chapter.tex imports
```

The result is `notebook.pdf`. It is **not** committed — CI builds it on every push to
`main` and publishes it as a release, so the current build is always one click away:

**[Download the latest notebook.pdf](https://github.com/Noborita9/Artigasaurios/releases/latest/download/notebook.pdf)**

That link never changes -- GitHub resolves it to whichever build is newest.

Every push to `main` also publishes its own numbered release (`v1`, `v2`, ...), so you can
fetch the exact PDF your team carried to a given contest rather than only the current one.
The twenty most recent builds are kept. Each CI run additionally attaches the PDF as an
artifact if you need a build from a branch.

### Requirements

- A TeX distribution with `pdflatex` and the `extreport` class
  (`texlive-latex-extra` on Debian/Ubuntu, MacTeX on macOS).
- Python 3, for the source preprocessor.
- **`-shell-escape` must be enabled.** The build calls the preprocessor through
  `\write18`. If your distribution restricts it, the build fails with an error that
  does not name the cause — that is the first thing to check.
- **On macOS you need GNU gcc for the content hashes**: `brew install gcc`. Apple's
  compiler rejects `-fpreprocessed`. The `Makefile` finds a `g++-NN` automatically for
  builds; to run `hash.sh` by hand there, set `CXX=g++-16`. On Ubuntu and Git Bash it
  works as-is. `hash.sh` fails loudly rather than printing a wrong hash.
- The `upquote` package and `T1` font encoding, so code prints straight `'` rather than
  a typographic `’`. Both come with `texlive-latex-recommended`. Without them, code
  copied off the page is invalid as typed.

## Verifying a snippet during a contest

Each snippet prints a six-character hash of its own code. Comments and all whitespace are
ignored, so only the tokens matter — skip the comments and indent however you like.

1. Type the snippet into its own file, `Dijkstra.cpp`, containing **nothing else**. No
   `#include`, no template, no `main`; any extra token changes the hash.
2. Hash it and compare to the page:

```sh
h Dijkstra.cpp              # helper in content/contest/.bashrc
sh hash.sh < Dijkstra.cpp   # the same thing
```

3. Only once it matches, read it into your solution (`:r Dijkstra.cpp` in vim) and *then*
   adapt it. Adapt first and the hash can never match.

A mismatch tells you *that* you mistyped, not where — there is nothing to bisect against.
Check the printed line count first, then re-read the dense lines. For a long snippet,
hash it before you start editing, so the failure surface stays small.

If it prints an error instead of a hash, that is deliberate: it refuses to emit a
hash-shaped string it cannot compute. A check that always passes is worse than no check.

## Layout

```
content/
  notebook.tex          document root; lists the chapters in print order
  tex/
    notebook.sty        3-column layout and the \nbimport machinery
    preprocessor.py     parses doc headers, strips comments, computes hashes
  contest/              template, shell setup, hash.sh, troubleshooting
  data-structures/  graph/  dp/  strings/
  number-theory/  numerical/  combinatorial/  geometry/  various/  appendix/
scripts/test-compiles.sh  compiles every snippet standalone
docs/known-issues.md      what is fixed, what is not, and what is untested
```

Each chapter directory holds a `chapter.tex` that lists its files, and that file is the
single source of truth for what gets printed. There is deliberately no index in this
README — the predecessor kept one by hand and it drifted out of sync.

## Adding a snippet

1. Create `content/<chapter>/YourThing.h` with a doc header:

```cpp
/**
 * Author: Your Name
 * Date: 2026-08-26
 * License: CC0
 * Source: where it came from, or "folklore"
 * Description: What it does, what it returns, and any indexing convention.
 * Time: O(N \log N)
 * Status: untested
 */
#pragma once
```

`Author` and `Description` are required — omit either and the build fails.
`Time` is LaTeX math. **If you are not sure of the bound, write `Time: unknown`**
rather than guessing; a wrong bound in a notebook misleads someone under time pressure.

   Add a `Usage:` line naming anything the caller must define. If the snippet needs
   declarations to compile standalone, put them in a deps block with `// exclude-line`
   on each line so they never reach the page or the hash.

2. Add `\nbimport{YourThing.h}` to that chapter's `chapter.tex`.
   Raw LaTeX files use `\input{content/<chapter>/file.tex}` instead.
3. `make showexcluded` — it should list only `content/contest/template.java`.
   Anything else means you added a file and forgot to import it.
4. `make fast` and check the page.

## Conventions

Snippets are written against the macros in `content/contest/template.cpp` —
`L(i,j,n)`, `SZ(x)`, `ALL(x)`, `vec`, `pb`, `eb`, `ll`, `ld`. This is deliberately
**not** KACTL's `rep`/`sz`/`all`/`vi` dialect: the code is ours and so is the muscle
memory. We adopted KACTL's machinery, not its idiom.

Every snippet compiles on its own — `make test-compiles` enforces it and CI fails the
build otherwise. Where a snippet needs solution-level declarations to do that, they sit
in a block marked `exclude-line`, which keeps them in the file for the compiler while
dropping them from both the printed page and the content hash:

```cpp
// --- deps (drop what your solution already defines) --- // exclude-line
const int N = 2e5 + 5; // exclude-line
// ------------------------------------------------------ // exclude-line
```

So you never see or type them. What the snippet needs is stated in its `Usage:` field
instead, which does print — for example `Define: const int N; vec<int> G[N].`

Compiling is not correctness: every snippet is still `Status: untested` and there are
no stress tests. See [docs/known-issues.md](docs/known-issues.md) for what is fixed,
what is still open, and the three snippets that are GCC-only.

## Credits

Build system ported from [KACTL](https://github.com/kth-competitive-programming/kactl)
by KTH Royal Institute of Technology, which is CC0. `notebook.sty` and
`preprocessor.py` are lightly renamed derivatives of theirs; `hash.sh` was rewritten
around `g++ -E` so it runs unmodified on Ubuntu, Git Bash and macOS. This notebook's
contents are ours.

## License

[CC0 1.0 Universal](LICENSE).
