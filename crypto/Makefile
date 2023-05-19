base64: queue.o utils.o
	gcc -nostdlib -std=c11 -r queue.o utils.o base64.c -o base64.o

queue.o:
	gcc -std=c11 -c queue.c

utils.o:
	gcc -std=c11 -c utils.c

clean:
	rm *.o
