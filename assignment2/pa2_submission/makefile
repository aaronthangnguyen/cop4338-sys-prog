CC = gcc
CFLAGS = -I. -g -w
DEPS = find.h
SRC = find.c util.c
OBJ = $(SRC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

find: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ) find
