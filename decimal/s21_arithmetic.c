#include "s21_decimal.h"

// 1 -
// 0 +

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_tozero(result);
  int status = 0;
  int sign1 = s21_getSign(value_1);
  int sign2 = s21_getSign(value_2);
  int buf = 0;
  int flag = 0;
  int operation = 0;
  if (s21_getScale(value_1) != s21_getScale(value_2) ||
      s21_getScale(value_1) > 28) {
    if (sign1 == sign2) {
      operation = 1;
    } else {
      operation = 2;
    }
    s21_normalization(&value_1, &value_2, operation);
  }
  if (sign1 == 1 && sign2 == 1) {
    flag = 1;
  } else if (sign1 == 0 && sign2 == 1) {
    s21_setSign(&value_2, 0);
    status = s21_sub(value_1, value_2, result);
    flag = 4;
  } else if (sign1 == 1 && sign2 == 0) {
    s21_setSign(&value_1, 0);
    status = s21_sub(value_2, value_1, result);
    flag = 4;
  }
  if (flag != 4) {
    s21_help_add(value_1, value_2, &buf, result);
    if (buf == 1 && s21_getScale(value_1) > 0) {
      s21_help_add_if_dec_is_float(&value_1, &value_2, result);
      buf = 0;
    }
  }
  if (flag == 1) {
    s21_setSign(result, 1);
  }
  s21_set_Scale(result, s21_getScale(value_1));
  if (buf == 1 && flag == 0) {
    status = 1;
  } else if (buf == 1 && flag == 1) {
    status = 2;
  }
  return status;
}

void s21_help_add_if_dec_is_float(s21_decimal *value_1, s21_decimal *value_2,
                                  s21_decimal *result) {
  s21_decimal ten, val1, val2;
  int buf = 0, scale;
  scale = s21_getScale(*value_1);
  s21_set_Scale(value_1, 0);
  s21_set_Scale(value_2, 0);
  s21_tozero(&ten);
  ten.bits[0] = TEN;
  val1 = s21_mod(*value_1, ten, value_1);
  val2 = s21_mod(*value_2, ten, value_2);
  s21_help_add(val1, val2, &buf, result);
  if (s21_is_less_or_equal(ten, *result)) {
    ten.bits[0] = 1;
    s21_help_add(*value_1, ten, &buf, value_1);
    ten.bits[0] = 10;
    s21_help_sub(*result, ten, result);
  }
  ten.bits[0] = FIVE;
  if (s21_is_less_or_equal(ten, *result) &&
      (s21_getBit(*value_1, 0) != s21_getBit(*value_2, 0))) {
    ten.bits[0] = 1;
    s21_help_add(*value_1, ten, &buf, value_1);
  }
  s21_help_add(*value_1, *value_2, &buf, result);
  s21_set_Scale(value_1, scale - 1);
}

void s21_help_add(s21_decimal value_1, s21_decimal value_2, int *buf,
                  s21_decimal *result) {
  int bit1, bit2;
  for (int i = 0; i < 96; i++) {
    bit1 = s21_getBit(value_1, i);
    bit2 = s21_getBit(value_2, i);
    *buf = *buf + bit1 + bit2;
    if (*buf == 0) {
      result = s21_setBit(result, i, 0);
    } else if (*buf == 1) {
      result = s21_setBit(result, i, 1);
      *buf = 0;
    } else if (*buf == 2) {
      result = s21_setBit(result, i, 0);
      *buf = 1;
    } else if (*buf == 3) {
      result = s21_setBit(result, i, 1);
      *buf = 1;
    }
  }
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_tozero(result);
  int status = 0;
  int buf = 0;
  int operation = 0;
  if (s21_getScale(value_1) != s21_getScale(value_2) ||
      s21_getScale(value_1) > 28) {
    if (s21_getSign(value_1) == s21_getSign(value_2)) {
      operation = 2;
    } else {
      operation = 1;
    }
    s21_normalization(&value_1, &value_2, operation);
  }
  s21_decimal val1 = value_1, val2 = value_2;
  int flag = 0;
  int sign1 = s21_getSign(val1);
  int sign2 = s21_getSign(val2);
  if (sign1 == 0 && sign2 == 0) {         // + +
    if (s21_is_less(value_1, value_2)) {  //<
      val1 = value_2;
      val2 = value_1;
      flag = 1;
    }
    s21_help_sub(val1, val2, result);
  } else if (sign1 == 1 && sign2 == 0) {  // - +
    s21_help_add(value_1, value_2, &buf, result);
    flag = 1;
    if (buf > 0) {
      status = 2;
    }
  } else if (sign1 == 0 && sign2 == 1) {  //+ -
    s21_help_add(value_1, value_2, &buf, result);
    if (buf > 0) {
      status = 1;
    }
  } else if (sign1 == 1 && sign2 == 1) {  // - -
    val1 = value_2;
    val2 = value_1;
    s21_setSign(&val1, 0);
    s21_setSign(&val2, 0);
    if (s21_is_less(val1, val2)) {
      val1 = value_1;
      val2 = value_2;
      flag = 1;
    }
    s21_help_sub(val1, val2, result);
  }
  if (flag == 1) {
    s21_setSign(result, 1);
  }
  s21_set_Scale(result, s21_getScale(value_1));
  return status;
}

