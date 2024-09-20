CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS := ./s21_grep.c
OBJS := $(SRCS:.c=.o)


EXEC = ./s21_grep

all: s21_grep

s21_grep: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(EXEC)
	rm -f $(OBJS)

clean: 
	rm -f $(OBJS) $(EXEC)  *.out