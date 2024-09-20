#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = OK;
  if (rows < 1 || columns < 1 || result == NULL) {
    flag = ERR_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      flag = ERR_MATRIX;
    } else {
      // Цикл выделения памяти под строки
      flag = OK;
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          flag = ERR_MATRIX;
          s21_remove_matrix(result);
          break;
        }
      }
    }
  }

  return flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (A == NULL || B == NULL) {
    flag = FAILURE;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    flag = FAILURE;
  }
  if (flag == SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          flag = FAILURE;
          break;
        }
      }
    }
  }
  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;

  if (A == NULL || B == NULL || result == NULL) {
    flag = ERR_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    flag = ERR_CALC;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
      flag = ERR_MATRIX;
    } else {
      // сложение
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;

  if (A == NULL || B == NULL || result == NULL) {
    flag = ERR_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    flag = ERR_CALC;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
      flag = ERR_MATRIX;
    } else {
      // вычитание
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = OK;
  if (A == NULL || A->rows <= 0 || A->columns <= 0 || result == NULL) {
    flag = ERR_MATRIX;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
      flag = ERR_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = (A->matrix[i][j]) * number;
        }
      }
    }
  }
  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;

  if (A == NULL || B == NULL || result == NULL) {
    flag = ERR_MATRIX;
  } else if (A->columns != B->rows) {
    flag = ERR_CALC;
  } else {
    if (s21_create_matrix(A->rows, B->columns, result) != OK) {
      flag = ERR_MATRIX;
    } else {
      // Умножение
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }
  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = OK;

  if (A == NULL || result == NULL) {
    flag = ERR_MATRIX;
  } else {
    if (s21_create_matrix(A->columns, A->rows, result) != OK) {
      flag = ERR_MATRIX;
    } else {
      // Транспонирование
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }

  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = OK;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    flag = ERR_MATRIX;
  } else if (A->rows != A->columns) {
    flag = ERR_CALC;
  } else {
    flag = s21_create_matrix(A->rows, A->columns, result);
    if (flag == OK) {
      if (A->rows != 1) {
        matrix_t help = {0};
        flag = s21_create_matrix(A->rows - 1, A->columns - 1, &help);
        if (flag == OK) {
          for (int sign = 0, x = 0; x < A->rows; x++) {
            for (int y = 0; y < A->columns; y++) {
              find_minor(A->matrix, help.matrix, x, y, A->rows);
              sign = ((x + y) % 2 == 0) ? 1 : -1;
              result->matrix[x][y] = sign * determinant(&help, A->rows - 1);
            }
          }
          s21_remove_matrix(&help);
        } else {
          s21_remove_matrix(result);
        }
      } else {
        // Для матрицы размером 1x1 комплементарная матрица — это 1
        result->matrix[0][0] = 1;
      }
    }
  }

  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = OK;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    flag = ERR_MATRIX;
  }
  if (A->rows != A->columns) {
    flag = ERR_CALC;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else
    *result = determinant(A, A->rows);
  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = OK;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    flag = ERR_MATRIX;
  } else if (A->rows != A->columns) {
    flag = ERR_CALC;
  } else {
    flag = s21_create_matrix(A->rows, A->rows, result);
    double det = 0;
    flag = s21_determinant(A, &det);
    if (det == 0 || flag != 0) {
      flag = ERR_CALC;
    } else {
      matrix_t help = {0}, help_trans = {0};
      s21_calc_complements(A, &help);
      s21_transpose(&help, &help_trans);
      for (int x = 0; x < A->rows; x += 1) {
        for (int y = 0; y < A->rows; y += 1) {
          result->matrix[x][y] = help_trans.matrix[x][y] / det;
        }
      }

      s21_remove_matrix(&help_trans);
      s21_remove_matrix(&help);
    }
  }
  return flag;
}