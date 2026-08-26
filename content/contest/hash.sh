# Hashes a file, ignoring all whitespace and comments. Use for
# verifying that code was correctly typed.
# `cpp -fpreprocessed` is a GNU cpp flag; on macOS the system `cpp` is an
# Apple clang alias that rejects it. Fall back to a GNU cpp binary
# (e.g. from Homebrew's gcc) if the default `cpp` doesn't support it.
# If no working cpp is found, fail loudly instead of silently hashing
# empty input (which produces a confident-looking but meaningless hash).
CPP=cpp
if ! : | $CPP -dD -P -fpreprocessed >/dev/null 2>&1; then
	for c in cpp-16 cpp-15 cpp-14 cpp-13 cpp-12 gcpp; do
		if command -v "$c" >/dev/null 2>&1 && : | "$c" -dD -P -fpreprocessed >/dev/null 2>&1; then
			CPP=$c
			break
		fi
	done
fi
if ! : | $CPP -dD -P -fpreprocessed >/dev/null 2>&1; then
	echo "hash.sh: no GNU cpp found (need 'cpp' supporting -fpreprocessed;" >&2
	echo "  on macOS: brew install gcc). Refusing to emit a bogus hash." >&2
	exit 1
fi

if command -v md5sum >/dev/null 2>&1; then
	MD5=md5sum
elif command -v md5 >/dev/null 2>&1; then
	MD5="md5 -r"
else
	echo "hash.sh: no md5sum or md5 found. Refusing to emit a bogus hash." >&2
	exit 1
fi

$CPP -dD -P -fpreprocessed | tr -d '[:space:]' | $MD5 | cut -c-6
