CC = gcc
CFLAGS = -Wall
PRG1 = matrix
PRG2 = newmatrix
SRC1 = matrix.c
SRC2 = newmatrix.c

old: clean
	$(CC) $(CFLAGS) $(SRC1) -o $(PRG1)
	time ./$(PRG1) out1 3
	diff -B out1 t2_asc_teste/out1_787
	
new: clean
	$(CC) $(CFLAGS) $(SRC2) -o $(PRG2)
	time ./$(PRG2) out2 3
	diff -B out2 t2_asc_teste/out1_787
clean:
	rm -rf *.o $(PRG1) $(PRG2) *~
