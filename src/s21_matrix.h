#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define ERR_MATRIX 1  // Ошибка, некорректная матрица;
#define ERR_CALC \
  2  // Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
     // нельзя провести вычисления и т. д.).

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// основные функции
int s21_create_matrix(int rows, int columns,
                      matrix_t *result);      // создание матриц
void s21_remove_matrix(matrix_t *A);          // очистка матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);  // сравнение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  // сложение матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  // вычитание матриц
int s21_mult_number(matrix_t *A, double number,
                    matrix_t *result);  // умножение матрицы на число
int s21_mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result);  // умножение матрицы на матрицу
int s21_transpose(matrix_t *A, matrix_t *result);  // транспонирование
int s21_calc_complements(
    matrix_t *A,
    matrix_t *result);  // минор и матрица алгебраических дополнений
int s21_determinant(matrix_t *A, double *result);  // определитель
int s21_inverse_matrix(matrix_t *A, matrix_t *result);  // обратная матрица
void find_minor(double **A, double **help, int delete_row, int delete_col,
                int size);
double determinant(matrix_t *A, int size);

#endif