void s21_help_sub(s21_decimal val1, s21_decimal val2, s21_decimal *result) {
  int bit1 = 0, bit2 = 0, buf = 0;
  for (int i = 0; i < 96; i++) {
    bit1 = s21_getBit(val1, i);
    bit2 = s21_getBit(val2, i);
    if (bit1 - bit2 < 0) {
      for (int j = i; j < 96; j++) {
        buf = s21_getBit(val1, j);
        if (buf == 1) {
          s21_setBit(&val1, j, 0);
          for (int k = j - 1; k >= i; k = k - 1) {
            s21_setBit(&val1, k, 1);
          }
          j = 96;
        }
      }
      bit1 = s21_getBit(val1, i);
      buf = 1;
    }
    buf = buf + bit1 - bit2;
    result = s21_setBit(result, i, buf);
    buf = 0;
  }
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal ten, pow;
  s21_decimal buf;
  s21_tozero(&buf);
  s21_tozero(&ten);
  s21_tozero(&pow);
  pow.bits[0] = ONE;
  s21_tozero(result);
  int status = 0;
  int sign = s21_signmul(&value_1, &value_2);
  s21_setSign(&value_1, 0);
  s21_setSign(&value_2, 0);
  s21_check_exp_28(&value_1);
  s21_check_exp_28(&value_2);
  int scale1 = s21_getScale(value_1);
  int scale2 = s21_getScale(value_2);
  int scale_res = scale1 + scale2;
  int number_of_bits = s21_getLastBit(value_1) + s21_getLastBit(value_2) + 2;
  int flag_ten = s21_mul_ten(value_1, value_2, result);
  if (flag_ten != -1) {
    status = flag_ten;
  } else if (number_of_bits > 96 && scale_res != 0) {
    status = s21_help_mul_big(value_1, value_2, result);
  } else if (scale_res == 0 && number_of_bits > 96) {
    status = 1;
  } else {
    s21_set_Scale(&value_1, 0);
    s21_set_Scale(&value_2, 0);
    s21_help_mul(value_1, &status, result, value_2);
    s21_set_Scale(result, scale_res);
    s21_check_exp_28(result);
  }
  if (sign == 1) {
    result = s21_setSign(result, 1);
  }
  if (status == 1 && sign == 1) {
    status = 2;
  }
  return status;
}

int s21_scale_pow(s21_decimal value) {
  s21_decimal pow, buff;
  s21_tozero(&buff);
  buff.bits[0] = 1;
  s21_tozero(&pow);
  pow.bits[0] = 10;
  int n = 0, status = 0;
  while (s21_is_less_or_equal(buff, value) && status == 0) {
    s21_help_mul(buff, &status, &buff, pow);
    n++;
  }
  n = n - 1;
  return n;
}

void s21_help_mul(s21_decimal value_1, int *status, s21_decimal *result,
                  s21_decimal value_2) {
  s21_decimal res;
  s21_tozero(result);
  s21_decimal *buf = &value_2;
  int nul = 0, bit = 0;
  for (int i = 0; i < 96 && *status == 0; i++) {
    bit = s21_getBit(value_1, i);
    if (bit == 1) {
      s21_shift_left(buf, i - nul, status);
      if (*status == 0) {
        res = *result;
        *status = s21_add(res, *buf, result);
        if (*status != 0) {
          *result = res;
        }
      }
      nul = i;
    }
  }
}

