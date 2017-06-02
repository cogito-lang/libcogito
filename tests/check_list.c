#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/list.h"

START_TEST(test_cg_list_append)
{
  cg_list_t *list = cg_list_build("head");
  cg_list_append(list, "tail");

  ck_assert_str_eq(list->head->next->value, "tail");
  cg_list_free(list);
}
END_TEST

START_TEST(test_cg_list_update)
{
  cg_list_t *list = cg_list_update(NULL, "head");
  ck_assert_str_eq(list->head->value, "head");
  cg_list_update(list, "tail");

  ck_assert_str_eq(list->head->next->value, "tail");
  cg_list_free(list);
}
END_TEST

START_TEST(test_cg_list_build)
{
  cg_list_t *list = cg_list_build("head");

  ck_assert_str_eq(list->head->value, "head");
  cg_list_free(list);
}
END_TEST

START_TEST(test_cg_list_value_size_sum)
{
  cg_list_t *list = cg_list_build("head");
  cg_list_append(list, "this is the body");
  cg_list_append(list, "tail");

  size_t sum = cg_list_value_size_sum(list);
  ck_assert_int_eq(sum, 24);
  cg_list_free(list);
}
END_TEST

Suite* list_suite(void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_limits;

  s = suite_create("Linked List");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_cg_list_append);
  tcase_add_test(tc_core, test_cg_list_update);
  tcase_add_test(tc_core, test_cg_list_build);
  tcase_add_test(tc_core, test_cg_list_value_size_sum);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = list_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
