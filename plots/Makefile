SCRIPTS=$(wildcard *.py)
PDFS=$(patsubst %.py,output/%.pdf, $(SCRIPTS))

all: $(PDFS)

output/%.pdf: %.py ../experiments/output/%.csv
	./$<

clean:
	rm -f $(PDFS)
