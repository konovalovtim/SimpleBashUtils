#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ON 1
#define OFF 0

typedef struct flag {
  int b, e, n, s, t, v;
} flags;

int parser(int argc, char *argv[], flags *flag);
void reader(char *argv[], flags *flag);
char flagV(int ch);
void flagE(char ch);
char flagT(int ch);
int flagS(char ch, char last, int empty_str_count);
int flagB(char ch, char last, int str_count);
int flagN(char last, int str_count);

#endif  //  SRC_CAT_S21_CAT_H_
