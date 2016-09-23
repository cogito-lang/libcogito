#include <stdio.h>
#include <stdlib.h>
#include "bin-cogito.h"

static void fail(char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
};

static void respond(response_t *response) {
  if (response->status != 0) {
    fail(response->message);
  }
  printf("%s\n", response->message);
}

int main(int argc, char **argv) {
  if (argc > 1 && strcmp(argv[1], "to-iam") == 0) {
    respond(cg_to_iam(argv[2]));
  } else if (argc > 1 && strcmp(argv[1], "to-json") == 0) {
    respond(cg_to_json(argv[2]));
  } else {
    fail("USAGE: cogito <to-json|to-iam> <text>");
  }
  return 0;
}
