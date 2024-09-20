#include "func.h"

int main(int argc, char *argv[]) {
  int b_flag = 0, e_flag = 0, n_flag = 0, s_flag = 0, t_flag = 0, v_flag = 0;
  int error = 0;
  int linenumber = 1;
  int opredelitel = 0;
  int nachalniy_index =
      parse(argc, argv, &b_flag, &e_flag, &n_flag, &s_flag, &t_flag, &v_flag);
  if (nachalniy_index == -1) {
    error = 1;
  } else {
    error = search(argc, argv, nachalniy_index, &linenumber, &opredelitel,
                   b_flag, e_flag, n_flag, s_flag, t_flag, v_flag);
  }
  return error;
}

int parse(int argc, char *argv[], int *b_flag, int *e_flag, int *n_flag,
          int *s_flag, int *t_flag, int *v_flag) {
  int error = 0;
  int i;
  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-') {
        if (strcmp(argv[i], "--number-nonblank") == 0) {
          *b_flag = 1;
        } else if (strcmp(argv[i], "--number") == 0) {
          *n_flag = 1;
        } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
          *s_flag = 1;
        } else {
          error = -1;
          break;
        }
      } else {
        for (int j = 1; argv[i][j] != '\0'; j++) {
          switch (argv[i][j]) {
            case 'b':
              *b_flag = 1;
              break;
            case 'e':
              *e_flag = 1;
              *v_flag = 1;
              break;
            case 'E':
              *e_flag = 1;
              break;
            case 'n':
              *n_flag = 1;
              break;
            case 's':
              *s_flag = 1;
              break;
            case 't':
              *t_flag = 1;
              *v_flag = 1;
              break;
            case 'T':
              *t_flag = 1;
              break;
            case 'v':
              *v_flag = 1;
              break;
            default:
              error = -1;
              break;
          }
          if (error) break;
        }
      }
    }
    if (error) {
      printf("error flag\n");
      return error;
    } else {
      return i;
    }
  }
  return argc;
}

int search(int argc, char *argv[], int nachalniy_index, int *linenumber,
           int *opredelitel, int b_flag, int e_flag, int n_flag, int s_flag,
           int t_flag, int v_flag) {
  int error = 0;
  *linenumber = 1;
  if (nachalniy_index < argc) {
    for (int i = nachalniy_index; i < argc; i++) {
      if (argv[i][0] != '-') {
        if (print(argv[i], linenumber, opredelitel, b_flag, e_flag, n_flag,
                  s_flag, t_flag, v_flag) != 0) {
          error = 1;
          break;
        }
      }
    }
  } else {
    printf("no file\n");
    error = 1;
  }
  return error;
}

int print(char *filename, int *linenumber, int *opredelitel, int b_flag,
          int e_flag, int n_flag, int s_flag, int t_flag, int v_flag) {
  FILE *file = fopen(filename, "r");
  int error = 0;
  if (file == NULL) {
    printf("EMPTY\n");
    error = 1;
  } else {
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
      if (b_flag) {
        flag_b_realiz(line, linenumber);
      } else if (v_flag) {
        flag_v_realiz(line, t_flag, e_flag);
      } else if (e_flag) {
        flag_e_realiz(line);
      } else if (n_flag) {
        flag_n_realiz(line, linenumber);
      } else if (s_flag) {
        flag_s_realiz(line, opredelitel);
      } else if (t_flag) {
        flag_t_realiz(line);
      } else if (v_flag) {
      } else {
        printf("%s", line);
        continue;
      }
    }
    fclose(file);
  }
  return error;
}

void flag_b_realiz(char *line, int *linenumber) {
  if (line[0] != '\n') {
    printf("%6d\t%s", (*linenumber)++, line);
  } else {
    printf("%s", line);
  }
}

void flag_e_realiz(char *line) {
  size_t len = strlen(line);
  if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
    printf("%s$\n", line);
  } else {
    printf("%s\n", line);
  }
}

void flag_n_realiz(char *line, int *linenumber) {
  printf("%6d\t%s", (*linenumber)++, line);
}

void flag_s_realiz(char *line, int *opredelitel) {
  if (line[0] == '\n') {
    if (*opredelitel == 0) {
      printf("%s", line);
      *opredelitel = 1;
    }
  } else {
    printf("%s", line);
    *opredelitel = 0;
  }
}

void flag_t_realiz(char *line) {
  for (int i = 0; line[i] != '\0'; i++) {
    if (line[i] == '\t') {
      printf("^I");
    } else {
      putchar(line[i]);
    }
  }
}

void flag_v_realiz(char *line, int t_flag, int e_flag) {
  for (int i = 0; line[i] != '\0'; i++) {
    unsigned char ch = line[i];
    if (ch == '\n') {
      if (e_flag) {
        printf("$");
      }
      printf("\n");
    } else if (ch == '\t') {
      if (t_flag) {
        printf("^I");
      } else {
        printf("\t");
      }
    } else if ((int)ch <= 31) {
      printf("^%c", ch + 64);
    } else if ((int)ch == 127) {
      printf("^?");
    } else if ((int)ch >= 128) {
      printf("M-");
      if ((int)ch < 128 + 32) {
        printf("^%c", ch - 64);
      } else {
        printf("%c", ch - 128);
      }
    } else {
      printf("%c", ch);
    }
  }
}
