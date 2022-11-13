#include "s21_grep.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    OffOptions();
    parser(argc, argv);
    reader(argc, argv);
  }
  return 0;
}

void parser(int argc, char **argv) {
  int opt;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", 0, 0)) != -1) {
    switch (opt) {
      case 'e':
        flag.e = ON;
        lines.eCount++;
        flagE();
        break;
      case 'i':
        flag.i = ON;
        break;
      case 'v':
        flag.v = ON;
        break;
      case 'c':
        flag.c = ON;
        break;
      case 'l':
        flag.l = ON;
        break;
      case 'n':
        flag.n = ON;
        break;
      case 'h':
        flag.h = ON;
        break;
      case 's':
        flag.s = ON;
        break;
      case 'f':
        flag.f = ON;
        flagF();
        break;
      case 'o':
        flag.o = ON;
        break;
      default:
        exit(EXIT_FAILURE);
    }
    if (flag.v && flag.o) flag.o = OFF;
    if (flag.v && flag.c) flag.o = OFF;
  }
  if (!flag.e && !flag.f) strcat(pattern, argv[optind++]);
}

void reader(int argc, char *argv[]) {
  lines.filesCount = argc - optind;
  while (optind < argc) {
    FILE *file = fopen(argv[optind], "r");
    if (file != NULL) {
      output(argv, file);
      fclose(file);
    } else if (!flag.s) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n",
              argv[optind]);
    }
    ++optind;
  }
}

void flagE() {
  if (lines.eCount > 1) {
    strcat(pattern, "|");
  }
  strcat(pattern, optarg);
}

void flagF() {
  FILE *file = NULL;
  char buffer[BUFFERSIZE] = {OFF};
  if ((file = fopen(optarg, "r"))) {
    while (fgets(buffer, BUFFERSIZE, file) != NULL) {
      if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = 0;
      }
      if (lines.eCount > 0) {
        strcat(pattern, "|");
      }
      if (*buffer == '\0') {
        lines.emptyLines = 1;
        strcat(pattern, ".");
      } else {
        strcat(pattern, buffer);
      }
      lines.eCount++;
    }
    fclose(file);
  } else {
    printf("s21_grep: No such file or directory\n");
    exit(EXIT_FAILURE);
  }
}

void output(char *argv[], FILE *file) {
  regex_t regex;
  int cflags = REG_EXTENDED;
  char buffer[BUFFERSIZE];
  regmatch_t regmatch[1] = {0};
  size_t file_lines_count = 1;
  lines.linesCount = 0;
  if (flag.i) cflags = REG_ICASE;
  regcomp(&regex, pattern, cflags);
  while (!feof(file)) {
    if (fgets(buffer, BUFFERSIZE, file)) {
      int is_new_line = 1;
      int status = regexec(&regex, buffer, 1, regmatch, 0);
      if (flag.v) status = status ? OFF : ON;
      if (status != REG_NOMATCH) {
        if (!flag.c && !flag.l) {
          if (!flag.h && lines.filesCount > 1) printf("%s:", argv[optind]);
          if (flag.n) printf("%lu:", file_lines_count);
          if (flag.o && !flag.v) {
            is_new_line = 0;
            char *ptr = buffer;
            while (!status) {
              printf("%.*s\n", (int)(regmatch[0].rm_eo - regmatch[0].rm_so),
                     ptr + regmatch[0].rm_so);
              ptr += regmatch[0].rm_eo;
              status = regexec(&regex, ptr, 1, regmatch, REG_NOTBOL);
            }
          }
          if (!flag.o) printf("%s", buffer);
          if (buffer[strlen(buffer) - 1] != '\n' && is_new_line) printf("\n");
        }
        lines.linesCount++;
      }
      file_lines_count++;
    }
  }
  if (flag.c) {
    if (!flag.h && lines.filesCount > 1) printf("%s:", argv[optind]);
    if (flag.l && lines.linesCount) {
      printf("1\n");
    } else {
      printf("%d\n", lines.linesCount);
    }
  }
  if (flag.l && lines.linesCount) printf("%s\n", argv[optind]);
  regfree(&regex);
}
