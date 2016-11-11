#ifndef COGITO_BUF
#define COGITO_BUF

typedef struct cg_buf {
  size_t length;
  size_t capacity;
  char *content;
} cg_buf_t;

cg_buf_t* cg_buf_build(char *str);
void cg_buf_append(cg_buf_t *buffer, char *str);
void cg_buf_free(cg_buf_t *buffer);

#endif
