.PHONY : all clean

all : myfuse

CFLAGS:=-D_FILE_OFFSET_BITS=64

LIBS:=-lfuse

myfuse : myfuse.c
	gcc $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f myfuse
