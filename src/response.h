#ifndef COGITO_RESPONSE
#define COGITO_RESPONSE

#include <stdlib.h>

typedef struct response {
  int status;
  char *message;
} response_t;

response_t* cg_response_build(int status, char *message);
void cg_response_free(response_t *response);

#endif
