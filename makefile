
all : distribution production

distribution: dis.c cyrand.c
	gcc -o distribution  dis.c cyrand.c  -std=c11 -I.
production: implementation.c cyrand.c
	gcc -o production  implementation.c cyrand.c  -std=c11 -I.

