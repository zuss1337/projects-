#ifndef FUNCS_H
#define FUNCS_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 4999

struct flags {
  int e, i, v, c, l, n, h, s, f, o;
};

void config(regex_t regex, struct flags *flags, char *line);
void checkingFlags(int argc, char **argv, struct flags *flags, char *patternE);
void read_file(struct flags *flags, FILE *fp, regex_t reg, char *file);
void grep_file(struct flags *flags, char *pattern, char *file);
int flagF(char *pattern, char *temp);
void grep(struct flags *flags, int argc, char **argv, char *temp);

#endif