MAIN=analisador
OBJS=analisador.o parser.o pilha.o tokenizador.o
CFLAGS=-Wall -Wextra -O
CC=gcc

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(MAIN)
