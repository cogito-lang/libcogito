#ifndef COGITO_STATEMENT_PART
#define COGITO_STATEMENT_PART

#include "buffer.h"
#include "linked_list.h"

/**
 * A struct representing either a list of AWS actions or a list of AWS
 * resources. This is used as part of the "ALLOW" or "ON" clauses within an IAM
 * query, and part of the "Action" and "Resource" blocks within an IAM json.
 */
typedef struct cg_stmt_part {
  int negated;
  cg_node_t *head;
} cg_stmt_part_t;

/**
 * Build a new cg_stmt_part_t struct with the given negated flag and linked
 * list.
 */
cg_stmt_part_t* cg_stmt_part_build(int negated, cg_node_t *head);

/**
 * Convert a cg_stmt_part_t struct into a string and push the content into the
 * given buffer.
 */
void cg_stmt_part_to_s(cg_stmt_part_t *stmt_part, cg_buf_t *buffer);

/**
 * Free an allocated cg_stmt_part_t struct.
 */
void cg_stmt_part_free(cg_stmt_part_t *stmt_part);

#endif
