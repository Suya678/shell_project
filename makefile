jdshell: jdshell.o
	gcc jdshell.o -o jdshell

jdshell.o: jdshell.c
	gcc -c jdshell.c

clean:
	rm -f jdshell jdshell.o

object_clean:
	rm -f *.o
