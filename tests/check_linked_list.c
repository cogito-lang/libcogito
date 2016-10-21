#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/linked_list.h"

node_t *head;

void setup(void)
{
  head = ll_build("head");
}

void teardown(void)
{
  ll_free(head);
}

START_TEST(test_linked_list_append)
{
  ll_append(head, "tail");
  ck_assert_str_eq(head->next->val, "tail");
}
END_TEST

Suite * linked_list_suite(void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_limits;

  s = suite_create("Linked List");
  tc_core = tcase_create("Core");

  tcase_add_checked_fixture(tc_core, setup, teardown);
  tcase_add_test(tc_core, test_linked_list_append);
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
