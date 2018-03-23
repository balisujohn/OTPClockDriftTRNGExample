tester: tester.c truerand.c
	gcc -o tester  tester.c truerand.c -I.
program: implementation.c truerand.c
	gcc -o program  implementation.c truerand.c -I.

