CC=gcc
FLAGS=-Wall -Werror
TRASH=*.o *.out

all: *.o
	$(CC) $(FLAGS) $^;

%.o: %.c
	$(CC) $(FLAGS) -c $^;

remove:
	rm $(TRASH)