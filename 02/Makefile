CFLAGS:=-std=c11 -I../extern -D__STDC_WANT_LIB_EXT2__=1

.PHONY: clean

#all: part1 part2
all: part1

part%: part%.c
	$(CC) $(CFLAGS) -o$@ $^

clean:
	rm -rf part1 part2
