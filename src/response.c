#include "response.h"

// Build a response
response_t* cg_response_build(int status, char *message) {
  response_t *response = (response_t*) malloc(sizeof(response_t));
  response->status = status;
  response->message = message;
  return response;
}

// Free a response
void cg_response_free(response_t *response) {
  free(response);
}
