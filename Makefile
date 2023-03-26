driver: utilities.o
	gcc -std=c11 ./utilities/utilities.o driver.c -o driver

utilities.o: 
	cd ./utilities && make utilities

clean:
	rm driver & rm ./utilities/utilities.o