set1: queue.o utils.o
	gcc -nostdlib -std=c11 -r queue.o utils.o set1.c -o set1.o

queue.o:
	gcc -std=c11 -c queue.c

utils.o:
	gcc -std=c11 -c utils.c

clean:
	rm *.o
