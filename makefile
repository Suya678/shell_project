build/jdshell: src/jdshell.o src/our_string.o src/cmd_handler.o
	gcc src/jdshell.o src/our_string.o src/cmd_handler.o -o builds/jdshell

src/jdshell.o: src/jdshell.c ./headers/*.h
	gcc -c src/jdshell.c -I./headers -o src/jdshell.o

src/our_string.o: src/our_string.c ./headers/our_string.h
	gcc -c src/our_string.c -I./headers -o src/our_string.o

src/cmd_handler.o: src/cmd_handler.c ./headers/cmd_handler.h 
	gcc -c src/cmd_handler.c -I./headers -o src/cmd_handler.o
clean:
	rm -f build/jdshell src/*.o

object_clean:
	rm -f src/*.o
