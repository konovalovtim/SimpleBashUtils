CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: s21_cat

s21_cat: s21_cat.c main.c
	$(CC) $(CFLAGS) -o s21_cat s21_cat.c main.c

python:
	python3 ../../materials/linters/cpplint.py --extensions=c s21_cat.c s21_cat.h main.c

leaks:
	leaks -atExit -- ./s21_cat

clean:
	rm -rf s21_cat

rebuild: clean all