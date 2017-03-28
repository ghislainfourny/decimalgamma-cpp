SCRIPTS=$(wildcard *.sh)
CSVFILES=$(patsubst %.sh,output/%.csv, $(SCRIPTS))

all: $(CSVFILES)

output/%.csv: %.sh
	./$<

clean:
	rm -f $(CSVFILES)
