#include "test.h"

START_TEST(floor_1) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 13454365;
  s21_set_Scale(&a, 3);
  s21_floor(a, &a);
  b.bits[0] = 13454;
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 13454365;
  s21_set_Scale(&a, 3);
  s21_setSign(&a, 1);
  s21_floor(a, &a);
  b.bits[0] = 13455;
  s21_setSign(&b, 1);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 13454365;
  s21_set_Scale(&a, 8);
  s21_setSign(&a, 1);
  s21_floor(a, &a);
  b.bits[0] = 1;
  s21_setSign(&b, 1);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(floor_4) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 13454365;
  s21_set_Scale(&a, 4);
  s21_setSign(&a, 0);
  s21_floor(a, &a);
  b.bits[0] = 1345;
  s21_setSign(&b, 0);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(round_1) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 13454365;
  s21_set_Scale(&a, 5);
  s21_setSign(&a, 0);
  s21_round(a, &a);
  b.bits[0] = 135;
  s21_setSign(&b, 0);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(round_2) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 13454365;
  s21_set_Scale(&a, 5);
  s21_setSign(&a, 1);
  s21_round(a, &a);
  b.bits[0] = 135;
  s21_setSign(&b, 1);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(round_3) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 13444;
  s21_set_Scale(&a, 2);
  s21_setSign(&a, 1);
  s21_round(a, &a);
  b.bits[0] = 134;
  s21_setSign(&b, 1);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(round_4) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 134445;
  s21_set_Scale(&a, 3);
  s21_setSign(&a, 1);
  s21_round(a, &a);
  b.bits[0] = 135;
  s21_setSign(&b, 1);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(round_5) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 134445;
  s21_set_Scale(&a, 3);
  s21_setSign(&a, 0);
  s21_round(a, &a);
  b.bits[0] = 135;
  s21_setSign(&b, 0);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 134445;
  s21_set_Scale(&a, 3);
  s21_setSign(&a, 0);
  s21_truncate(a, &a);
  b.bits[0] = 134;
  s21_setSign(&b, 0);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 134445;
  s21_set_Scale(&a, 6);
  s21_setSign(&a, 0);
  s21_truncate(a, &a);
  b.bits[0] = 0;
  s21_setSign(&b, 0);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 134445;
  s21_set_Scale(&a, 4);
  s21_setSign(&a, 0);
  s21_truncate(a, &a);
  b.bits[0] = 13;
  s21_setSign(&b, 0);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(truncate_4) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 134445;
  s21_set_Scale(&a, 4);
  s21_setSign(&a, 1);
  s21_truncate(a, &a);
  b.bits[0] = 13;
  s21_setSign(&b, 1);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(truncate_5) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 134445;
  s21_set_Scale(&a, 7);
  s21_setSign(&a, 1);
  s21_truncate(a, &a);
  b.bits[0] = 0;
  s21_setSign(&b, 0);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(negative_1) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 134445;
  s21_set_Scale(&a, 3);
  b = a;
  s21_setSign(&a, 1);
  s21_negate(a, &a);
  s21_setSign(&b, 0);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

START_TEST(negative_2) {
  s21_decimal a, b;
  s21_tozero(&a);
  s21_tozero(&b);
  a.bits[0] = 1423;
  b = a;
  s21_negate(a, &a);
  s21_setSign(&b, 1);
  ck_assert_int_eq(a.bits[0], b.bits[0]);
  ck_assert_int_eq(a.bits[1], b.bits[1]);
  ck_assert_int_eq(a.bits[2], b.bits[2]);
  ck_assert_int_eq(a.bits[3], b.bits[3]);
}
END_TEST

Suite *test_funck(void) {
  Suite *s = suite_create("\033[45m-=s21_funck=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, floor_1);
  tcase_add_test(tc_core, floor_2);
  tcase_add_test(tc_core, floor_3);
  tcase_add_test(tc_core, floor_4);
  tcase_add_test(tc_core, round_1);
  tcase_add_test(tc_core, round_2);
  tcase_add_test(tc_core, round_3);
  tcase_add_test(tc_core, round_4);
  tcase_add_test(tc_core, round_5);
  tcase_add_test(tc_core, truncate_1);
  tcase_add_test(tc_core, truncate_2);
  tcase_add_test(tc_core, truncate_3);
  tcase_add_test(tc_core, truncate_4);
  tcase_add_test(tc_core, truncate_5);
  tcase_add_test(tc_core, negative_1);
  tcase_add_test(tc_core, negative_2);

  suite_add_tcase(s, tc_core);

  return s;
}
