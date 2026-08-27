# Hashes a snippet, ignoring comments and all whitespace, so you can check
# what you typed against the notebook. Usage:  sh hash.sh < Dijkstra.cpp
# Needs a GNU preprocessor: `cpp` on Linux, or g++ anywhere else (Git Bash,
# macOS with `brew install gcc`). Apple's cpp rejects -fpreprocessed.
strip() {
	if : | cpp -dD -P -fpreprocessed >/dev/null 2>&1; then cpp -dD -P -fpreprocessed; return; fi
	for c in cpp-16 cpp-15 cpp-14 cpp-13 cpp-12; do
		command -v "$c" >/dev/null 2>&1 && : | "$c" -dD -P -fpreprocessed >/dev/null 2>&1 \
			&& { "$c" -dD -P -fpreprocessed; return; }
	done
	for c in ${CXX:-} g++ g++-16 g++-15 g++-14 g++-13 g++-12; do
		command -v "$c" >/dev/null 2>&1 && : | "$c" -fpreprocessed -dD -E -P -x c++ - >/dev/null 2>&1 \
			&& { "$c" -fpreprocessed -dD -E -P -x c++ -; return; }
	done
	echo "hash.sh: no GNU preprocessor found (need cpp or g++ supporting" >&2
	echo "  -fpreprocessed). macOS: brew install gcc. Refusing to guess." >&2
	exit 1
}
digest() {
	if command -v md5sum >/dev/null 2>&1; then md5sum
	elif command -v md5 >/dev/null 2>&1; then md5 -r
	else echo "hash.sh: no md5sum or md5 found. Refusing to guess." >&2; exit 1; fi
}
strip | tr -d '[:space:]' | digest | cut -c-6
