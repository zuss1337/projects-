#include "s21_string.h"

#include "errors.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  s21_size_t i = 0;
  int position = -1;
  const char *str1 = (const char *)str;
  while (i < s21_strlen(str1) && i < n) {
    if ((int)str1[i] == c) {
      position = i;
      break;
    }
    i++;
  }
  return position == -1 ? s21_NULL : (void *)str + position;
}

int s21_memcmp(const void *str1, const void *str2,
               s21_size_t n) {  //Сравнивает первые n байтов str1 и str2
  int flag = 0;
  const char *c_str1 = (const char *)str1;  // Приведение str1 к const char*
  const char *c_str2 = (const char *)str2;  // Приведение str2 к const char*
  for (s21_size_t i = 0; i < n; i++) {
    if (c_str1[i] != c_str2[i]) {
      flag = c_str1[i] - c_str2[i];
      break;
    }
  }
  return flag;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  s21_size_t i;
  char *dest1 = (char *)dest;
  const char *src1 = (const char *)src;
  s21_size_t len = s21_strlen(src1);
  for (i = 0; i < len && i < n; i++) {
    dest1[i] = src1[i];
  }
  if (i > s21_strlen(dest1)) dest1[i] = '\0';
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  s21_size_t i = 0;
  char *str1 = (char *)str;
  while (i < s21_strlen(str1) && i < n) {
    str1[i] = (char)c;
    i++;
  }
  return str;
}

char *s21_strncat(
    char *dest, const char *src,
    s21_size_t n) {  //Добавляет строку, на которую указывает src, в конец
                     //строки, на которую указывает dest, длиной до n символов
  char *end = dest;
  while (*end) {
    end++;
  }
  // char *sr = src;
  s21_size_t i = 0;
  while (*src && i < n) {
    *end = *src;
    end++;
    src++;
    i++;
  }
  *end = '\0';
  return dest;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  s21_size_t i = 0;
  while (*str1 != '\0' && *str1 == *str2 && i < n) {
    str1++;
    str2++;
    i++;
  }
  if (*str1 == '\0' && *str2 == '\0') {
    result = 0;
  } else if (*str1 != *str2) {
    result = str1[0] - str2[0];
  }
  return result;
}
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  s21_size_t len = s21_strlen(src);
  for (i = 0; i < len && i < n; i++) {
    dest[i] = src[i];
  }
  if (i > s21_strlen(dest)) dest[i] = '\0';
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int flag = 0;
  s21_size_t len = 0;
  for (s21_size_t i = 0; str1[i] != '\0'; i++) {
    for (s21_size_t j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
      }
    }
    if (flag == 0) {
      len++;
    }
  }
  return len;
}

char *s21_strerror(int errnum) {
  static char result[512] = {'\0'};
  if (errnum <= MIN_ERRLIST || errnum >= MAX_ERRLIST) {
#if defined(__APPLE__)
    s21_sprintf(result, "Unknown error: %d", errnum);  // исправить
#elif defined(__linux__)
    s21_sprintf(result, "Unknown error %d", errnum);
#endif
  } else
    return (char *)errorList[errnum];
  return result;
}

char *s21_strchr(const char *str, int c) {
  char *f = s21_NULL;
  while (*str) {
    if (*str == c) {
      f = (char *)str;
      break;
    }
    str++;
  }
  if (*str == c) {
    f = (char *)str;
  }
  return f;
}

char *s21_strpbrk(
    const char *str1,
    const char *str2) {  //Находит первый символ в строке str1, который
                         //соответствует любому символу, указанному в str2
  int k = 0, i, position = -1;
  while (*str2) {
    char b;
    b = str2[0];
    for (i = 0; str1[i]; i++) {
      if (str1[i] == b && (position >= i || position == -1)) {
        position = i;
        k = 1;
        break;
      }
    }
    str2++;
  }
  return k == 0 ? s21_NULL : (char *)&str1[position];
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; str[len]; len++)
    ;
  return len;
}

char *s21_strstr(char *haystack, const char *needle) {
  if (!*needle) return (char *)haystack;
  const char *p1, *p2;
  for (p1 = haystack; *p1 != '\0'; p1++) {
    p2 = needle;
    while (*p2 != '\0' && *p1 == *p2) {
      p1++;
      p2++;
    }
    if (*p2 == '\0') return (char *)p1 - (p2 - needle);
  }
  return s21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  const char *f = s21_NULL;

  while (*str) {
    if (*str == c) f = str;
    str++;
  }
  if (c == '\0') {
    f = (char *)str;
  }

  return (char *)f;
}

char *s21_strtok(char *str, const char *delim) {
  static char *nextstr;
  if (str) {
    nextstr = str;
  }
  if (!nextstr) {
    return s21_NULL;
  }

  char *res = nextstr;
  while (*nextstr && s21_strchr(delim, *nextstr)) {
    nextstr++;
  }
  if (!*nextstr) {
    return s21_NULL;
  }

  res = nextstr;
  while (*nextstr && !s21_strchr(delim, *nextstr)) {
    nextstr++;
  }
  if (*nextstr) {
    *nextstr = '\0';
    nextstr++;
  } else {
    nextstr = s21_NULL;
  }

  return res;
}

void s21_strcpy(char *str, const char *str1) {
  s21_size_t len = s21_strlen(str);
  s21_size_t i;
  for (i = 0; i < len; i++) {
    str[i] = str1[i];
  }
  if (i < s21_strlen(str)) str[i] = '\0';
}