int s21_signmul(s21_decimal *value_1, s21_decimal *value_2) {
  int sign1 = s21_getSign(*value_1);
  int sign2 = s21_getSign(*value_2);
  int sign = 0;
  if ((sign1 == 0 && sign2 == 1) || (sign1 == 1 && sign2 == 0)) {
    sign = 1;
  }
  value_1 = s21_setSign(value_1, 0);
  value_2 = s21_setSign(value_2, 0);
  return sign;
}

int s21_help_mul_big(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int status = 0;
  int flag = 0, powsm;
  s21_decimal ten, pow;
  s21_tozero(&ten);
  s21_tozero(&pow);
  s21_tozero(result);
  int scale1 = s21_getScale(value_1);
  int scale2 = s21_getScale(value_2);
  s21_set_Scale(&value_2, 0);
  s21_set_Scale(&value_1, 0);
  s21_decimal small = value_1, big = value_2;
  if (s21_is_less(value_1, value_2) != 1) {  //<
    big = value_1;
    small = value_2;
    flag = scale1;
    scale1 = scale2;
    scale2 = flag;
    flag = 0;
  }
  ten.bits[0] = TEN;
  pow.bits[0] = 1;
  powsm = s21_scale_pow(big);
  for (int i = 0; i < powsm; i++) {
    s21_help_mul(pow, &flag, &pow, ten);
  }
  status =
      s21_help_help_bif_mul(small, big, powsm, pow, scale1, scale2, result);
  return status;
}

int s21_help_help_bif_mul(s21_decimal value_1, s21_decimal value_2, int powsm,
                          s21_decimal pow, int scale1, int scale2,
                          s21_decimal *result) {
  s21_decimal val_buf, mod, buf_res, ten, buffer;
  int status = 0;
  val_buf = value_1;
  s21_tozero(&ten);
  s21_tozero(result);
  s21_tozero(&buf_res);
  s21_tozero(&mod);
  ten.bits[0] = 10;
  int buf_powsm, local_scale1, flag, buf_scale_buf = 0, trash = 0;
  for (int k = 0; k < powsm; k++) {
    value_1 = val_buf;
    buf_powsm = powsm - k;
    local_scale1 = scale1;
    flag = 0;
    mod = s21_mod(value_2, pow, &buf_res);
    s21_mod(pow, ten, &pow);
    value_2 = mod;
    if (buf_powsm - scale2 > 0) {
      while (buf_powsm - scale2 != 0 && local_scale1 != 0) {
        local_scale1 = local_scale1 - 1;
        buf_powsm = buf_powsm - 1;
      }
      for (int i = 0; i < buf_powsm - scale2 && flag == 0; i++) {
        s21_help_mul(buf_res, &flag, &buf_res, ten);
      }
      status = flag;
      buf_scale_buf = 0;
    } else {
      buf_scale_buf = scale2 - buf_powsm;
    }
    while (s21_getLastBit(value_1) + s21_getLastBit(buf_res) + 2 > 96 &&
           local_scale1 >= 0) {
      s21_mod(value_1, ten, &value_1);
      local_scale1 = local_scale1 - 1;
    }
    if (s21_getLastBit(value_1) + s21_getLastBit(buf_res) + 2 > 96) {
      status = 1;
    }
    s21_help_mul(value_1, &trash, &buffer, buf_res);
    if (trash != 0) {
      status = 1;
    }
    s21_set_Scale(&buffer, local_scale1 + buf_scale_buf);
    trash = s21_add(*result, buffer, result);
    if (trash != 0) {
      status = 1;
    }
    if (status != 0) {
      k = powsm;
    }
  }
  value_1 = val_buf;
  if (s21_getLastBit(value_1) + s21_getLastBit(buf_res) + 2 > 96) {
    s21_mod(value_1, ten, &value_1);
    scale1 = scale1 - 1;
  }
  s21_help_mul(value_1, &trash, &buffer, mod);
  if (trash != 0) {
    status = 1;
  }
  s21_set_Scale(&buffer, scale1 + scale2);
  trash = s21_add(*result, buffer, result);
  if (trash != 0) {
    status = 1;
  }
  return status;
}

