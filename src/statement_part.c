#include "statement_part.h"

cg_stmt_part_t* cg_stmt_part_build(int negated, cg_node_t *head) {
  cg_stmt_part_t *stmt_part = (cg_stmt_part_t *) malloc(sizeof(cg_stmt_part_t));
  stmt_part->negated = negated;
  stmt_part->head = head;
  return stmt_part;
}

void cg_stmt_part_to_s(cg_stmt_part_t *stmt_part, cg_buf_t *buffer) {
  cg_node_t *ptr;

  cg_ll_foreach(stmt_part->head, ptr) {
    cg_buf_append(buffer, ptr->val);

    if (ptr->next != NULL) {
      cg_buf_append(buffer, ",\n");
    }
  }
}

void cg_stmt_part_free(cg_stmt_part_t *stmt_part) {
  cg_ll_free(stmt_part->head);
  free(stmt_part);
}
