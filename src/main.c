#include <stdio.h>
#include <stdlib.h>
#include "bin-cogito.h"

int main(int argc, char **argv) {
  if (strcmp(argv[1], "to-iam") == 0) {
    printf("%s\n", cg_to_iam(argv[2]));
  } else if (strcmp(argv[1], "to-json") == 0) {
    printf("%s\n", cg_to_json(argv[2]));
  } else {
    fprintf(stderr, "USAGE: cogito <to-json|to-iam> <text>\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}
