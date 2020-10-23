CC = gcc
CFLAGS = -Wall -pedantic -pthread -g

modus_hall: modus_hall.c lcg.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.o: .c
	$(CC) $^ -c $(CFLAGS) $(LIBS)

clean: 
	rm -rf modus_hall *.o *.exe

.PHONY: clean
