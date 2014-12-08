TARGET=paper

all:
	pdflatex $(TARGET).tex
	bibtex $(TARGET)
	pdflatex $(TARGET).tex
	pdflatex $(TARGET).tex

view: all
	xpdf $(TARGET).pdf

clean:
	rm $(TARGET).{pdf,aux,log,out,toc,bbl,blg}

