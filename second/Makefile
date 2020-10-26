CC = gcc
CFLAGS = -Wall -pedantic -pthread -g

busywait_modus_hall: busywait_modus_hall.c lcg.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.o: .c
	$(CC) $^ -c $(CFLAGS) $(LIBS)

clean: 
	rm -rf busywait_modus_hall *.o *.exe

.PHONY: clean
