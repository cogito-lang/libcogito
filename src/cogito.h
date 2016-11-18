#ifndef COGITO
#define COGITO

#include "cogito/buffer.h"
#include "cogito/linked_list.h"
#include "cogito/statement.h"
#include "cogito/parser.h"

int cg_to_json(cg_buf_t *buffer, char *input);
int cg_to_iam(cg_buf_t *buffer, char *input);

#endif
