#ifndef COGITO_RESPONSE
#define COGITO_RESPONSE

#include <stdlib.h>

typedef struct response {
  int status;
  char *message;
} response_t;

response_t* build_response(int status, char *message);

#endif
