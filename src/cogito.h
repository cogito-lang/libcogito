#ifndef COGITO
#define COGITO

#include "cogito/linked_list.h"
#include "cogito/statement.h"
#include "cogito/parser.h"

response_t* cg_to_json(char *input);
response_t* cg_to_iam(char *input);

#endif
