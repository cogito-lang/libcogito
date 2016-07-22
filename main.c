#include <stdio.h>
#include <stdlib.h>
#include "src/linked-list.h"
#include "src/statement.h"
#include "parser.tab.h"

extern int cg_parse(char *filepath);

int main(int argc, char **argv) {
  return cg_parse(argv[1]);
}
