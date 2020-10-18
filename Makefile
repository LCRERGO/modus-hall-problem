CC = clang
CFLAGS = -Wall -pedantic -pthread -g

modus_hall: modus_hall.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean: 
	rm -rf modus_hall *.o

.PHONY: clean
