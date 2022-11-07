#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 2048

static char pattern[BUFFERSIZE] = {0};

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

struct option flags[] = {
    {"e", no_argument, 0, 'e'}, {"i", no_argument, 0, 'i'},
    {"v", no_argument, 0, 'v'}, {"c", no_argument, 0, 'c'},
    {"l", no_argument, 0, 'l'}, {"n", no_argument, 0, 'n'},
    {"h", no_argument, 0, 'h'}, {"s", no_argument, 0, 's'},
    {"f", no_argument, 0, 'f'}, {"o", no_argument, 0, 'o'},
};

struct flag {
  int e, i, v, c, l, n, h, s, f, o, anyFlags;
} flag;

void OffOptions() {  // зануляем значения
  flag.e = 0;
  flag.i = 0;
  flag.v = 0;
  flag.c = 0;
  flag.l = 0;
  flag.n = 0;
  flag.h = 0;
  flag.s = 0;
  flag.f = 0;
  flag.o = 0;

  lines.linesCount = 0;
  lines.filesCount = 0;
  lines.emptyLines = 0;
  lines.eCount = 0;
}

#endif  // SRC_GREP_S21_GREP_H_
