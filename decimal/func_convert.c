#include "s21_decimal.h"

void s21_zerobits(s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
}

s21_decimal *s21_setbit(s21_decimal *dst, int bit_position, int value) {
  int index = bit_position / 32;  // Индекс элемента массива bits
  int offset = bit_position % 32;  // Смещение внутри элемента
  int mask = 1U << offset;  // Маска для установки или сброса бита

  if (value) {
    dst->bits[index] |= mask;  // Устанавливаем бит в 1
  } else {
    dst->bits[index] &= ~mask;  // Сбрасываем бит в 0
  }

  return dst;  // Возвращаем указатель на измененную структуру
}

// Функция для проверки знака числа
int get_sign(s21_decimal src) { return (src.bits[3] >> 31) & 1; }

// Функция для установки знака
void set_sign(s21_decimal *value, int sign) {
  if (sign)
    value->bits[3] |= (1u << 31);
  else
    value->bits[3] &= ~(1u << 31);
}

// Функция для получения позиции первого ненулевого бита
int get_firstnonzero(s21_decimal src) {
  for (int i = 95; i >= 0; i--) {
    if ((src.bits[i / 32] >> (i % 32)) & 1) {
      return i;
    }
  }
  return -1;
}

int s21_getscale(s21_decimal value) {
  int scale = value.bits[3] & SCALE;
  return scale >> 16;
}

// Функция для проверки определенного бита в decimal
int s21_getbit(s21_decimal value, int bit) {
  int elem = value.bits[bit / 32];
  int mask = 1u << (bit % 32);
  return !!(elem & mask);
}

s21_decimal *s21_set_scale(s21_decimal *value, int scale) {
  if (scale >= 0) {
    value->bits[3] = value->bits[3] & (~(SCALE));
    value->bits[3] = value->bits[3] | scale << 16;
  }
  return value;
}
