#include "s21_decimal.h"

int s21_floor(s21_decimal value,
              s21_decimal *result) {  //Округляет указанное Decimal число до
                                      //ближайшего целого числа в сторону
                                      //отрицательной бесконечности.
  int flag = OK;
  int sign = get_sign(value);
  s21_decimal one = {0};
  s21_from_int_to_decimal(1, &one);
  s21_truncate(value, result);
  if (sign == 1 && !s21_is_equal(value, *result)) {
    s21_sub(*result, one, result);
  }
  return flag;
}

int s21_round(
    s21_decimal value,
    s21_decimal *result) {  //Округляет Decimal до ближайшего целого числа.
  int scale = s21_getScale(value);
  int sign = s21_getSign(value);
  s21_setSign(&value, 0);
  s21_bank_round(value, result, scale, -2);
  s21_setSign(result, sign);
  return 0;
}

int s21_truncate(s21_decimal value,
                 s21_decimal *result) {  //Возвращает целые цифры указанного
                                         // Decimal числа; любые дробные цифры
                                         //отбрасываются, включая конечные нули.
  int sign = s21_getSign(value);
  int scale = s21_getScale(value);
  s21_decimal ten;
  s21_tozero(&ten);
  ten.bits[0] = 10;
  *result = value;
  s21_set_Scale(result, 0);
  s21_setSign(result, 0);
  for (int i = 0; i < scale; i++) {
    s21_mod(*result, ten, result);
  }
  if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0) {
    sign = 0;
  }
  s21_setSign(result, sign);
  return 0;
}

int s21_negate(s21_decimal value,
               s21_decimal *result) {  //Возвращает результат умножения
                                       //указанного Decimal на -1.
  int flag = OK;
  *result = value;
  result->bits[3] ^= 1 << 31;  //выполняется побитовое XOR
  return flag;
}