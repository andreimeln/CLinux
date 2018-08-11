.PHONY : all clean

all : server client

server : server.o sema.o
	gcc -o $@ $^ -lstdc++

client : client.o sema.o
	gcc -o $@ $^ -lstdc++

server.o : server.cpp sema.h
	gcc -c $<

client.o : client.cpp sema.h
	gcc -c $<

sema.o : sema.cpp sema.h
	gcc -c $<

clean :
	rm -f server client *.o *~
