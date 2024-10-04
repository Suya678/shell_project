build/jdshell: src/jdshell.o src/our_string.o src/cmd_runner.o src/parser.o 
	gcc src/jdshell.o src/our_string.o src/cmd_runner.o src/parser.o -o builds/jdshell

src/jdshell.o: src/jdshell.c ./headers/*.h
	gcc -c src/jdshell.c -I./headers -o src/jdshell.o

src/our_string.o: src/our_string.c ./headers/our_string.h
	gcc -c src/our_string.c -I./headers -o src/our_string.o

src/cmd_runner.o: src/cmd_runner.c ./headers/cmd_runner.h 
	gcc -c src/cmd_runner.c -I./headers -o src/cmd_runner.o

src/parser.o: src/parser.c ./headers/parser.h 
	gcc -c src/parser.c -I./headers -o src/parser.o

clean:
	rm -f build/jdshell src/*.o

object_clean:
	rm -f src/*.o
