test_our_string: tst_our_string.o our_string.o
	gcc tst_our_string.o our_string.o -o test_our_string

tst_our_string.o: tst_our_string.c ../../headers/*
	gcc -c tst_our_string.c -I../../headers -o tst_our_string.o

our_string.o: ../../src/our_string.c ../../headers/* 
	gcc -c ../../src/our_string.c -I../../headers -o our_string.o
clean:
	rm -f test_our_string *.o

