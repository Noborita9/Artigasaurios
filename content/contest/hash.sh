# Verify a snippet you typed: sh hash.sh < Dijkstra.cpp
# Ignores comments and whitespace. macOS: CXX=g++-16 (brew install gcc).
${CXX:-g++} -fpreprocessed -dD -E -P -x c++ - | tr -d '[:space:]' | md5sum | cut -c-6
