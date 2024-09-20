#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  static char result[512];
  // Очистка результата перед каждым вызовом
  s21_memset(result, '\0', sizeof(result));
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    char b = str[i];
    if (b >= 'a' && b <= 'z') {
      result[i] = b + 'A' - 'a';
    } else {
      result[i] = b;
    }
  }
  return (void *)result;
}

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  static char result[512] = {'\0'};
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    char b = str[i];
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = b - 'A' + 'a';
    }
  }
  return (void *)result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL) return s21_NULL;
  s21_size_t n_src = s21_strlen(src);
  if (start_index > n_src) return s21_NULL;
  if (str == s21_NULL) {
    char *result = (char *)malloc((n_src + 1) * sizeof(char));
    s21_memcpy(result, src, n_src + 1);
    return result;
  }

  s21_size_t n_str = s21_strlen(str);

  char *result = (char *)malloc((n_src + n_str + 1) * sizeof(char));
  s21_size_t i = 0;
  while (i < start_index) {
    result[i] = src[i];
    i++;
  }
  while (i - start_index < n_str) {
    result[i] = str[i - start_index];
    i++;
  }
  while (start_index <= n_src) {
    result[i] = src[start_index];
    i++;
    start_index++;
  }

  return (void *)result;
}
void *s21_trim(const char *src, const char *trim_chars) {
  char *f = s21_NULL;
  if (src) {
    if (!trim_chars) {
      trim_chars = " ";
    }
    char *ptr_str = (char *)src;
    char *end_str = (char *)src + s21_strlen(src);
    for (; *ptr_str && s21_strchr(trim_chars, *ptr_str); ptr_str++)
      ;
    for (; end_str != ptr_str && s21_strchr(trim_chars, *(end_str - 1));
         end_str--)
      ;
    f = (char *)calloc(end_str - ptr_str + 1, sizeof(char));
    if (f) {
      s21_strncpy(f, ptr_str, end_str - ptr_str);
      *(f + (end_str - ptr_str)) = '\0';
    }
  }
  return f;
}