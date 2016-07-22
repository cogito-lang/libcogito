#include <stdio.h>
#include <stdlib.h>
#include "src/linked-list.h"
#include "src/statement.h"
#include "parser.tab.h"

void cg_parse(char *input, char *output);

int main(int argc, char **argv) {
  char output[1000];
  cg_parse(argv[1], output);
  printf("%s\n", output);
  return 0;
}
