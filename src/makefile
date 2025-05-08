CC = gcc
CFLAGS = -Wall -I./header
SRCDIR = .
IMPLDIR = c
SRC = $(SRCDIR)/main.c $(wildcard $(IMPLDIR)/*.c)
OBJ = $(SRC:.c=.o)
EXEC = main

.PHONY: all clean run test

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(EXEC)

test: all
	./$(EXEC) test

clean:
	rm -f $(IMPLDIR)/*.o *.o $(EXEC)