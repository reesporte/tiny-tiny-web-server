default: all

all: utils.o
	cc server.c -o server utils.o

utils.o: utils.c utils.h
	cc utils.c -c

run: all
	./server 8080

clean:
	rm server utils.o