CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: s21_grep

s21_grep: s21_grep.c
	$(CC) $(CFLAGS) -o s21_grep s21_grep.c

python:
	python3 ../../materials/linters/cpplint.py --extensions=c s21_grep.c s21_grep.h

leaks: 
	leaks -atExit -- ./s21_grep -i R test_6_grep.txt

clean:
	rm -rf s21_grep

rebuild: clean all