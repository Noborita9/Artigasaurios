#!/usr/bin/env bash
# Compile every content header standalone against the team template.
# Snippets must be self-contained: paste one into a solution and it works.
set -uo pipefail
cd "$(dirname "$0")/.."

CXX=${CXX:-}
if [ -z "$CXX" ]; then
	for c in g++-16 g++-15 g++-14 g++-13 g++; do
		command -v "$c" >/dev/null 2>&1 && { CXX=$c; break; }
	done
fi
[ -n "$CXX" ] || { echo "test-compiles: no C++ compiler found" >&2; exit 1; }

TMP=$(mktemp -d); trap 'rm -rf "$TMP"' EXIT

# Template minus the x86-only perf pragmas (they break on arm64) and minus
# solve()/main(); keeps includes, macros and typedefs.
sed -e '/^#pragma GCC/d' -e '/^void solve/,$d' content/contest/template.cpp > "$TMP/prelude.h"

fail=0; pass=0
while IFS= read -r header; do
	grep -q 'test-compiles: skip' "$header" && continue
	{ cat "$TMP/prelude.h"; echo "#include \"$PWD/$header\""; echo "int main(){}"; } > "$TMP/tu.cpp"
	if err=$("$CXX" -std=c++20 -fsyntax-only -w -I"$PWD" "$TMP/tu.cpp" 2>&1); then
		pass=$((pass+1))
	else
		echo "FAIL $header"
		echo "$err" | grep -E "error:" | head -3 | sed 's/^/      /'
		fail=$((fail+1))
	fi
done < <(find content -name '*.h' | sort)

echo "$pass compile, $fail fail."
[ "$fail" -eq 0 ]
