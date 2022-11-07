#include "s21_grep.h"

int main(int argc, char *argv[]) {
  OffOptions();  // зануляем значения
  parser(argc, argv);
  reader(argc, argv);
  return 0;
}

void parser(int argc, char **argv) {
  int opt;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", flags, 0)) != -1) {
    flag.anyFlags = 1;
    switch (opt) {
      case 'e':
        flag.e = 1;
        ++lines.eCount;
        flagE();
        break;
      case 'i':
        flag.i = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 'c':
        flag.c = 1;
        break;
      case 'l':
        flag.l = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'h':
        flag.h = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'f':
        flag.f = 1;
        flagF();
        break;
      case 'o':
        flag.o = 1;
        break;
      default:
        exit(1);
    }
  }
  if (!flag.e && !flag.f) {
    strcat(pattern, argv[optind++]);  // указатель на массив в который будет добавлена строка и из которого будет скопирована строка
    // Возвращает указатель на pattern
  }
}

void reader(int argc, char *argv[]) {
  lines.filesCount = argc - optind;
  while (optind < argc) {
    FILE *file;
    if ((file = fopen(argv[optind], "r")) != NULL) {  // флаг -s
      output(argv, file);
      fclose(file);
    } else if (!flag.s) {
      printf("s21_grep: %s: No such file or directory\n", argv[optind]);
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
  char buffer[BUFFERSIZE] = {0};
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
      ++lines.eCount;
    }
    fclose(file);
  } else {
    printf("File not found\n");
    exit(1);
  }
}

void output(char *argv[], FILE *file) {
  regex_t regex;
  int cflags = REG_EXTENDED;
  char buffer[BUFFERSIZE];  // Массив для строки в файле
  int nmatch = 1;  // Длина структуры regmatch_t,
  // regexec() - Структура, сохраняющая информацию о том, где находится искомая строка
  regmatch_t regmatch[1] = {0};
  int status;  // Результат regexec()
  size_t file_lines_count = 1;
  lines.linesCount = 0;
  if (flag.i) {  // флаг -i
    cflags = REG_ICASE;  // Игнорирование регистра
  }
  regcomp(&regex, pattern, cflags);  // regcomp() - обработка регулярного выражения для regexec()
  while (!feof(file)) {
    if (fgets(buffer, BUFFERSIZE, file)) {
      int is_new_line = 1;
      status = regexec(&regex, buffer, nmatch, regmatch, 0);  //  для сравнения строки, завершающейся null
      if (flag.v) {  //  флаг -v
        status = status ? 0 : 1;
      }
      if (status != REG_NOMATCH) { // если есть совпадения
        if (!flag.c && !flag.l) {
          if (!flag.h && lines.filesCount > 1) {
            printf("%s:", argv[optind]);
          }
          if (flag.n) {  // флаг -n
            printf("%lu:", file_lines_count);
          }
          if (flag.o && !flag.v) {  // флаг -o
            is_new_line = 0;
            char *ptr = buffer;
            while (!status && regmatch[0].rm_eo != regmatch[0].rm_so) {
              printf("%.*s\n", (int)(regmatch[0].rm_eo - regmatch[0].rm_so),
                     ptr + regmatch[0].rm_so);
              ptr += regmatch[0].rm_eo;
              status = regexec(&regex, ptr, nmatch, regmatch, REG_NOTBOL);
            }
          }
          if (!flag.o) {
            printf("%s", buffer);
          }
          if (buffer[strlen(buffer) - 1] != '\n' && is_new_line) {
            printf("\n");
          }
        }
        ++lines.linesCount;
      }
      ++file_lines_count;
    }
  }
  if (flag.c) {  // флаг -c
    if (!flag.h && lines.filesCount > 1) {
      printf("%s:", argv[optind]);
    }
    if (flag.l && lines.linesCount) {
      printf("1\n");
    } else {
      printf("%d\n", lines.linesCount);
    }
  }
  if (flag.l && lines.linesCount) {  // флаг -l
    printf("%s\n", argv[optind]);
    regfree(&regex);
  }
}