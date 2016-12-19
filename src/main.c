#include <stdio.h>
#include <stdlib.h>
#include "bin-cogito.h"

#define CG_ERR_USAGE -1

static void process(int response) {
  char *message;
  switch (response) {
    case CG_ERR_USAGE:
      message = "USAGE: cogito <to-json|to-iam> <text>";
      break;
    case CG_ERR_INVALID_IAM:
      message = "Invalid IAM syntax";
      break;
    case CG_ERR_INVALID_JSON:
      message = "Invalid JSON syntax";
      break;
    case CG_ERR_JSON_NOT_ARRAY:
      message = "JSON must be an array";
      break;
    case CG_ERR_INVALID_ACTION:
      message = "Action must be a string or an array";
      break;
    case CG_ERR_INVALID_RESOURCE:
      message = "Resource must be a string or an array";
      break;
  }
  fprintf(stderr, "%s\n", message);
}

int main(int argc, char **argv) {
  cg_buf_t *buffer = cg_buf_build();
  int response;

  if (argc == 3 && strcmp(argv[1], "to-iam") == 0) {
    response = cg_to_iam(buffer, argv[2]);
  } else if (argc == 3 && strcmp(argv[1], "to-json") == 0) {
    response = cg_to_json(buffer, argv[2]);
  } else {
    response = CG_ERR_USAGE;
  }

  if (response) {
    process(response);
  } else {
    printf("%s\n", buffer->content);
  }
  return response;
}
