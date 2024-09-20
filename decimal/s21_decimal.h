#ifndef _SRC_S21_DECIMAL_H
#define _SRC_S21_DECIMAL_H
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_MAX_UINT 4294967295
#define MAX_DECIMAL 79228162514264337593543950335.0F
#define SCALE 0b11111111 << 16
#define TEN 0b1010
#define FIVE 0b101
#define ONE 0b1

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// узнать бит
int s21_getBit(s21_decimal value, int bit);
// поменять бит
s21_decimal *s21_setBit(s21_decimal *value, int pos_bit, int bit);
// проверяет знак 0 - это плюс 1 - это минус
int s21_getSign(s21_decimal value);
// замена знака
s21_decimal *s21_setSign(s21_decimal *value, int bit);
// возвращает номер последнего единичного бита
int s21_getLastBit(s21_decimal value);
// перемещает биты влево на shift (изменяет status на 1 если переполнен децимал)
s21_decimal *s21_shift_left(s21_decimal *value, int shift, int *status);
// перемещает биты в право
s21_decimal *s21_shift_right(s21_decimal *value, int shift);
// возвращает знак произведения 0 - это плюс 1 - это минус
int s21_signmul(s21_decimal *value_1, s21_decimal *value_2);
// возвращает масштаб
int s21_getScale(s21_decimal value);
// меняет масштаб(надо переправерить)
s21_decimal *s21_set_Scale(s21_decimal *value, int scale);
// привод к общему знаменателю
// и заодно округляет с учетом того какой результат должен получится после
// банковского округления
void s21_normalization(
    s21_decimal *value_1, s21_decimal *value_2,
    int operation);  // операция 1 сложение операция 2 вычитание
//
void s21_help_normalization(s21_decimal *value_1, s21_decimal *value_2,
                            int scale1, int scale2, int operation);
// обнуляет децимал
void s21_tozero(s21_decimal *a);
// банковское округление
void s21_bank_round(s21_decimal value_1, s21_decimal *result, int round,
                    int flag_add_even);
// проверка что степень числа не превышает 28, если превышает то изменяю степень
void s21_check_exp_28(s21_decimal *value);

// сложение
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_help_add(s21_decimal value_1, s21_decimal value_2, int *buf,
                  s21_decimal *result);
void s21_help_add_if_dec_is_float(s21_decimal *value_1, s21_decimal *value_2,
                                  s21_decimal *result);

// разность
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_help_sub(s21_decimal val1, s21_decimal val2, s21_decimal *result);

// умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_help_mul(s21_decimal value_1, int *status, s21_decimal *result,
                  s21_decimal value_2);
int s21_scale_pow(s21_decimal value);
int s21_help_mul_big(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
int s21_help_help_bif_mul(s21_decimal value_1, s21_decimal value_2, int powsm,
                          s21_decimal pow, int scale1, int scale2,
                          s21_decimal *result);
int s21_ten_funck(s21_decimal value, s21_decimal *pow,
                  int *powsm);  // возвращает единицу если число кратно десяти
int s21_mul_ten(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_help_mul_ten(s21_decimal value, int powsm, s21_decimal *result);

// деление c остатком возвращает остаток
s21_decimal s21_mod(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);
void s21_help_funck_littlenumber(s21_decimal *buff, s21_decimal value_1,
                                 s21_decimal *buff_one, int *status,
                                 s21_decimal value_2);
int s21_help_round_div(s21_decimal mod, s21_decimal res, s21_decimal value_2);

// деление
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_help_div(s21_decimal *mod, s21_decimal value_2, int *res_scale,
                  int *flag, s21_decimal *result, s21_decimal ten,
                  s21_decimal *buf_res);
void s21_help_help_div(int res_scale, int flag, s21_decimal buf_res, int sign,
                       int *status, s21_decimal *result);

// меньше
int s21_is_less(s21_decimal value_1, s21_decimal value_2);

// меньше или равно
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// больше
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);

// больше или или равно
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

// равно
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

// не равно
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

#define OK 0
#define FAILURE 1
int s21_floor(s21_decimal value, s21_decimal *res);
int s21_negate(s21_decimal value, s21_decimal *res);
int s21_truncate(s21_decimal value, s21_decimal *res);
int s21_round(s21_decimal value, s21_decimal *res);

//преобразователи
#define OK 0
#define FAILURE 1
#define SCALE 0b11111111 << 16
#define max_dec 79228162514264337593543950335.0F

void s21_zerobits(s21_decimal *dst);
s21_decimal *s21_setbit(s21_decimal *dst, int bit_position, int value);
int get_sign(s21_decimal src);
void set_sign(s21_decimal *value, int sign);
int get_firstnonzero(s21_decimal src);
int s21_getscale(s21_decimal value);
int s21_getbit(s21_decimal value, int bit);
s21_decimal *s21_set_scale(s21_decimal *value, int scale);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int scale_right(s21_decimal num);
#endif