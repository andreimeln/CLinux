.PHONY: all clean

all : envlist getenv putenv

CPP:=gcc
CFLAGS:=-std=c99

envlist: envlist.c
	$(CPP) $(FLAGS) -o $@ $^

getenv : getenv.c
	$(CPP) -o $@ $^

putenv: putenv.c
	$(CPP) -o $@ $^

clean:
	rm -f envlist getenv putenv *.o *~
