driver: set1.o
	gcc -std=c11 ./crypto/set1.o driver.c -o driver

set1.o:
	cd ./crypto && make set1

clean:
	rm driver ; cd ./crypto && make clean
