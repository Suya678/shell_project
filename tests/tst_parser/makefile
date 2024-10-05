tst_: tst_parser.o parser.o our_string.o
	gcc tst_parser.o parser.o our_string.o -o tst_parser

tst_parser.o: tst_parser.c ../../headers/*
	gcc -c tst_parser.c -I../../headers -o tst_parser.o

our_string.o: ../../src/our_string.c ../../headers/*
	gcc -c ../../src/our_string.c -I../../headers -o our_string.o

parser.o: ../../src/parser.c ../../headers/* 
	gcc -c ../../src/parser.c -I../../headers -o parser.o
clean:
	rm -f test_parser *.o

