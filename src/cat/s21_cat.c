#include "s21_cat.h"

void reader(char *argv[], flags *flag) {
  FILE *file = fopen(argv[optind], "r");
  if (file != NULL) {
    int str_count = 1, empty_str_count = 0, last = '\n';
    while (!feof(file)) {
      int ch = fgetc(file);
      if (ch == EOF) break;
      if (flag->s && ch == '\n' && last == '\n') {
        empty_str_count++;
        if (empty_str_count > 1) {
          continue;
        }
      } else {
        empty_str_count = 0;
      }
      if (last == '\n' && ((flag->b && ch != '\n') || flag->n))
        printf("%6d\t", str_count++);
      if (flag->t && ch == '\t') {
        printf("^");
        ch = 'I';
      }
      if (flag->e && ch == '\n') {
        printf("$");
      }
      if (flag->v) {
        if ((ch >= 0 && ch < 9) || (ch > 10 && ch < 32) ||
            (ch > 126 && ch <= 160)) {
          printf("^");
          if (ch > 126) {
            ch -= 64;
          } else {
            ch += 64;
          }
        }
      }
      printf("%c", ch);
      last = ch;
    }
    fclose(file);
  } else {
    // printf("No such file or directory\n");
    exit(1);
  }
}

int parser(int argc, char *argv[], flags *flag) {
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
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      default:
        printf("Wrong flag \n");
        exit(1);
        break;
    }
    if (flag->b && flag->n) flag->n = 0;
  }
  return 0;
}
