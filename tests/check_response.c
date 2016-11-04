#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/response.h"

START_TEST(test_cg_response_build)
{
  response_t *response = cg_response_build(5, "foobar");
  ck_assert_int_eq(response->status, 5);
  ck_assert_str_eq(response->message, "foobar");
  cg_response_free(response);
}
END_TEST

Suite* response_suite(void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_limits;

  s = suite_create("Response");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_cg_response_build);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = response_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
