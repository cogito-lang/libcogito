#ifndef COGITO
#define COGITO

#include "cogito/buffer.h"
#include "cogito/list.h"
#include "cogito/statement.h"
#include "cogito/parser.h"

/**
 * Convert the given input string to JSON and copy it onto the given buffer.
 * @param buffer The buffer on which to copy the converted JSON
 * @param input The input string in IAM format
 * @return An integer describing success (0 for success, error code for failure)
 */
int cg_to_json(cg_buf_t *buffer, char *input);

/**
 * Convert the given input string to IAM and copy it onto the given buffer.
 * @param buffer The buffer on which to copy the converted JSON
 * @param input The input string in JSON format
 * @return An integer describing success (0 for success, error code for failure)
 */
int cg_to_iam(cg_buf_t *buffer, char *input);

#endif
