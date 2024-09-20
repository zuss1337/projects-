#include "s21_decimal.h"

// 110000110001 1111111  11111 0
s21_decimal *s21_setBit(s21_decimal *value, int pos_bit, int bit) {
  int elem = value->bits[pos_bit / 32];
  int mask = 1u << (pos_bit % 32);
  if (bit == 1) {
    value->bits[pos_bit / 32] = elem | mask;
  } else if (bit == 0) {
    value->bits[pos_bit / 32] = elem & (~mask);
  }
  return value;
}

int s21_getBit(s21_decimal value, int bit) {
  int elem = value.bits[bit / 32];
  int maska = 1u << (bit % 32);
  return !!(elem & maska);
}

int s21_getSign(s21_decimal value) { return s21_getBit(value, 127); }

s21_decimal *s21_setSign(s21_decimal *value, int bit) {
  return s21_setBit(value, 127, bit);
}

int s21_getScale(s21_decimal value) {
  int scale = value.bits[3] & SCALE;
  return scale >> 16;
}

s21_decimal *s21_set_Scale(s21_decimal *value, int scale) {
  if (scale >= 0 /*&& scale <= 28*/) {
    value->bits[3] = value->bits[3] & (~(SCALE));
    value->bits[3] = value->bits[3] | scale << 16;
  }
  return value;
}

int s21_getLastBit(s21_decimal value) {
  int last = -1, bit = 0;
  for (int i = 0; i < 96; i++) {
    bit = s21_getBit(value, i);
    if (bit == 1) {
      last = i;
    }
  }
  return last;
}

s21_decimal *s21_shift_left(s21_decimal *value, int shift, int *status) {
  int size = s21_getLastBit(*value) + 1 + shift;
  int lastbit1, lastbit2;
  if (size > 96) {
    *status = 1;
  } else {
    for (int i = 0; i < shift; i++) {
      lastbit1 = s21_getBit(*value, 31);
      lastbit2 = s21_getBit(*value, 63);
      for (int j = 0; j < 3; j++) {
        value->bits[j] = value->bits[j] << 1;
      }
      if (lastbit1 == 1) {
        value = s21_setBit(value, 32, 1);
      }
      if (lastbit2 == 1) {
        value = s21_setBit(value, 64, 1);
      }
    }
    *status = 0;
  }
  return value;
}

s21_decimal *s21_shift_right(s21_decimal *value, int shift) {
  int firstbit1, firstbit2;
  for (int i = 0; i < shift; i++) {
    firstbit1 = s21_getBit(*value, 32);
    firstbit2 = s21_getBit(*value, 64);
    for (int j = 0; j < 3; j++) {
      value->bits[j] = value->bits[j] >> 1;
    }
    if (firstbit1 == 1) {
      value = s21_setBit(value, 31, 1);
    }
    if (firstbit2 == 1) {
      value = s21_setBit(value, 63, 1);
    }
  }
  return value;
}
void s21_normalization(s21_decimal *value_1, s21_decimal *value_2,
                       int operation) {
  s21_check_exp_28(value_1);
  s21_check_exp_28(value_2);
  int scale1 = s21_getScale(*value_1);
  int scale2 = s21_getScale(*value_2);
  if (scale1 != scale2) {
    s21_set_Scale(value_1, 0);
    s21_set_Scale(value_2, 0);
  }
  if (scale1 > scale2) {
    s21_help_normalization(value_2, value_1, scale2, scale1, operation);
  } else if (scale1 < scale2) {
    s21_help_normalization(value_1, value_2, scale1, scale2, operation);
  }
}

void s21_help_normalization(s21_decimal *value_1, s21_decimal *value_2,
                            int scale1, int scale2, int operation) {
  s21_decimal res, ten;
  int flag_even = -1;
  int status = 0;
  int num = 0;
  s21_tozero(&ten);
  s21_tozero(&res);
  ten.bits[0] = 0b1010;
  res = *value_1;
  for (int i = 0; i < scale2 - scale1 && status == 0; i++) {
    status = s21_mul(res, ten, value_1);
    if (status == 0) {
      res = *value_1;
    } else {
      *value_1 = res;
      num = num - 1;
    }
    num = i;
  }
  if (status != 0) {
    if (operation == 1) {
      if (s21_getBit(*value_1, 0) == 1) {
        flag_even = 1;
      } else {
        flag_even = 0;
      }
    } else if (operation == 2) {
      if (s21_getBit(*value_1, 0) == 1) {
        flag_even = 2;
      } else {
        flag_even = 3;
      }
    }
    s21_bank_round(*value_2, value_2, scale2 - scale1 - num, flag_even);
    scale2 = scale1 + num;
  }
  s21_set_Scale(value_1, scale2);
  s21_set_Scale(value_2, scale2);
}

void s21_tozero(s21_decimal *a) {
  a->bits[0] = a->bits[1] = a->bits[2] = a->bits[3] = 0;
}

void s21_check_exp_28(s21_decimal *value) {
  int scale = s21_getScale(*value);
  if (scale > 28) {
    s21_bank_round(*value, value, scale - 28, -1);
  }
}
//-1
void s21_bank_round(s21_decimal value_1, s21_decimal *result, int round,
                    int flag_add_even) {
  int flag_even = 0;  // если нечетный то нуль
  // flag_add_even нуль если четный
  int scale = s21_getScale(value_1);
  s21_set_Scale(&value_1, 0);
  s21_decimal mod, ten, five;
  s21_tozero(&ten);
  s21_tozero(&five);
  s21_tozero(result);
  *result = value_1;
  ten.bits[0] = TEN;
  for (int i = 0; i < round; i++) {
    flag_even = 0;
    five.bits[0] = FIVE;
    mod = s21_mod(*result, ten, result);
    scale = scale - 1;
    if (s21_getBit(*result, 0) == 0) {
      flag_even = 1;
    }
    if (flag_add_even == 0 || flag_add_even == 1 || flag_add_even == -1 ||
        flag_add_even == -2) {
      if (s21_is_less_or_equal(five, mod) == 1 &&
          ((flag_even == 0 && flag_add_even == -1) ||
           (flag_add_even == 1 && i == round - 1 && flag_even == 1) ||
           (flag_add_even == 0 && i == round - 1 && flag_even == 0) ||
           flag_add_even == -2)) {
        five.bits[0] = ONE;
        s21_add(*result, five, result);
      }
    } else {
      if (!(s21_is_less_or_equal(five, mod) != 1 &&
            ((flag_add_even == 2 && flag_even == 0) ||
             (flag_add_even == 3 && flag_even == 1)))) {
        five.bits[0] = ONE;
        s21_add(*result, five, result);
      }
    }
  }
  s21_set_Scale(result, scale);
}

int scale_right(s21_decimal num) {
  int exp = s21_getscale(num);
  if (exp == 0) {
    // Нельзя уменьшать экспоненту ниже нуля
    return -1;  // Индикация ошибки
  }

  uint64_t reminder = 0;

  for (int i = 2; i >= 0; i--) {
    num.bits[i] += reminder << 32;
    reminder = num.bits[i] % 10;
    num.bits[i] /= 10;
  }

  exp--;

  return reminder;
}