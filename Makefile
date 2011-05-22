all: frack

frack: frack.c
	cc -o frack frack.c

clean:
	rm ./frack