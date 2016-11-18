#include <stdio.h>
#include <stdlib.h>
#include "bin-cogito.h"

static void process(int response) {
  char *message;
  switch (response) {
    case -1:
      message = "USAGE: cogito <to-json|to-iam> <text>";
      break;
    case 1:
      message = "Invalid IAM syntax";
      break;
    case 2:
      message = "Invalid JSON syntax";
      break;
    case 3:
      message = "JSON must be an array";
      break;
  }
  fprintf(stderr, "%s\n", message);
}

int main(int argc, char **argv) {
  cg_buf_t *buffer = cg_buf_build();
  int response;

  if (argc > 1 && strcmp(argv[1], "to-iam") == 0) {
    response = cg_to_iam(buffer, argv[2]);
  } else if (argc > 1 && strcmp(argv[1], "to-json") == 0) {
    response = cg_to_json(buffer, argv[2]);
  } else {
    response = -1;
  }

  if (response) {
    process(response);
  } else {
    printf("%s\n", buffer->content);
  }
  return response;
}
