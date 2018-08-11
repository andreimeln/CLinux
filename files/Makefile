.PHONY : all clean

all : envlist getenv putenv

CPP:=gcc
CFLAGS:=-std=c99

envlist : envlist.c
        $(CPP) $(CFLAGS) -o $@ $^

getenv : getenv.c
        $(CPP) -o $@ $^

putenv : putenv.c
        $(CPP) -o $@ $^

clean:
        rm -f envlist getenv putenv


Makefile.files
..PHONY : all clean

all : openclose

openclose : openclose.c
        gcc -o $@ $<

clean:
        rm -f openclose *.o *~
