# hash.sh needs a GNU preprocessor. Linux g++ is one; Apple's is not, so pick
# a Homebrew gcc when present. Kept here rather than in hash.sh, which prints
# in the notebook and must stay short enough to retype.
# NB: make predefines CXX = c++, so ?= would never fire. Only override the
# built-in default, never a CXX the user set deliberately.
ifeq ($(origin CXX),default)
CXX := $(shell for c in g++-16 g++-15 g++-14 g++-13 g++; do \
	if command -v $$c >/dev/null 2>&1 && : | $$c -fpreprocessed -dD -E -P -x c++ - >/dev/null 2>&1; \
	then echo $$c; break; fi; done)
endif
export CXX

LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "Artigasaurios ICPC notebook"
	@echo ""
	@echo "	make fast		- build once (quick iteration)"
	@echo "	make notebook		- build properly (two passes)"
	@echo "	make test-compiles	- compile every snippet standalone"
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

test-compiles:
	./scripts/test-compiles.sh

showexcluded: | build
	grep -Rho '\\nbimport[^{]*{[^}]*}' content/ | sed 's/.*{//; s/}//' > build/headers_included
	find ./content -path ./content/tex -prune -o \( -name "*.h" -o -name "*.py" -o -name "*.java" \) -print | grep -vFf build/headers_included || true

.PHONY: help fast notebook clean veryclean showexcluded test-compiles
