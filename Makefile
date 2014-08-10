# Very simple Makefile
CFLAGS=-Wall -ansi -pedantic

getline: getline.c
	gcc $(CFLAGS) -o $@ $<
