#include <check.h>

#include "s21_string.h"

//тесты для первого задания

START_TEST(s21_memset_test_1) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(s21_memset(string_1, '6', 10), memset(string_1, '6', 10));
}
END_TEST

START_TEST(s21_memset_test_2) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(s21_memset(string_1, '\t', 5), memset(string_1, '\t', 5));
}
END_TEST

START_TEST(s21_memset_test_3) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(s21_memset(string_1, '\0', 10), memset(string_1, '\0', 10));
}
END_TEST

START_TEST(s21_memset_test_4) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(s21_memset(string_1, 'G', 2), memset(string_1, 'G', 2));
}
END_TEST

START_TEST(s21_memset_test_5) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(s21_memset(string_1, 'J', 10), memset(string_1, 'J', 10));
}
END_TEST

START_TEST(s21_memset_test_6) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(s21_memset(string_1, '`', 10), memset(string_1, '`', 10));
}
END_TEST

START_TEST(s21_strncat_test_1) {
  char string_1[80] = "Unreal genius";
  ck_assert_str_eq(strncat(string_1, "abcd", 1),
                   s21_strncat(string_1, "abcd", 1));
}
END_TEST

START_TEST(s21_strncat_test_2) {
  char string_1[80] = "Unreal genius";
  ck_assert_str_eq(strncat(string_1, " - this is nerealniye genii", 13),
                   s21_strncat(string_1, " - this is nerealniye genii", 13));
}
END_TEST

START_TEST(s21_strchr_test_1) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(strchr(string_1, 'l'), s21_strchr(string_1, 'l'));
}
END_TEST

START_TEST(s21_strchr_test_2) {
  char string_1[20] = "Unreal genius";
  ck_assert(strchr(string_1, '\n') == NULL);
}
END_TEST

START_TEST(s21_strchr_test_3) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(strchr(string_1, '\0'), s21_strchr(string_1, '\0'));
}
END_TEST

START_TEST(s21_strrchr_test_1) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(strrchr(string_1, 'l'), s21_strrchr(string_1, 'l'));
}
END_TEST

START_TEST(s21_strrchr_test_2) {
  char string_1[20] = "Unreal genius";
  ck_assert(s21_strrchr(string_1, '\n') == NULL);
}
END_TEST

START_TEST(s21_strrchr_test_3) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(strrchr(string_1, '\0'), s21_strrchr(string_1, '\0'));
}
END_TEST

START_TEST(s21_strrchr_test_4) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(strrchr(string_1, ' '), s21_strrchr(string_1, ' '));
}
END_TEST

START_TEST(s21_strtok_test_1) {
  char string_1[20] = "Unreal/genius";
  ck_assert_str_eq(strtok(string_1, "/"), s21_strtok(string_1, "/"));
}
END_TEST

START_TEST(s21_strtok_test_2) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(strtok(string_1, " "), s21_strtok(string_1, " "));
}
END_TEST

START_TEST(s21_strtok_test_3) {
  char string_1[20] = "Unreal:genius";
  ck_assert_str_eq(strtok(string_1, ":"), s21_strtok(string_1, ":"));
}
END_TEST

START_TEST(s21_strtok_test_4) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(strtok(string_1, " "), s21_strtok(string_1, " "));
}
END_TEST

START_TEST(s21_strtok_test_5) {
  char delitel[7] = "!+ -/:";
  char string_1[80] =
      "Unreal!genius+Nerealniye/genii ------ i      "
      "Kstati++++++hz:chto/s+Nikitoy";
  ck_assert_str_eq(strtok(string_1, delitel), s21_strtok(string_1, delitel));
}
END_TEST

START_TEST(s21_strtok_test_6) {
  char string_1[20] = "Unreal genius";
  ck_assert_str_eq(strtok(string_1, " "), s21_strtok(string_1, " "));
}
END_TEST

