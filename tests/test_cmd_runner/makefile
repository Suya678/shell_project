CC = gcc
CFLAGS = -Wall -Wextra


tst_: tst_cmd_runner.o parser.o cmd_runner.o our_string.o 
	$(CC) $(CFLAGS) tst_cmd_runner.o parser.o cmd_runner.o our_string.o -o tst_cmd_runner

tst_cmd_runner.o: tst_cmd_runner.c ../../headers/*
	$(CC) $(CFLAGS) -c tst_cmd_runner.c -I../../headers -o tst_cmd_runner.o

our_string.o: ../../src/our_string.c ../../headers/*
	$(CC) $(CFLAGS) -c ../../src/our_string.c -I../../headers -o our_string.o

cmd_runner.o: ../../src/cmd_runner.c ../../headers/* 
	$(CC) $(CFLAGS) -c ../../src/cmd_runner.c -I../../headers -o cmd_runner.o

parser.o: ../../src/parser.c ../../headers/* 
	$(CC) $(CFLAGS) -c ../../src/parser.c -I../../headers -o parser.o
clean:
	rm -f tst_cmd_runner *.o

