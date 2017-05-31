#ifndef COGITO
#define COGITO

#include "cogito/buffer.h"
#include "cogito/linked_list.h"
#include "cogito/statement.h"
#include "cogito/parser.h"

/**
 * Convert the given input string to JSON and copy it onto the given buffer.
 */
int cg_to_json(cg_buf_t *buffer, char *input);

/**
 * Convert the given input string to IAM and copy it onto the given buffer.
 */
int cg_to_iam(cg_buf_t *buffer, char *input);

#endif