START_TEST(s21_strtok_test_7) {
  char *s1 = "Hello world";
  char *s2 = "Hello world";
  char s3[] = "";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(s21_strtok_test_8) {
  char *s1 = "Hello world";
  char *s2 = "Hello world";
  char s3[] = "\0";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(s21_strtok_test_9) {
  char *s1 = "\0FOFOFOFOFOFOF";
  char *s2 = "\0FOFOFOFOFOFOF";
  char s3[] = "F";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(s21_strtok_test_10) {
  char *s1 = "\0Hello world";
  char *s2 = "\0Hello world";
  char s3[] = "\0";
  ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(s21_strtok_test_11) {
  char *s1 = "Hello world";
  char *s2 = "Hello world";
  char *s3 = "H";
  ck_assert_pstr_eq(s21_strtok(s1, s3), s21_strtok(s2, s3));
}
END_TEST

START_TEST(s21_strtok_test_12) {
  char s1[] = "Hello, world! And other people";
  char s2[] = "Hello, world! And other people";
  char s3[] = "\0Come here";
  char s4[] = "\0Come here";
  char s5[] = "";

  ck_assert_pstr_eq(strtok(s1, s5), s21_strtok(s2, s5));
  for (int i = 0; i < 5; i++) {
    ck_assert_pstr_eq(strtok(s21_NULL, s5), s21_strtok(s21_NULL, s5));
  }
  ck_assert_pstr_eq(strtok(s3, s5), s21_strtok(s4, s5));
  ck_assert_pstr_eq(strtok(s21_NULL, s5), s21_strtok(s21_NULL, s5));
  ck_assert_pstr_eq(strtok(s21_NULL, s5), s21_strtok(s21_NULL, s5));
}
END_TEST

START_TEST(s21_strtok_test_13) {
  // ++
  char str11[100] = "1/2/3/4";
  char str21[100] = "/";
  char str111[100] = "1/2/3/4\0";
  char str121[100] = "/\0";
  ck_assert_str_eq(s21_strtok(str11, str21), strtok(str111, str121));
  ck_assert_str_eq(s21_strtok(NULL, str21), strtok(NULL, str121));
  ck_assert_str_eq(s21_strtok(NULL, str21), strtok(NULL, str121));
  ck_assert_str_eq(s21_strtok(NULL, str21), strtok(NULL, str121));
  ck_assert_ptr_eq(s21_strtok(NULL, str21), strtok(NULL, str121));
}
END_TEST

START_TEST(s21_strpbrk_test_1) {
  ck_assert_str_eq(strpbrk("Unreal genius", "us"),
                   s21_strpbrk("Unreal genius", "us"));
}
END_TEST

START_TEST(s21_strpbrk_test_2) {
  ck_assert_str_eq(strpbrk("Unreal genius", " "),
                   s21_strpbrk("Unreal genius", " "));
}
END_TEST

START_TEST(s21_strpbrk_test_3) {
  ck_assert_ptr_eq(strpbrk("123", "abc"), s21_strpbrk("123", "abc"));
}
END_TEST

START_TEST(s21_strpbrk_test_4) {
  ck_assert_ptr_eq(strpbrk("Hello", ""), s21_strpbrk("Hello", ""));
}
END_TEST

START_TEST(s21_strstr_test_1) {
  char str1[10] = "School21";
  char str2[10] = "dod";
  ck_assert_ptr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(s21_strstr_test_2) {
  char str1[10] = "School21";
  char str2[10] = " ";
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(s21_strlen_test_1) {
  char string_1[40] = "Unreal genius";
  ck_assert_uint_eq(strlen(string_1), s21_strlen(string_1));
}
END_TEST

START_TEST(s21_strlen_test_2) { ck_assert_uint_eq(strlen(""), s21_strlen("")); }
END_TEST

START_TEST(s21_strlen_test_3) {
  ck_assert_uint_eq(strlen("\0"), s21_strlen("\0"));
}
END_TEST

START_TEST(s21_strlen_test_4) {
  char string_1[4] = "[]";
  ck_assert_uint_eq(strlen(string_1), s21_strlen(string_1));
}
END_TEST

START_TEST(s21_strlen_test_5) {
  char string_1[20] = "               ";
  ck_assert_uint_eq(strlen(string_1), s21_strlen(string_1));
}
END_TEST

START_TEST(s21_strlen_test_6) {
  char string_1[4] = "";
  ck_assert_uint_eq(strlen(string_1), s21_strlen(string_1));
}
END_TEST

START_TEST(s21_strncmp_test_1) {
  ck_assert(s21_strncmp("123456", "123456", 4) == 0);
}
END_TEST

START_TEST(s21_strncmp_test_2) {
  ck_assert(s21_strncmp("1234567", "7654321", 4) < 0);
}
END_TEST

START_TEST(s21_strncmp_test_3) {
  ck_assert(s21_strncmp("7654321", "1234567", 4) > 0);
}
END_TEST

START_TEST(s21_memcpy_test_1) {
  char string_1[100] = "Unreal genius";
  char string_2[100] = "";
  ck_assert_str_eq(memcpy(string_1, string_2, strlen(string_1)),
                   s21_memcpy(string_1, string_2, strlen(string_1)));
}
END_TEST

START_TEST(s21_memcpy_test_2) {
  char string_1[100] = "Unreal genius";
  char string_2[100] = "";
  ck_assert_str_eq(memcpy(string_1, string_2, 15),
                   s21_memcpy(string_1, string_2, 15));
}
END_TEST

START_TEST(s21_memcpy_test_3) {
  char string_1[100] = "Unreal genius";
  char string_2[100] = "";
  ck_assert_str_eq(memcpy(string_1, string_2, 4),
                   s21_memcpy(string_1, string_2, 4));
}
END_TEST

START_TEST(s21_memcpy_test_4) {
  char string_1[100] = "Unreal genius";
  char string_2[100] = "";
  ck_assert_str_eq(memcpy(string_1, string_2, 0),
                   s21_memcpy(string_1, string_2, 0));
}
END_TEST

START_TEST(s21_memchr_test_1) {
  char string_1[100] = "Unreal genius";
  ck_assert_ptr_eq(memchr(string_1, 'l', 14), s21_memchr(string_1, 'l', 14));
}
END_TEST

START_TEST(s21_memchr_test_2) {
  char string_1[100] = "Unreal genius";
  ck_assert_ptr_eq(memchr(string_1, 'd', 14), s21_memchr(string_1, 'd', 14));
}
END_TEST

START_TEST(s21_memchr_test_3) {
  char string_1[100] = "Unreal genius";
  ck_assert_ptr_eq(memchr(string_1, 'l', 5), s21_memchr(string_1, 'l', 5));
}
END_TEST

START_TEST(s21_memchr_test_4) {
  char string_1[100] = "Unreal genius";
  ck_assert_ptr_eq(memchr(string_1, 'l', 1), s21_memchr(string_1, 'l', 1));
}
END_TEST

START_TEST(s21_memchr_test_5) {
  char string_1[100] = "Unreal genius";
  ck_assert_ptr_eq(memchr(string_1, 'd', 1), s21_memchr(string_1, 'd', 1));
}
END_TEST

START_TEST(s21_memchr_test_6) {
  char string_1[100] = "Unreal genius";
  ck_assert_ptr_eq(memchr(string_1, 's', 12), s21_memchr(string_1, 's', 12));
}
END_TEST

START_TEST(s21_memcmp_test_1) {
  ck_assert(memcmp("Hello", "Hello", 10) == s21_memcmp("Hello", "Hello", 10));
}
END_TEST

START_TEST(s21_memcmp_test_2) { ck_assert(s21_memcmp("Day", "Today", 7) < 0); }
END_TEST

START_TEST(s21_strcspn_test_1) {
  ck_assert_int_eq(s21_strcspn("ABCDEFG", "AB"), strcspn("ABCDEFG", "AB"));
}
END_TEST

START_TEST(s21_strerror_1) {
  int n = 130;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST

START_TEST(s21_strerror_2) {
  int n = 0;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST

START_TEST(s21_strerror_3) {
  int n = 105;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

START_TEST(s21_strerror_4) {
  int n = 57;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

START_TEST(s21_strncpy_test_1) {
  char buf_to_1[100] = "000000000";
  char buf_to_2[100] = "000000000";
  char buf_from_1[100] = "1111111111";
  char buf_from_2[100] = "1111111111";
  strncpy(buf_from_1, buf_to_1, 7);
  s21_strncpy(buf_from_2, buf_to_2, 7);
  ck_assert_str_eq(buf_to_1, buf_to_2);
}
END_TEST

//тесты для спринтф
START_TEST(s21_sprintf_test_c_1) {
  char str1[100];
  char str2[100];
  char *str3 = "%c \n %c \n %c";
  int a = -6;
  int b = -10;
  int c = -17;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                   s21_sprintf(str2, str3, a, b, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_2) {
  char str1[100];
  char str2[100];
  char *str3 = "%c \n %c \n %c";
  char a[] = "lol";
  ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                   s21_sprintf(str2, str3, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_3) {
  char str1[100];
  char str2[100];
  char *str3 = "%c \n %c \n %c";
  unsigned long int a = 1;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                   s21_sprintf(str2, str3, a, a, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_4) {
  char str1[100];
  char str2[100];
  char *str3 = "%c \n %c \n %c";
  char a[] = "lol";
  ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                   s21_sprintf(str2, str3, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_5) {
  char str1[100];
  char str2[100];
  char *str3 = "%3c \n %3c \n %3c";
  unsigned long int a = 200;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                   s21_sprintf(str2, str3, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_6) {
  char str1[100];
  char str2[100];
  char *str3 = "%3c \n %3c \n %3c";
  unsigned long int a = 200;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                   s21_sprintf(str2, str3, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_7) {
  char str1[100];
  char str2[100];
  char *str3 = "%-3c \n %-3c \n % -3c";
  unsigned long int a = 200;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                   s21_sprintf(str2, str3, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_8) {
  char str1[100];
  char str2[100];
  char *str3 = "%-3c \n %-.3c \n % -3c";
  unsigned long int a = 200;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                   s21_sprintf(str2, str3, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_9) {
  char str1[100];
  char str2[100];
  char *str3 = "%-3c \n %-.3c \n % -c";
  unsigned long int a = 200;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                   s21_sprintf(str2, str3, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_10) {
  char str1[100];
  char str2[100];
  char *str3 = "%c\n %c \n%hc";
  int a = 3;
  unsigned long int b = 103;
  unsigned short e = 255;
  ck_assert_int_eq(sprintf(str1, str3, a, b, e),
                   s21_sprintf(str2, str3, a, b, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_c_11) {
  char str1[100];
  char str2[100];
  char *str3 = "%c\n %c \n%hc";
  int a = 3;
  unsigned long int b = 103;
  unsigned short e = 255;
  ck_assert_int_eq(sprintf(str1, str3, a, b, e),
                   s21_sprintf(str2, str3, a, b, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d_1) {
  char str1[100];
  char str2[100];
  char *str3 = "%d\n ";
  int a = 3;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d_2) {
  char str1[100];
  char str2[100];
  char *str3 = "%d\n ";
  int a = 3;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d_4) {
  char str1[100];
  char str2[100];
  char *str3 = "%.5d\n ";
  int a = 3;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d_5) {
  char str1[100];
  char str2[100];
  char *str3 = "%+5d";
  int a = 3;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d_6) {
  char str1[100];
  char str2[100];
  char *str3 = "        %+5ld\n  ";
  long int a = 3;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d_7) {
  char str1[200];
  char str2[200];
  char *str3 = "%d %3.d %5.7d %10d %-d %+d %.d % .d";
  int a = 1;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a, a, a, a),
                   s21_sprintf(str2, str3, a, a, a, a, a, a, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d_8) {
  char str1[200];
  char str2[200];
  char *str3 = "%- d ";
  int a = -3231;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d_9) {
  char str1[200];
  char str2[200];
  char *str3 = "%- 15d ";
  int a = -3231;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d_10) {
  char str1[200];
  char str2[200];
  char *str3 = " %- 15d %- d";
  int a = 3231;
  int b = 3231;
  ck_assert_int_eq(sprintf(str1, str3, a, b), s21_sprintf(str2, str3, a, b));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST
START_TEST(s21_sprintf_test_d_11) {
  char str1[200];
  char str2[200];
  char *str3 = " %15d %d";
  int a = -3231454;
  int b = -3231454;
  ck_assert_int_eq(sprintf(str1, str3, a, b), s21_sprintf(str2, str3, a, b));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_s_1) {
  char buf1[100] = "HELLO WORLD, I AM UNREAL GENIUS";
  char buf2[100] = "HELLO WORLD, I AM UNREAL GENIUS";
  sprintf(buf1, "%s", "Amir genius");
  s21_sprintf(buf2, "%s", "Amir genius");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_test_s_3) {
  char buf1[100] = "HELLO WORLD, I AM UNREAL GENIUS";
  char buf2[100] = "HELLO WORLD, I AM UNREAL GENIUS";
  sprintf(buf1, "%-.10s", "123");
  s21_sprintf(buf2, "%-.10s", "123");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_test_l_1) {
  char buf1[100] = "HELLO WORLD, I AM UNREAL GENIUS";
  char buf2[100] = "HELLO WORLD, I AM UNREAL GENIUS";
  sprintf(buf1, "%.10s", "123");
  s21_sprintf(buf2, "%.10s", "123");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_test_u_1) {
  char str1[100];
  char str2[100];
  char *str3 = "%lu";
  long unsigned int a = 4038625721333946;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_2) {
  char str1[100];
  char str2[100];
  long unsigned int a = 12030010103;
  char *str3 = " %lu";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_3) {
  char str1[100];
  char str2[100];
  unsigned short a = 110;
  char *str3 = "%hu";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_8) {
  char str1[40];
  char str2[40];
  unsigned int a = 110;
  char *str3 = "%.u";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_9) {
  char str1[40];
  char str2[40];
  unsigned int a = 110;
  char *str3 = "%.5u";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_10) {
  char str1[40];
  char str2[40];
  unsigned int a = 110;
  char *str3 = "%-3.5u";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_11) {
  char str1[40];
  char str2[40];
  unsigned int a = 110;
  char *str3 = "%0u";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_12) {
  char str1[40];
  char str2[40];
  unsigned int a = 11346;
  char *str3 = "%0.u";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_13) {
  char str1[40];
  char str2[40];
  unsigned int a = 10;
  char *str3 = "%0.0u";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_14) {
  char str1[40];
  char str2[40];
  unsigned int a = 0;
  char *str3 = "%#10u";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_u_15) {
  char str1[40];
  char str2[40];
  unsigned int a = -110;
  char *str3 = "%%+5.7u";
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_s_15) {
  char str1[40];
  char str2[40];
  char *str3 = "%+5.s";
  char *str4 = "Hello my name";
  ck_assert_int_eq(sprintf(str1, str3, str4), s21_sprintf(str2, str3, str4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f_1) {
  char buf1[100] = "";
  char buf2[100] = "";
  char *buf3 = "Lf %.Lf";
  long double a = -12.8524657;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a), s21_sprintf(buf2, buf3, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_f_2) {
  char buf1[40] = "";
  char buf2[40] = "";
  char *buf3 = "Lf %.Lf";
  long double a = -12.8524657;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a), s21_sprintf(buf2, buf3, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_f_3) {
  char buf1[200] = "";
  char buf2[200] = "";
  char *buf3 = "%20.10f %20.15f %-20.5f";
  double a = -76.756589;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a, a),
                   s21_sprintf(buf2, buf3, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_f_4) {
  char buf1[400];
  char buf2[400];
  char *buf3 = "%f %.f %3f %4.f %5.10f";
  double a = -76.756589367;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a, a, a, a),
                   s21_sprintf(buf2, buf3, a, a, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_f_5) {
  char buf1[400];
  char buf2[400];
  char *buf3 = "%+15.f %+16.f %+18.0f";
  double a = 7648938790.756589;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a, a),
                   s21_sprintf(buf2, buf3, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_f_6) {
  char buf1[400];
  char buf2[400];
  char *buf3 = "%+ 18.0f %+10.f %+25.f!";
  double a = 7648938790.756589;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a, a),
                   s21_sprintf(buf2, buf3, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_f_7) {
  char buf1[400];
  char buf2[400];
  char *buf3 = "%-26.1f %-18.0f %-10.f";
  double a = 7648938790.756589;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a, a),
                   s21_sprintf(buf2, buf3, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_f_8) {
  char buf1[400];
  char buf2[400];
  char *buf3 = "%-15.f %-+25.f";
  double a = 7648938790.756589;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a, a),
                   s21_sprintf(buf2, buf3, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_f_9) {
  char buf1[400];
  char buf2[400];
  char *buf3 = "%-15.4f %-26.1f %-18.0f";
  double a = 7648938790.756589;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a, a),
                   s21_sprintf(buf2, buf3, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(s21_sprintf_f_10) {
  char buf1[400];
  char buf2[400];
  char *buf3 = "%-15.4f %-26.1f %-18.0f";
  double a = 7648938790.756589;
  ck_assert_int_eq(sprintf(buf1, buf3, a, a, a),
                   s21_sprintf(buf2, buf3, a, a, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

START_TEST(SPRINTFTest1) {
  char str1[200] = {};
  char str2[200] = {};
  char s = 'S';
  char str3[6] = "kazan";
  s21_sprintf(str1, "test c:%c", s);
  sprintf(str2, "test c:%c", s);
  ck_assert_str_eq(str1, str2);

  s21_sprintf(str1, "test c:%-c %%", s);
  sprintf(str2, "test c:%-c %%", s);
  ck_assert_str_eq(str1, str2);

  s21_sprintf(str1, "test c:%s %15s", str3, str3);
  sprintf(str2, "test c:%s %15s", str3, str3);
  ck_assert_str_eq(str1, str2);

  s21_sprintf(str1, "test c:%c %-c %% %s", s, s, str3);
  sprintf(str2, "test c:%c %-c %% %s", s, s, str3);
  ck_assert_str_eq(str1, str2);

  wchar_t str_w[] = L"abra carabra";

  s21_sprintf(str1, "test c:%ls", str_w);
  sprintf(str2, "test c:%ls", str_w);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(SPRINTFTest2) {
  char str1[100] = {};
  char str2[100] = {};
  int n = 345678;
  long int n2 = 45454564654;
  short n3 = 777;
  s21_sprintf(str1, "test i: %i %+i %9i %-9i %.5i %hi", n, n, n, n, n, n3);
  sprintf(str2, "test i: %i %+i %9i %-9i %.5i %hi", n, n, n, n, n, n3);
  ck_assert_str_eq(str1, str2);

  s21_sprintf(str1, "%hi %li", n3, n2);
  sprintf(str2, "%hi %li", n3, n2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_1239) {
  char test_pointer1239[50];
  char test_str_1239[50] = "";
  char test_str_1239_1239[50] = "";
  s21_sprintf(test_str_1239, "%-p", test_pointer1239);
  sprintf(test_str_1239_1239, "%-p", test_pointer1239);
  ck_assert_str_eq(test_str_1239, test_str_1239_1239);
}
END_TEST

START_TEST(sprintf_test_1229) {
  char test_str_1229[50] = "";
  char test_str_1229_1229[50] = "";
  int int_test_str_1229[50] = {0, 0, 0, 0, 0};
  int int_test_str_1229_1229[50] = {0, 0, 0, 0, 0};
  s21_sprintf(test_str_1229, "dsdsdsds %n", int_test_str_1229);
  sprintf(test_str_1229_1229, "dsdsdsds %n", int_test_str_1229_1229);
  ck_assert_int_eq(int_test_str_1229[0], int_test_str_1229_1229[0]);
}
END_TEST

START_TEST(s21_sprintf_g_1) {
  char buf1[400];
  char buf2[400];
  char *buf3 = "%g";
  double a = 76.75;
  ck_assert_int_eq(sprintf(buf1, buf3, a), s21_sprintf(buf2, buf3, a));
  ck_assert_pstr_eq(buf1, buf2);
}
END_TEST

//тесты для шарповских функций

START_TEST(s21_to_upper_test_1) {
  char *buf1 = "ABCD";
  char buf2[100] = "abcd";
  char *buf3 = s21_to_upper(buf2);
  ck_assert_pstr_eq(buf1, buf3);
}
END_TEST

START_TEST(s21_to_upper_test_2) {
  char *buf1 = "";
  char *buf2 = s21_to_upper(buf1);
  char buf3[] = "";
  ck_assert_pstr_eq(buf3, buf2);
}
END_TEST

START_TEST(s21_to_upper_test_3) {
  char *buf1 = "ABCD";
  char buf2[100] = "ABCD";
  char *buf3 = s21_to_upper(buf2);
  ck_assert_pstr_eq(buf1, buf3);
}
END_TEST

START_TEST(s21_to_lower_test_1) {
  char *buf1 = "abcd";
  char buf2[100] = "ABCD";
  char *buf3 = s21_to_lower(buf2);
  ck_assert_pstr_eq(buf1, buf3);
}
END_TEST

START_TEST(s21_to_lower_test_2) {
  char *buf1 = "abcd";
  char buf2[100] = "abcd";
  char *buf3 = s21_to_lower(buf2);
  ck_assert_pstr_eq(buf1, buf3);
}
END_TEST

START_TEST(s21_insert_test_1) {
  char *buf1 = "abcd";
  char *buf2 = "12345";
  int a = 3;
  char *buf3 = s21_insert(buf1, buf2, a);
  char *buf4 = "abc12345d";
  ck_assert_pstr_eq(buf4, buf3);
  if (buf3) free(buf3);
}
END_TEST

START_TEST(s21_trim_test_1) {
  char *buf1 = "abcd";
  char *buf2 = "abc12345abcd";
  char *buf3 = s21_trim(buf2, buf1);
  char *buf4 = "12345";
  ck_assert_pstr_eq(buf4, buf3);
  if (buf3) free(buf3);
}
END_TEST

START_TEST(s21_trim_test_2) {
  char *buf1 = " ";
  char *buf2 = " 12345  ";
  char *buf3 = s21_trim(buf2, buf1);
  char *buf4 = "12345";
  ck_assert_pstr_eq(buf4, buf3);
  if (buf3) free(buf3);
}
END_TEST

START_TEST(s21_trim_test_3) {
  char *buf1 = "";
  char *buf2 = "  12345 ";
  char *buf3 = s21_trim(buf2, buf1);
  char *buf4 = "  12345 ";
  ck_assert_pstr_eq(buf4, buf3);
  if (buf3) free(buf3);
}
END_TEST

START_TEST(s21_trim_test_4) {
  char *buf1 = "\n";
  char *buf2 = "\n12345\n";
  char *buf3 = s21_trim(buf2, buf1);
  char *buf4 = "12345";
  ck_assert_pstr_eq(buf4, buf3);
  if (buf3) free(buf3);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_memset_test_1);
  tcase_add_test(tc1_1, s21_memset_test_2);
  tcase_add_test(tc1_1, s21_memset_test_3);
  tcase_add_test(tc1_1, s21_memset_test_4);
  tcase_add_test(tc1_1, s21_memset_test_5);
  tcase_add_test(tc1_1, s21_memset_test_6);
  tcase_add_test(tc1_1, s21_strncat_test_1);
  tcase_add_test(tc1_1, s21_strncat_test_2);
  tcase_add_test(tc1_1, s21_strchr_test_1);
  tcase_add_test(tc1_1, s21_strchr_test_2);
  tcase_add_test(tc1_1, s21_strchr_test_3);
  tcase_add_test(tc1_1, s21_strrchr_test_1);
  tcase_add_test(tc1_1, s21_strrchr_test_2);
  tcase_add_test(tc1_1, s21_strrchr_test_3);
  tcase_add_test(tc1_1, s21_strrchr_test_4);
  tcase_add_test(tc1_1, s21_strtok_test_1);
  tcase_add_test(tc1_1, s21_strtok_test_2);
  tcase_add_test(tc1_1, s21_strtok_test_3);
  tcase_add_test(tc1_1, s21_strtok_test_4);
  tcase_add_test(tc1_1, s21_strtok_test_5);
  tcase_add_test(tc1_1, s21_strtok_test_6);
  tcase_add_test(tc1_1, s21_strtok_test_7);
  tcase_add_test(tc1_1, s21_strtok_test_8);
  tcase_add_test(tc1_1, s21_strtok_test_9);
  tcase_add_test(tc1_1, s21_strtok_test_10);
  tcase_add_test(tc1_1, s21_strtok_test_11);
  tcase_add_test(tc1_1, s21_strtok_test_12);
  tcase_add_test(tc1_1, s21_strtok_test_13);
  tcase_add_test(tc1_1, s21_strpbrk_test_1);
  tcase_add_test(tc1_1, s21_strpbrk_test_2);
  tcase_add_test(tc1_1, s21_strpbrk_test_3);
  tcase_add_test(tc1_1, s21_strpbrk_test_4);
  tcase_add_test(tc1_1, s21_strstr_test_1);
  tcase_add_test(tc1_1, s21_strstr_test_2);
  tcase_add_test(tc1_1, s21_strlen_test_1);
  tcase_add_test(tc1_1, s21_strlen_test_2);
  tcase_add_test(tc1_1, s21_strlen_test_3);
  tcase_add_test(tc1_1, s21_strlen_test_4);
  tcase_add_test(tc1_1, s21_strlen_test_5);
  tcase_add_test(tc1_1, s21_strlen_test_6);
  tcase_add_test(tc1_1, s21_strncmp_test_1);
  tcase_add_test(tc1_1, s21_strncmp_test_2);
  tcase_add_test(tc1_1, s21_strncmp_test_3);
  tcase_add_test(tc1_1, s21_memcpy_test_1);
  tcase_add_test(tc1_1, s21_memcpy_test_2);
  tcase_add_test(tc1_1, s21_memcpy_test_3);
  tcase_add_test(tc1_1, s21_memcpy_test_4);
  tcase_add_test(tc1_1, s21_memchr_test_1);
  tcase_add_test(tc1_1, s21_memchr_test_2);
  tcase_add_test(tc1_1, s21_memchr_test_3);
  tcase_add_test(tc1_1, s21_memchr_test_4);
  tcase_add_test(tc1_1, s21_memchr_test_5);
  tcase_add_test(tc1_1, s21_memchr_test_6);
  tcase_add_test(tc1_1, s21_memcmp_test_1);
  tcase_add_test(tc1_1, s21_memcmp_test_2);
  tcase_add_test(tc1_1, s21_strcspn_test_1);
  tcase_add_test(tc1_1, s21_sprintf_test_c_1);
  tcase_add_test(tc1_1, s21_sprintf_test_c_2);
  tcase_add_test(tc1_1, s21_sprintf_test_c_3);
  tcase_add_test(tc1_1, s21_sprintf_test_c_4);
  tcase_add_test(tc1_1, s21_sprintf_test_c_5);
  tcase_add_test(tc1_1, s21_sprintf_test_c_6);
  tcase_add_test(tc1_1, s21_sprintf_test_c_7);
  tcase_add_test(tc1_1, s21_sprintf_test_c_8);
  tcase_add_test(tc1_1, s21_sprintf_test_c_9);
  tcase_add_test(tc1_1, s21_sprintf_test_c_10);
  tcase_add_test(tc1_1, s21_sprintf_test_c_11);
  tcase_add_test(tc1_1, s21_sprintf_test_d_1);
  tcase_add_test(tc1_1, s21_sprintf_test_d_2);
  tcase_add_test(tc1_1, s21_sprintf_test_d_4);
  tcase_add_test(tc1_1, s21_sprintf_test_d_5);
  tcase_add_test(tc1_1, s21_sprintf_test_d_6);
  tcase_add_test(tc1_1, s21_sprintf_test_d_7);
  tcase_add_test(tc1_1, s21_sprintf_test_d_8);
  tcase_add_test(tc1_1, s21_sprintf_test_d_9);
  tcase_add_test(tc1_1, s21_sprintf_test_d_10);
  tcase_add_test(tc1_1, s21_sprintf_test_d_11);
  tcase_add_test(tc1_1, s21_sprintf_test_s_1);
  tcase_add_test(tc1_1, s21_sprintf_test_s_3);
  tcase_add_test(tc1_1, s21_sprintf_test_l_1);
  tcase_add_test(tc1_1, s21_sprintf_test_u_1);
  tcase_add_test(tc1_1, s21_sprintf_test_u_2);
  tcase_add_test(tc1_1, s21_sprintf_test_u_3);
  tcase_add_test(tc1_1, s21_sprintf_test_u_8);
  tcase_add_test(tc1_1, s21_sprintf_test_u_9);
  tcase_add_test(tc1_1, s21_sprintf_test_u_10);
  tcase_add_test(tc1_1, s21_sprintf_test_u_11);
  tcase_add_test(tc1_1, s21_sprintf_test_u_12);
  tcase_add_test(tc1_1, s21_sprintf_test_u_13);
  tcase_add_test(tc1_1, s21_sprintf_test_u_14);
  tcase_add_test(tc1_1, s21_sprintf_test_u_15);
  tcase_add_test(tc1_1, s21_sprintf_s_15);
  tcase_add_test(tc1_1, s21_sprintf_f_1);
  tcase_add_test(tc1_1, s21_sprintf_f_2);
  tcase_add_test(tc1_1, s21_sprintf_f_3);
  tcase_add_test(tc1_1, s21_sprintf_f_4);
  tcase_add_test(tc1_1, s21_sprintf_f_5);
  tcase_add_test(tc1_1, s21_sprintf_f_6);
  tcase_add_test(tc1_1, s21_sprintf_f_7);
  tcase_add_test(tc1_1, s21_sprintf_f_8);
  tcase_add_test(tc1_1, s21_sprintf_f_9);
  tcase_add_test(tc1_1, s21_sprintf_f_10);
  tcase_add_test(tc1_1, SPRINTFTest1);
  tcase_add_test(tc1_1, SPRINTFTest2);
  tcase_add_test(tc1_1, sprintf_test_1239);
  tcase_add_test(tc1_1, sprintf_test_1229);
  tcase_add_test(tc1_1, s21_sprintf_g_1);
  tcase_add_test(tc1_1, s21_strerror_1);
  tcase_add_test(tc1_1, s21_strerror_2);
  tcase_add_test(tc1_1, s21_strerror_3);
  tcase_add_test(tc1_1, s21_strerror_4);
  tcase_add_test(tc1_1, s21_strncpy_test_1);
  tcase_add_test(tc1_1, s21_to_upper_test_1);
  tcase_add_test(tc1_1, s21_to_upper_test_2);
  tcase_add_test(tc1_1, s21_to_upper_test_3);
  tcase_add_test(tc1_1, s21_to_lower_test_1);
  tcase_add_test(tc1_1, s21_to_lower_test_2);
  tcase_add_test(tc1_1, s21_insert_test_1);
  tcase_add_test(tc1_1, s21_trim_test_1);
  tcase_add_test(tc1_1, s21_trim_test_2);
  tcase_add_test(tc1_1, s21_trim_test_3);
  tcase_add_test(tc1_1, s21_trim_test_4);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
