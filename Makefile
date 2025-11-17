CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2

SOURCES = FreeFire-novato.c FreeFire-aventureiro.c FreeFire-mestre.c
BINS = FreeFire-novato FreeFire-aventureiro FreeFire-mestre

.PHONY: all clean run-novato run-aventureiro run-mestre

all: $(BINS)

FreeFire-novato: FreeFire-novato.c
	$(CC) $(CFLAGS) -o $@ $<

FreeFire-aventureiro: FreeFire-aventureiro.c
	$(CC) $(CFLAGS) -o $@ $<

FreeFire-mestre: FreeFire-mestre.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BINS) *.o

run-novato: FreeFire-novato
	./FreeFire-novato

run-aventureiro: FreeFire-aventureiro
	./FreeFire-aventureiro

run-mestre: FreeFire-mestre
	./FreeFire-mestre
