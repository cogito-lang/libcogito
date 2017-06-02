#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/statement.h"

START_TEST(test_stmt_build)
{
  cg_list_t *actions = cg_ll_build("s3:PutObject");
  cg_list_t *resources = cg_ll_build("s3:::test-bucket*/*");
  statement_t *statement = stmt_build("allow", actions, resources);

  ck_assert_str_eq(statement->macro, "allow");
  ck_assert_str_eq(statement->actions->head->value, "s3:PutObject");
  ck_assert_str_eq(statement->resources->head->value, "s3:::test-bucket*/*");

  stmt_free(statement);
}
END_TEST

Suite* statement_suite(void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_limits;

  s = suite_create("Statement");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_stmt_build);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = statement_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
