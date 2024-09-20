#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse(int argc, char *argv[], int *b_flag, int *e_flag, int *n_flag,
          int *s_flag, int *t_flag, int *v_flag);
int search(int argc, char *argv[], int start_index, int *line_number,
           int *was_empty, int b_flag, int e_flag, int n_flag, int s_flag,
           int t_flag, int v_flag);
int print(char *filename, int *line_number, int *was_empty, int b_flag,
          int e_flag, int n_flag, int s_flag, int t_flag, int v_flag);
void flag_b_realiz(char *line, int *line_number);
void flag_e_realiz(char *line);
void flag_n_realiz(char *line, int *line_number);
void flag_s_realiz(char *line, int *was_empty);
void flag_t_realiz(char *line);
void flag_v_realiz(char *line, int t_flag, int e_flag);

#endif