all: pdf clean

pdf: 
	pdflatex latex/rapport.tex 
	evince rapport.pdf
	rm -f *.toc *.pdf *.aux *.log *.out

%.pdf: %.tex
	rubber -m pdftex latex/$<

clean:
	rm -f .toc .aux .log .out

cleanall:
	rm -f *.toc *.pdf *.aux *.log *.out

.PHONY: all pdf clean cleanall

.SILENT: pdf
