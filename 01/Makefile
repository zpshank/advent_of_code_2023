CFLAGS:=-std=c11 -I../extern -D__STDC_WANT_LIB_EXT2__=1

.PHONY: clean

all: part1 

part1: part1.c
	$(CC) $(CFLAGS) -o$@ $^

clean:
	rm -rf part1 part2
