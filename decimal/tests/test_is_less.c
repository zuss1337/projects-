#include "test.h"

START_TEST(test_is_less_1) {
  s21_decimal _a, _b;
  int he = -22111;
  int hu = -612234;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

START_TEST(test_is_less_2) {
  s21_decimal _a, _b;
  int he = 22111;
  int hu = 612234;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 1);
}
END_TEST

START_TEST(test_is_less_3) {
  s21_decimal _a, _b;
  int he = 22111;
  int hu = 22111;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

START_TEST(test_is_less_4) {
  s21_decimal _a, _b;
  int he = -22111;
  int hu = 22111;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 1);
}
END_TEST

START_TEST(test_is_less_5) {
  s21_decimal _a, _b;
  int he = 22111;
  int hu = -22111;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

START_TEST(test_is_less_6) {
  s21_decimal _a, _b;
  int he = 1;
  int hu = 1000000;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 1);
}
END_TEST

START_TEST(test_is_less_7) {
  s21_decimal _a, _b;
  int he = 1000000;
  int hu = 1;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

START_TEST(test_is_less_8) {
  s21_decimal _a, _b;
  int he = 1000000000;
  int hu = 999999999;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

START_TEST(test_is_less_9) {
  s21_decimal _a, _b;
  int he = 999999999;
  int hu = 1000000000;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 1);
}
END_TEST

START_TEST(test_is_less_10) {
  s21_decimal _a, _b;
  int he = 2147483647;
  int hu = -2147483647;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

START_TEST(test_is_less_11) {
  s21_decimal _a, _b;
  int he = -2147483647;
  int hu = 2147483647;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 1);
}
END_TEST

START_TEST(test_is_less_12) {
  s21_decimal _a, _b;
  int he = 2147483647;
  int hu = 2147483647;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

START_TEST(test_is_less_13) {
  s21_decimal _a, _b;
  int he = -147483647;
  int hu = -47483647;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 1);
}
END_TEST

START_TEST(test_is_less_14) {
  s21_decimal _a, _b;
  int he = -47483647;
  int hu = -47483647;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

START_TEST(test_is_less_15) {
  s21_decimal _a, _b;
  int he = -97483647;
  int hu = -47483647;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 1);
}
END_TEST

START_TEST(test_is_less_16) {
  s21_decimal _a, _b;
  int he = -17483647;
  int hu = -47483647;
  s21_from_int_to_decimal(he, &_a);
  s21_from_int_to_decimal(hu, &_b);
  ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

Suite *test_is_less(void) {
  Suite *s = suite_create("\033[45m-=s21_is_less=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_less_1);
  tcase_add_test(tc_core, test_is_less_2);
  tcase_add_test(tc_core, test_is_less_3);
  tcase_add_test(tc_core, test_is_less_4);
  tcase_add_test(tc_core, test_is_less_5);
  tcase_add_test(tc_core, test_is_less_6);
  tcase_add_test(tc_core, test_is_less_7);
  tcase_add_test(tc_core, test_is_less_8);
  tcase_add_test(tc_core, test_is_less_9);
  tcase_add_test(tc_core, test_is_less_10);
  tcase_add_test(tc_core, test_is_less_11);
  tcase_add_test(tc_core, test_is_less_12);
  tcase_add_test(tc_core, test_is_less_13);
  tcase_add_test(tc_core, test_is_less_14);
  tcase_add_test(tc_core, test_is_less_15);
  tcase_add_test(tc_core, test_is_less_16);
  suite_add_tcase(s, tc_core);

  return s;
}
