CC = gcc
CFLAGS = -I. -g -w
DEPS = hash.h
OBJ = main.o hashmap.o hashset.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

discussion9: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)