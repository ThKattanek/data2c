CC=g++
LD=g++

install: all
	mv data2c /usr/local/bin

all: data2c

data2c: main.o
	$(LD) main.o -o data2c

main.o: main.cpp main.h
	$(CC) -c main.cpp

clean:
	rm -f *.o 

fullclean: clean
	rm -f data2c	