int s21_mul_ten(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int powsm = 0;
  int status = 0;
  s21_decimal pow, ten, one;
  s21_tozero(&one);
  one.bits[0] = 1;
  s21_tozero(&ten);
  ten.bits[0] = 10;
  int scale_res = s21_getScale(value_1) + s21_getScale(value_2);
  if (s21_is_equal(one, value_1)) {
    *result = value_2;
    s21_set_Scale(result, scale_res);
  } else if (s21_is_equal(one, value_2)) {
    *result = value_1;
    s21_set_Scale(result, scale_res);
  } else if (s21_ten_funck(value_1, &pow, &powsm) &&
             s21_is_less_or_equal(ten, value_1)) {
    status = s21_help_mul_ten(value_2, powsm, result);
  } else if (s21_ten_funck(value_2, &pow, &powsm) &&
             s21_is_less_or_equal(ten, value_2)) {
    status = s21_help_mul_ten(value_1, powsm, result);
  } else {
    status = -1;
  }
  return status;
}

int s21_help_mul_ten(s21_decimal value, int powsm, s21_decimal *result) {
  int status = 0;
  int scale = s21_getScale(value);
  s21_set_Scale(&value, 0);
  int scale_res = scale - powsm;
  s21_decimal ten;
  s21_tozero(&ten);
  ten.bits[0] = 10;
  *result = value;
  if (scale_res < 0) {
    while (scale_res != 0 && status == 0) {
      s21_help_mul(*result, &status, result, ten);
      scale_res++;
    }
  }
  if (status == 0) {
    s21_set_Scale(result, scale_res);
  }
  return status;
}

int s21_ten_funck(s21_decimal value, s21_decimal *pow, int *powsm) {
  int status = 0;
  s21_decimal ten, mod;
  s21_tozero(&ten);
  s21_tozero(pow);
  s21_tozero(&mod);
  int scale = s21_getScale(value);
  s21_set_Scale(&value, 0);
  ten.bits[0] = 10;
  pow->bits[0] = 1;
  int flag = 0;
  *powsm = s21_scale_pow(value);
  for (int i = 0; i < *powsm; i++) {
    s21_help_mul(*pow, &flag, pow, ten);
  }
  mod = s21_mod(value, *pow, &ten);
  s21_tozero(&ten);
  *powsm = *powsm - scale;
  if (s21_is_equal(mod, ten)) {
    status = 1;
  }
  return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero, mod, res, ten, buf_res;
  s21_tozero(&buf_res);
  s21_tozero(result);
  s21_tozero(&zero);
  s21_tozero(&res);
  s21_tozero(&ten);
  ten.bits[0] = TEN;
  int res_scale = s21_getScale(value_1) - s21_getScale(value_2);
  int status = 0;
  int flag = 0;
  int sign = 0;

  if ((s21_getSign(value_1) == 1 && s21_getSign(value_2) == 0) ||
      (s21_getSign(value_1) == 0 && s21_getSign(value_2) == 1)) {
    sign = 1;
  }
  s21_setSign(&value_1, 0);
  s21_setSign(&value_2, 0);
  s21_set_Scale(&value_1, 0);
  s21_set_Scale(&value_2, 0);
  if (s21_is_equal(zero, value_2)) {
    status = 3;
  } else {
    mod = s21_mod(value_1, value_2, &res);
    s21_help_add(*result, res, &status, result);
    buf_res = *result;
    while (s21_is_equal(zero, mod) != 1 && res_scale < 28 && flag == 0) {
      s21_help_div(&mod, value_2, &res_scale, &flag, result, ten, &buf_res);
      mod = s21_mod(mod, value_2, &res);
      if (flag == 0) {
        s21_help_add(*result, res, &flag, result);
      }
      if (flag == 0) {
        buf_res = *result;
      }
      if (flag != 0 || res_scale == 28) {
        if (s21_help_round_div(mod, res, value_2) == 1 &&
            s21_getBit(buf_res, 0) == 1) {
          ten.bits[0] = 1;
          flag = 0;
          s21_help_add(buf_res, ten, &flag, &buf_res);
          flag = 1;
        }
      }
    }
    s21_help_help_div(res_scale, flag, buf_res, sign, &status, result);
  }
  if (sign == 1) {
    s21_setSign(result, 1);
  }
  return status;
}

