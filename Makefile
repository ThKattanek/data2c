CC=g++
LD=g++

all: data2c

data2c: main.o
	$(LD) main.o -o data2c

main.o: main.cpp main.h
	$(CC) -c main.cpp

clean:
	rm -f *.o 

fullclean: clean
	rm -f data2c	
