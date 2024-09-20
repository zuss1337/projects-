#include "s21_matrix.h"

void find_minor(double **A, double **help, int delete_row, int delete_col,
                int size) {
  int m = 0, n = 0;
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      if (row != delete_row && col != delete_col) {
        help[m][n++] = A[row][col];
        if (n == size - 1) {
          n = 0;
          m++;
        }
      }
    }
  }
}

double determinant(matrix_t *A, int size) {
  if (size == 1) return A->matrix[0][0];
  matrix_t help = {0};
  double result = 0;
  s21_create_matrix(size, size, &help);
  for (int sign = 1, x = 0; x < size; x += 1, sign *= (-1)) {
    find_minor(A->matrix, help.matrix, 0, x, size);
    result += sign * A->matrix[0][x] * determinant(&help, size - 1);
  }
  s21_remove_matrix(&help);
  return result;
}
