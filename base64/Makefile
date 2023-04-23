base64: queue.o
	gcc -nostdlib -std=c11 -r queue.o base64.c -o base64.o

queue.o:
	gcc -std=c11 -c queue.c

clean:
	rm base64.o	queue.o
