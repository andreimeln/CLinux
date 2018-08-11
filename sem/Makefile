.PHONY : all clean

all : server

server : server.o sema.o
	gcc -o $@ $^ -lstdc++

server.o : server.cpp sema.h
	gcc -c $<

sema.o : sema.cpp sema.h
	gcc -c $<

clean :
	rm -f *.o server *~
