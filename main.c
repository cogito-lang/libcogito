#include <stdio.h>
#include <stdlib.h>
#include "cogito.h"

int main(int argc, char **argv) {
  char output[1000];
  cg_parse(argv[1], output);
  printf("%s\n", output);
  return 0;
}
