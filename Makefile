CC=gcc
FLAGS=-Wall -Werror

all: *.o
	$(CC) $(FLAGS) $^;

%.o: %.c
	$(CC) $(FLAGS) -c $^;