#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = OK;

  if (dst == NULL) {
    res = FAILURE;
  } else {
    s21_zerobits(dst);  // Обнуляем все биты структуры
    if (src < 0) {
      s21_setbit(dst, 127, 1);  // Устанавливаем знак в 127-й бит
      src = -src;  // Преобразуем в положительное число
    }

    dst->bits[0] = (unsigned int)src;  // Присваиваем значение

    // Остальные биты структуры остаются равными 0, так как они были обнулены
  }

  return res;
}
// int s21_from_int_to_decimal(int src, s21_decimal *dst) {
//   int error = 1;
//   if (dst) {
//     error = 0;
//     s21_tozero(dst);
//     dst->bits[0] = abs(src);
//     if (src < 0) set_sign(dst, 1);
//   }
//   return error;
// }

//////////ЗДЕСЬ ВСЕ ОК ПЕРЕПРОВЕРИЛ ИНТ В ДЕЦИМАЛ

// Функция конвертации decimal в int
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 1;
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = src.bits[0];
    if (get_sign(src)) {
      *dst *= -1;
    }
    *dst /= (int)pow(10, s21_getscale(src));
    error = 0;
  }
  return error;
}

/////////ПРОВЕРИЛ ВСЕ РАБОТАЕТ ХАЙП!!!!!!!!!

// Функция конвертации decimal в float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 1;
  if (dst != NULL) {
    int scale = s21_getscale(src);
    long double tmp = 0;
    for (int i = 0; i < 96; i++) {
      tmp += pow(2, i) * s21_getbit(src, i);
    }
    while (scale > 0) {
      tmp /= 10;
      scale--;
    }
    if (get_sign(src) == 1) {
      tmp *= -1.0;
    }
    *dst = tmp;
    error = 0;
  }
  return error;
}

///// ЗДЕСЬ ВРОДЕ ТОЖЕ ОК

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  if ((src != src) || fabs(src) > max_dec || src == (1.0 / 0.0) ||
      src == -(1.0 / 0.0) || !dst) {
    error = 1;
  }
  if (!error) {
    s21_zerobits(dst);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = fabs(src);
    }

    int temp = (int)src;
    int scale = 0;

    while (src - ((float)temp / (int)(pow(10, scale))) != 0) {
      scale++;
      temp = src * (int)(pow(10, scale));
    }
    s21_from_int_to_decimal(temp, dst);
    if (sign) set_sign(dst, 1);
    s21_set_scale(dst, scale);
  }
  return error;
}
