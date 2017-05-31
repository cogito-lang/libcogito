#ifndef COGITO
#define COGITO

#include "src/buffer.h"
#include "src/errors.h"
#include "src/linked_list.h"
#include "src/statement.h"
#include "src/parser.h"

/**
 * Convert the given input string to JSON and copy it onto the given buffer.
 */
int cg_to_json(cg_buf_t *buffer, char *input);

/**
 * Convert the given input string to IAM and copy it onto the given buffer.
 */
int cg_to_iam(cg_buf_t *buffer, char *input);

#endif
