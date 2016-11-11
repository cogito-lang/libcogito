#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/buffer.h"

START_TEST(test_cg_buf_build)
{
  cg_buf_t *buffer = cg_buf_build();

  ck_assert_int_eq(buffer->length, 0);
  ck_assert_int_eq(buffer->capacity, 256);
  ck_assert_str_eq(buffer->content, "");

  cg_buf_free(buffer);
}
END_TEST

START_TEST(test_cg_buf_append)
{
  cg_buf_t *buffer = cg_buf_build();
  cg_buf_append(buffer, "foobar");

  ck_assert_int_eq(buffer->length, 6);
  ck_assert_str_eq(buffer->content, "foobar");

  cg_buf_free(buffer);
}
END_TEST

START_TEST(test_cg_buf_append_increase)
{
  cg_buf_t *buffer = cg_buf_build();
  cg_buf_append(buffer, "foobar");

  char *addition = "0123456789";
  int idx;

  for (idx = 0; idx < 25; idx++) {
    cg_buf_append(buffer, addition);
  }

  ck_assert_int_eq(buffer->length, 256);
  ck_assert_int_eq(buffer->capacity, 512);

  cg_buf_free(buffer);
}
END_TEST

Suite* buffer_suite(void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_limits;

  s = suite_create("Buffer");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_cg_buf_build);
  tcase_add_test(tc_core, test_cg_buf_append);
  tcase_add_test(tc_core, test_cg_buf_append_increase);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = buffer_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
