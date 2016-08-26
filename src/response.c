#include "response.h"

// Build a response
response_t* build_response(int status, char *message) {
  response_t *response = (response_t*) malloc(sizeof(response_t));
  response->status = status;
  response->message = message;
  return response;
}
