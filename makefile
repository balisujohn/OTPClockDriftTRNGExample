
all : distribution production

distribution: dis.c cyrand.c
	gcc -o distribution  dis.c cyrand.c  -std=c11 -I. -lm
production: implementation.c cyrand.c
	gcc -o production  implementation.c cyrand.c  -std=c11 -I. -lm

