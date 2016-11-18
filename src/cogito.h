#ifndef COGITO
#define COGITO

#include "cogito/linked_list.h"
#include "cogito/statement.h"
#include "cogito/parser.h"
#include "cogito/buffer.h"

const int CG_ERR_INVALID_JSON = 1;
const int CG_ERR_JSON_NOT_ARRAY = 2;

int cg_to_json(cg_buf_t *buffer, char *input);
int cg_to_iam(cg_buf_t *buffer, char *input);



#endif
