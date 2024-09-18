jdshell: jdshell.o usr_input.o
	gcc jdshell.o usr_input.o -o jdshell

jdshell.o: jdshell.c
	gcc -c jdshell.c

usr_input.o: usr_input.c
	gcc -c usr_input.c usr_input.h

clean:
	rm -f jdshell jdshell.o

object_clean:
	rm -f *.o
