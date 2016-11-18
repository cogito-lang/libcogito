#ifndef COGITO_BUF
#define COGITO_BUF

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct cg_buf {
  size_t length;
  size_t capacity;
  char *content;
} cg_buf_t;

cg_buf_t* cg_buf_build(void);
int cg_buf_append(cg_buf_t *buffer, const char *str);
void cg_buf_free(cg_buf_t *buffer);

#endif
