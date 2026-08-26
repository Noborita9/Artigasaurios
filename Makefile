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
