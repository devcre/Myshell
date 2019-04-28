# Makefile for myshell.c, cat.c, ls.c, mkdir.c

CC = gcc

all: myshell cat ls mkdir

shell : myshell.c
	$(CC) -o $@ $<

ls: ls.c
	$(CC) -o $@ $<

cat: cat.c
	$(CC) -o $@ $<

mkdir: mkdir.c
	$(CC) -o $@ $<

clean:
	rm -f *.o shell
