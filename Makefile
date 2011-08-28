all: frack

frack: frack.c
	cc -lm -o frack frack.c

clean:
	rm ./frack