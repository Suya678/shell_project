tst_cmd_handler: tst_cmd_handler.o cmd_handler.o our_string.o
	gcc tst_cmd_handler.o cmd_handler.o our_string.o -o tst_cmd_handler

tst_cmd_handler.o: tst_cmd_handler.c ../../headers/*
	gcc -c tst_cmd_handler.c -I../../headers -o tst_cmd_handler.o

our_string.o: ../../src/our_string.c ../../headers/*
	gcc -c ../../src/our_string.c -I../../headers -o our_string.o

cmd_handler.o: ../../src/cmd_handler.c ../../headers/* 
	gcc -c ../../src/cmd_handler.c -I../../headers -o cmd_handler.o
clean:
	rm -f test_cmd_handler *.o

