#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long unsigned s21_size_t;

#define s21_NULL (void *)0
#define ERRSIZE 10
typedef struct {
  void *p;
  long double ld;
} types_t;

typedef struct {
  int error;
  types_t value;
} types_return_t;

struct flags {
  bool hyphen;
  bool plus;
  bool space;
  bool sharp;
  bool nul;
  bool spec_int;
  bool spec_float;
};

int s21_sprintf(char *form, const char *format, ...);
int s21_sprintf(char *str, const char *format, ...);
void reverse(char *out);
char *from_int_to_string(long long int src);
int flags_processing(const char *format, struct flags *status_flags);
int width_processing(const char *format, int *width, va_list args);
int precision_processing(const char *format, int *precision, va_list args);
char *out_str_formatting(char *str, struct flags status_flags, int width,
                         int precision);
char *from_double_to_str(long double src, int precision, bool have_sharp);
char *specifier_processing(const char *format, va_list args, int *shift,
                           struct flags *status_flags, int *precision,
                           char *end_str);
char *mant_exp_str(long double src, int precision, bool have_sharp,
                   char E_or_e);
char *int_to_8_10_16(long long int src, int base, bool high_reg,
                     bool have_sharp);
char *short_note_gG(long double src, int precision, bool have_sharp,
                    char E_or_e);

// str func
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
int s21_strncmp(const char *str1, const char *str2, size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strchr(const char *str, int b);
char *s21_strstr(char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void s21_strcpy(char *str, const char *str1);
char *s21_strrchr(const char *str, int c);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
#endif