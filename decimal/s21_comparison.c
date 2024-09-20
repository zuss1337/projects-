#include "s21_decimal.h"

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int flag = 1;  // Предполагаем, что числа равны (TRUE)
  int sign1 = (num1.bits[3] >> 31) & 0b1;
  int sign2 = (num2.bits[3] >> 31) & 0b1;

  // Если знаки разные, числа не равны
  if (sign1 != sign2) {
    flag = 0;  // FALSE
  } else {
    // Сравниваем мантиссы (числа без учета знака)
    for (int i = 2; i >= 0; i--) {
      if (num1.bits[i] != num2.bits[i]) {
        flag = 0;  // FALSE
        break;
      }
    }
  }

  return flag;
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  int flag = !s21_is_equal(num1, num2);
  return flag;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;

  if (s21_getSign(value_1) != s21_getSign(value_2)) {
    if (s21_getSign(value_1) == 1 && s21_getSign(value_2) == 0) {
      result = 1;
    } else if (s21_getSign(value_1) == 0 && s21_getSign(value_2) == 1) {
      result = 0;
    }
  } else {
    s21_normalization(&value_1, &value_2, -1);

    for (int i = 127; i >= 0 && result == 0; i--) {
      if (s21_getSign(value_1) == 0 &&
          s21_getBit(value_1, i) < s21_getBit(value_2, i)) {
        result = 1;
      } else if (s21_getSign(value_1) == 0 &&
                 s21_getBit(value_1, i) > s21_getBit(value_2, i)) {
        result = 0;
        break;
      } else if (s21_getSign(value_1) == 1 &&
                 s21_getBit(value_1, i) > s21_getBit(value_2, i)) {
        result = 1;
      } else if (s21_getSign(value_1) == 1 &&
                 s21_getBit(value_1, i) < s21_getBit(value_2, i)) {
        result = 0;
        break;
      }
    }
  }

  return result;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) == 0 &&
                 s21_is_equal(value_1, value_2) == 0
             ? 1
             : 0;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) == 1 ||
                 s21_is_less(value_1, value_2) == 0
             ? 1
             : 0;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) == 1 ||
                 s21_is_less(value_1, value_2) == 1
             ? 1
             : 0;
}
