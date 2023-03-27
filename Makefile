driver: base64.o
	gcc -std=c11 ./base64/base64.o driver.c -o driver

base64.o:
	cd ./base64 && make base64

clean:
	rm driver ./base64/base64.o