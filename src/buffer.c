#include "buffer.h"

#define COGITO_BUF_INCR 256

cg_buf_t* cg_buf_build() {
  cg_buf_t *buffer = (cg_buf_t*) malloc(sizeof(cg_buf_t));
  buffer->length = 0;
  buffer->capacity = COGITO_BUF_INCR;
  buffer->content = (char *) malloc(buffer->capacity);
  buffer->content[0] = '\0';
  return buffer;
}

void cg_buf_append(cg_buf_t *buffer, char *str) {
  size_t str_len = strlen(str);
  if (str_len == 0) {
    return;
  }

  size_t new_length = buffer->length + str_len;
  while (new_length >= buffer->capacity) {
    buffer->capacity += COGITO_BUF_INCR;
    buffer->content = (char *) realloc(buffer->content, buffer->capacity);
  }

  size_t idx;
  for (idx = 0; idx < str_len; idx++) {
    buffer->content[buffer->length++] = str[idx];
  }
  buffer->content[buffer->length] = '\0';
}

void cg_buf_free(cg_buf_t *buffer) {
  free(buffer->content);
  free(buffer);
}
