driver: base64.o
	gcc -std=c11 ./crypto/base64.o driver.c -o driver

base64.o:
	cd ./crypto && make base64

clean:
	rm driver ; cd ./crypto && make clean
