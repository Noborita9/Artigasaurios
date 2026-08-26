# Hashes a file, ignoring all whitespace and comments. Use for
# verifying that code was correctly typed.
# `cpp -fpreprocessed` is a GNU cpp flag; on macOS the system `cpp` is an
# Apple clang alias that rejects it. Fall back to a GNU cpp binary
# (e.g. from Homebrew's gcc) if the default `cpp` doesn't support it.
CPP=cpp
if ! : | $CPP -dD -P -fpreprocessed >/dev/null 2>&1; then
	for c in cpp-16 cpp-15 cpp-14 cpp-13 cpp-12 gcpp; do
		if command -v "$c" >/dev/null 2>&1 && : | "$c" -dD -P -fpreprocessed >/dev/null 2>&1; then
			CPP=$c
			break
		fi
	done
fi
$CPP -dD -P -fpreprocessed | tr -d '[:space:]'| md5sum |cut -c-6
