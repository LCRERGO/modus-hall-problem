CC = clang
CFLAGS = -O2 -Wall -pedantic -pthread

modus_hall: modus_hall.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean: 
	rm -rf modus_hall *.o

.PHONY: clean
