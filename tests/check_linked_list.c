#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/linked_list.h"

START_TEST(test_cg_ll_append)
{
  cg_list_t *list = cg_ll_build("head");
  cg_ll_append(list, "tail");

  ck_assert_str_eq(list->head->next->val, "tail");
  cg_ll_free(list);
}
END_TEST

START_TEST(test_cg_ll_update)
{
  cg_list_t *list = cg_ll_update(NULL, "head");
  ck_assert_str_eq(list->head->val, "head");
  cg_ll_update(list, "tail");

  ck_assert_str_eq(list->head->next->val, "tail");
  cg_ll_free(list);
}
END_TEST

START_TEST(test_cg_ll_build)
{
  cg_list_t *list = cg_ll_build("head");

  ck_assert_str_eq(list->head->val, "head");
  cg_ll_free(list);
}
END_TEST

START_TEST(test_cg_ll_val_size_sum)
{
  cg_list_t *list = cg_ll_build("head");
  cg_ll_append(list, "this is the body");
  cg_ll_append(list, "tail");

  size_t sum = cg_ll_val_size_sum(list);
  ck_assert_int_eq(sum, 24);
  cg_ll_free(list);
}
END_TEST

Suite* linked_list_suite(void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_limits;

  s = suite_create("Linked List");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_cg_ll_append);
  tcase_add_test(tc_core, test_cg_ll_update);
  tcase_add_test(tc_core, test_cg_ll_build);
  tcase_add_test(tc_core, test_cg_ll_val_size_sum);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = linked_list_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
