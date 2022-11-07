#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <errno.h>

#include <getopt.h>

typedef struct flag {
  int b, e, n, s, t, v;
} flags;

int parser(int argc, char *argv[], flags *flag);
void reader(char *argv[], flags *flag);

#endif  //  SRC_CAT_S21_CAT_H_
