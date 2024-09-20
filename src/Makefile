CFLAGS = gcc -c -Wall -Werror -Wextra -std=c11 -g 
LDFLAGS = -lcheck
ifeq ($(shell uname), Linux)
  LINUX_LIBS = -lsubunit -lrt -lpthread -lm
endif

all: s21_matrix.a

s21_matrix.a: 
	rm -rf *.o
	rm -rf s21_matrix.a
	$(CFLAGS) *.c 
	ar r s21_matrix.a *.o
	ranlib s21_matrix.a

test: clean s21_matrix.a
	gcc -Wall -Werror -Wextra -std=c11 -g tests/tests.c s21_matrix.a -o test.out $(LDFLAGS) $(LINUX_LIBS)
	./test.out

gcov_report: tests/*.c *.c
	clear
	gcc -Wall -Werror -Wextra -std=c11 -g tests/tests.c *.c -o coverage.o  $(LDFLAGS)  $(LINUX_LIBS) -fprofile-arcs -ftest-coverage  
	./coverage.o
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage
	open coverage/index.html


clean:
	rm -rf *.o *.out
	rm -rf *.gcda *.gcno
	rm -rf coverage coverage.info CPPLINT.cfg cpplint.py valgrind-out.txt s21_matrix.a test

rebuild: clean all
