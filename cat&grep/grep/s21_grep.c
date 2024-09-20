#include "funcs.h"

int main(int argc, char *argv[]) {
  struct flags flags = {0};
  char patternE[BUFFER_SIZE] = {0};
  checkingFlags(argc, argv, &flags, patternE);
  if (argc >= 3) grep(&flags, argc, argv, patternE);
  return 0;
}

void checkingFlags(int argc, char **argv, struct flags *flags, char *patternE) {
  int opt = 0;
  const char *s_options = "e:ivclnhsf:o";
  while ((opt = getopt(argc, argv, s_options)) != -1) {
    switch (opt) {
      case 'e':
        flags->e = 1;
        snprintf(patternE, BUFFER_SIZE, "%s", optarg);
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'f':
        flags->f = 1;
        snprintf(patternE, BUFFER_SIZE, "%s", optarg);
        break;
      case 'o':
        flags->o = 1;
        break;
      default:
        printf("Error\n");
        break;
    }
  }
}

void read_file(struct flags *flags, FILE *fp, regex_t reg, char *file) {
  char text[4999] = {0};

  regmatch_t pmatch[1];
  int line_matches = 0, nline = 1;
  while (fgets(text, BUFFER_SIZE - 1, fp) != NULL) {
    int match = 0;
    int success = regexec(&reg, text, 1, pmatch, 0);
    if (strchr(text, '\n') == NULL) strcat(text, "\n");
    if (success == 0 && !flags->v) match = 1;
    if (success == REG_NOMATCH && flags->v) match = 1;
    if (match && !flags->l && !flags->c && flags->n) printf("%d:", nline);
    if (match && !flags->l && !flags->c && !flags->o) printf("%s", text);
    if (match && flags->o) {
      config(reg, flags, text);
    }
    line_matches += match;
    nline++;
  }
  if (flags->l && line_matches > 0) printf("%s\n", file);
  if (flags->c && !flags->l) printf("%d\n", line_matches);
}

void config(regex_t regex, struct flags *flags, char *line) {
  while (regexec(&regex, line, 0, NULL, 0) == flags->v) {
    char *aux = (char *)calloc(strlen(line) + 1, 1);
    strcpy(aux, line);
    int end = strlen(line);
    while (regexec(&regex, aux, 0, NULL, 0) == flags->v) {
      end--;
      aux[strlen(aux) - 1] = 0;
    }
    aux[strlen(aux)] = line[strlen(aux)];
    int start = 0;
    while (regexec(&regex, aux, 0, NULL, 0) == flags->v && strlen(aux) > 0) {
      start++;
      int j = 0;
      while (aux[j] != 0) {
        aux[j] = aux[j + 1];
        j++;
      }
    }
    start--;
    int i = strlen(aux);
    while (i != 0) {
      aux[i] = aux[i - 1];
      i--;
    }
    aux[0] = line[start];
    printf("%s\n", aux);
    free(aux);
    i = start + 1;
    while (line[i] != 0) {
      line[i - start - 1] = line[i];
      i++;
    }
    line[i - start - 1] = 0;
  }
}

void grep_file(struct flags *flags, char *pattern, char *filename) {
  int cflags = REG_EXTENDED;
  regex_t reg;
  FILE *file;
  file = fopen(filename, "r");
  if (flags->i) cflags = REG_ICASE;
  if (file != NULL) {
    regcomp(&reg, pattern, cflags);
    read_file(flags, file, reg, filename);
    regfree(&reg);
    fclose(file);
  }
}

int flagF(char *pattern, char *filename) {
  FILE *file;
  file = fopen(filename, "r");
  int i = 0;
  if (file != NULL) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
      if (ch == 13 || ch == 10) pattern[i++] = '|';
      if (ch != 13 && ch != 10) pattern[i++] = ch;
    }
  } else {
    printf("error\n");
    i = -1;
  }
  if (pattern[i - 1] == '|') pattern[i - 1] = '\0';
  fclose(file);
  return i;
}

void grep(struct flags *flags, int argc, char **argv, char *buff) {
  char pattern[BUFFER_SIZE] = {0};
  int f_pattern = 0;
  if (!flags->f && !flags->e)
    snprintf(pattern, BUFFER_SIZE, "%s", argv[optind++]);
  if (flags->f) f_pattern = flagF(pattern, buff);
  if (!flags->f && flags->e) snprintf(pattern, BUFFER_SIZE, "%s", buff);
  if (f_pattern != -1) {
    int file_true = 0;
    if (argc - optind > 1) file_true = 1;
    for (int i = optind; i < argc; i++) {
      if (file_true && !flags->h && !flags->l) printf("%s:", argv[i]);
      grep_file(flags, pattern, argv[i]);
    }
  }
}