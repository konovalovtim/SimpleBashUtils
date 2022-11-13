#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 2048
#define ON 1
#define OFF 0

char pattern[BUFFERSIZE] = {OFF};

void parser(int argc, char* argv[]);
void reader(int argc, char* argv[]);
void flagE();
void flagF();
void output(char* argv[], FILE* file);

struct lines {
  int linesCount;
  int filesCount;
  int emptyLines;
  int eCount;
} lines;

struct flag {
  int e, i, v, c, l, n, h, s, f, o;
} flag;

void OffOptions() {
  flag.e = OFF;
  flag.i = OFF;
  flag.v = OFF;
  flag.c = OFF;
  flag.l = OFF;
  flag.n = OFF;
  flag.h = OFF;
  flag.s = OFF;
  flag.f = OFF;
  flag.o = OFF;

  lines.linesCount = OFF;
  lines.filesCount = OFF;
  lines.emptyLines = OFF;
  lines.eCount = OFF;
}

#endif  // SRC_GREP_S21_GREP_H_
