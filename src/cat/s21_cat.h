#ifndef S21_CAT_H_
#define S21_CAT_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <errno.h>
#include <getopt.h>

typedef struct flag {
    int b, e, n, s, t, v;
} flags;

int parser(int argc, char *argv[], flags *flag);
void reader(char *argv[], flags *flag);

#endif