#ifndef COGITO
#define COGITO

#include "src/linked_list.h"
#include "src/statement.h"
#include "src/parser.h"

response_t* cg_to_json(char *input);
response_t* cg_to_iam(char *input);

#endif
