.PHONY: all clean

CC=g++
CFLAGS=-Wall -Wextra -Werror
SRC_PATH=src

all: clean s21_containers.a

test: clean
	$(CC) $(CFLAGS) tests/tests.cpp -lgtest
	./a.out

clean:
	rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt gcov_main gcov_report
