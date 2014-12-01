TARGET=paper

all:
	pdflatex $(TARGET).tex
	pdflatex $(TARGET).tex

view: all
	xpdf $(TARGET).pdf

clean:
	rm $(TARGET).{pdf,aux,log,out,toc}

