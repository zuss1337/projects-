CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS := ./s21_cat.c
OBJS := $(SRCS:.c=.o)


EXEC = ./s21_cat

all: s21_cat

s21_cat: $(OBJS)
	$(FORMAT)
	$(CC) $(FLAGS) $(OBJS) -o $(EXEC)
	rm -f $(OBJS)

clean: 
	rm -f $(OBJS) $(EXEC)  