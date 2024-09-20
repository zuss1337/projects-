CFLAGS = gcc -c -Wall -Werror -Wextra -std=c11 -g 
LDFLAGS = -lcheck
ifeq ($(shell uname), Linux)
  LINUX_LIBS = -lsubunit -lrt -lpthread -lm
endif

all: s21_string.a

s21_string.a: 
	rm -rf *.o
	rm -rf s21_string.a
	$(CFLAGS) s21_sprintf.c s21_string.c s21_string_class.c
	ar r s21_string.a s21_*.o
	ranlib s21_string.a

test: clean s21_string.a
	gcc -Wall -Werror -Wextra -std=c11 -g unit_tests.c s21_string.a -o check.out $(LDFLAGS) $(LINUX_LIBS)
	./check.out

gcov_report: unit_tests.c s21_*.c
	clear
	gcc -Wall -Werror -Wextra -std=c11 -g  unit_tests.c s21_*.c -o coverage.o  $(LDFLAGS)  $(LINUX_LIBS) -fprofile-arcs -ftest-coverage  
	./coverage.o
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage
	open coverage/index.html


clean:
	rm -rf *.o *.out
	rm -rf *.gcda *.gcno
	rm -rf coverage coverage.info CPPLINT.cfg cpplint.py valgrind-out.txt s21_string.a

rebuild: clean all