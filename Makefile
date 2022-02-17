CC=gcc
FLAGS=-g
TRASH=*.o *.out
FILES=*.c

network: $(FILES)
	$(CC) $(FLAGS) $(FILES) -o network;

remove:
	rm $(TRASH)