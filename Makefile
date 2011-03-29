CC = gcc
CFLAGS = -Wall
PRG = matrix
SRC = matrix.c

build: clean
	$(CC) $(CFLAGS) $(SRC) -o $(PRG)
clean:
	rm -rf *.o $(PRG) *~