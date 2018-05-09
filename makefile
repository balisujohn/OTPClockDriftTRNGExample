
all : distribution production source

distribution: dis.c cyrand.c
	gcc -o distribution  dis.c cyrand.c  -std=c11 -I. -lm -fno-loop-optimize  -fno-strength-reduce

production: implementation.c cyrand.c
	gcc -o production  implementation.c cyrand.c  -std=c11 -I. -lm -fno-loop-optimize -fno-strength-reduce

source:   source.c cyrand.c
	gcc -o source  source.c cyrand.c  -std=c11 -I. -lm -fno-loop-optimize -fno-strength-reduce
