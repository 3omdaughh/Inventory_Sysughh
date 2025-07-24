CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lncurses

SRC=src/main.c src/ui.c src/ins.c src/io.c
INC=-Iinclude

inventory : $(SRC)
	$(CC) $(CFLAGS) -o inventory $(SRC) $(LDFLAGS) $(INC)

clean:
	rm -f inventory *.o