void s21_help_help_div(int res_scale, int flag, s21_decimal buf_res, int sign,
                       int *status, s21_decimal *result) {
  s21_decimal ten;
  s21_tozero(&ten);
  if (res_scale < 0 && flag == 0) {
    while (res_scale != 0 && flag == 0) {
      ten.bits[0] = TEN;
      s21_help_mul(ten, &flag, &buf_res, buf_res);
      if (flag == 0) {
        res_scale++;
      }
    }
  }
  if (res_scale < 0 && sign == 0) {
    *status = 1;
  } else if (res_scale < 0 && sign == 1) {
    *status = 2;
  } else {
    *result = buf_res;
    result = s21_set_Scale(result, res_scale);
  }
}

int s21_help_round_div(s21_decimal mod, s21_decimal res, s21_decimal value_2) {
  s21_decimal result, ten, trash;
  s21_tozero(&ten);
  ten.bits[0] = TEN;
  int res_scale = 0;
  int status = 0;
  s21_tozero(&result);
  s21_help_add(result, res, &status, &result);
  for (int i = 0; i < 2; i++) {
    s21_help_div(&mod, value_2, &res_scale, &status, &result, ten, &trash);
    mod = s21_mod(mod, value_2, &res);
    s21_help_add(result, res, &status, &result);
  }
  s21_bank_round(result, &result, 2, -1);
  ten.bits[0] = FIVE;
  if (s21_is_less_or_equal(ten, result) == 1) {
    status = 1;
  } else {
    status = 0;
  }
  return status;
}

void s21_help_div(s21_decimal *mod, s21_decimal value_2, int *res_scale,
                  int *flag, s21_decimal *result, s21_decimal ten,
                  s21_decimal *buf_res) {
  while (s21_is_less(*mod, value_2) && *res_scale < 28 && *flag == 0) {
    s21_help_mul(ten, flag, mod, *mod);
    s21_help_mul(ten, flag, result, *result);
    if (*flag == 0) {
      *buf_res = *result;
      *res_scale = *res_scale + 1;
    }
  }
}

s21_decimal s21_mod(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  s21_decimal buff, buff1, mod;
  int status = 0;
  s21_tozero(result);
  s21_tozero(&mod);
  s21_tozero(&buff);
  s21_tozero(&buff1);
  s21_decimal *buff_one = &buff1;
  int sign_res = 0, sign_mod = 0;
  int sign1 = s21_getSign(value_1);
  int sign2 = s21_getSign(value_2);
  if ((sign1 == 0 && sign2 == 1) || (sign1 == 1 && sign2 == 0)) {
    sign_res = 1;
  }
  if ((sign1 == 1 && sign2 == 1) || (sign1 == 1 && sign2 == 0)) {
    sign_mod = 1;
  }
  s21_setSign(&value_1, 0);
  s21_setSign(&value_2, 0);
  while (s21_is_less_or_equal(value_2, value_1)) {
    s21_tozero(buff_one);
    s21_setBit(buff_one, 0, 1);
    s21_help_funck_littlenumber(&buff, value_1, buff_one, &status, value_2);
    s21_add(*result, *buff_one, result);
    s21_help_mul(value_2, &status, &buff, *buff_one);
    s21_sub(value_1, buff, &value_1);
  }
  if (sign_res == 1) {
    s21_setSign(result, 1);
  }
  if (sign_mod == 1) {
    s21_setSign(&value_1, 1);
  }
  return value_1;
}

void s21_help_funck_littlenumber(s21_decimal *buff, s21_decimal value_1,
                                 s21_decimal *buff_one, int *status,
                                 s21_decimal value_2) {
  int flag = 0;
  int perepoln = 0;
  s21_tozero(buff);
  *status = 0;
  while (s21_is_less_or_equal(*buff, value_1) && perepoln == 0 &&
         *status == 0) {
    if (flag != 0) {
      buff_one = s21_shift_left(buff_one, 1, status);
    }
    if (perepoln == 0 && *status == 0) {
      s21_help_mul(value_2, &perepoln, buff, *buff_one);
    }
    flag = 1;
  }
  buff_one = s21_shift_right(buff_one, 1);
  *status = 0;
}
