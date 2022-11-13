#include "s21_cat.h"

int parser(int argc, char **argv, flags *flag) {
  int f;
  const char *f_options = "+benstvET";
  static struct option options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((f = getopt_long(argc, argv, f_options, options, NULL)) != -1) {
    switch (f) {
      case 'b':
        flag->b = ON;
        break;
      case 'e':
        flag->e = ON;
        flag->v = ON;
        break;
      case 'n':
        flag->n = ON;
        break;
      case 's':
        flag->s = ON;
        break;
      case 't':
        flag->t = ON;
        flag->v = ON;
        break;
      case 'v':
        flag->v = ON;
        break;
      case 'E':
        flag->e = ON;
        break;
      case 'T':
        flag->t = ON;
        break;
      default:
        exit(EXIT_FAILURE);
        break;
    }
    if (flag->b && flag->n) flag->n = OFF;
  }
  return 0;
}

void reader(char **argv, flags *flag) {
  FILE *file = fopen(argv[optind], "r");
  if (file != NULL) {
    int last = '\n', str_count = 0, empty_str_count = 0;
    while (!feof(file)) {
      int ch = fgetc(file);

      if (ch == EOF) break;
      if (flag->s) {
        if ((empty_str_count = flagS(ch, last, empty_str_count)) > 1) continue;
      }
      if (flag->b) {
        str_count = flagB(ch, last, str_count);
      }
      if (flag->n) {
        str_count = flagN(last, str_count);
      }
      if (flag->t) {
        ch = flagT(ch);
      }
      if (flag->e) {
        flagE(ch);
      }
      if (flag->v) {
        ch = flagV(ch);
      }
      printf("%c", ch);
      last = ch;
    }
    fclose(file);
  } else {
    exit(EXIT_FAILURE);
  }
}

int flagB(char ch, char last, int str_count) {
  if (last == '\n' && ch != '\n') {
    printf("%6d\t", ++str_count);
  }
  return str_count;
}

void flagE(char ch) {
  if (ch == '\n') printf("$");
}

int flagN(char last, int str_count) {
  if (last == '\n') {
    printf("%6d\t", ++str_count);
  }
  return str_count;
}

int flagS(char ch, char last, int empty_str_count) {
  if (ch == '\n' && last == '\n') {
    empty_str_count++;
  } else {
    empty_str_count = 0;
  }
  return empty_str_count;
}

char flagT(int ch) {
  if (ch == '\t') {
    printf("^");
    ch = 'I';
  }
  return ch;
}

char flagV(int ch) {
  if ((ch >= 0 && ch < 9) || (ch > 10 && ch < 32) || (ch > 126 && ch <= 160)) {
    printf("^");
    if (ch > 126) {
      ch -= 64;
    } else {
      ch += 64;
    }
  }
  return ch;
}
