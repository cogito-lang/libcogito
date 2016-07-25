#include <stdio.h>
#include <stdlib.h>
#include "cogito.h"

int main(int argc, char **argv) {
  printf("%s\n", cg_parse(argv[1]));
  return 0;
}
