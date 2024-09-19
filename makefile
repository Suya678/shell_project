jdshell: src/jdshell.o src/usr_input.o
	gcc src/jdshell.o src/usr_input.o -o jdshell

src/jdshell.o: src/jdshell.c ./headers/usr_input.h
	gcc -c src/jdshell.c -I./headers -o src/jdshell.o

src/usr_input.o: src/usr_input.c ./headers/usr_input.h 
	gcc -c src/usr_input.c -I./headers -o src/usr_input.o
clean:
	rm -f jdshell src/*.o

