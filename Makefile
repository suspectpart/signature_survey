all: 
	gcc src/sigs.c src/options.c src/survey.c -o sigs 

clean:
	rm -f sigs

install:
	cp sigs /usr/local/bin

uninstall:
	rm -f /usr/local/bin/sigs
