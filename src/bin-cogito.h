#ifndef COGITO
#define COGITO

#include "src/buffer.h"
#include "src/errors.h"
#include "src/list.h"
#include "src/statement.h"
#include "src/parser.h"

int cg_to_json(cg_buf_t *buffer, char *input);
int cg_to_iam(cg_buf_t *buffer, char *input);

#endif
