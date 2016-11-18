#include "buffer.h"

#define COGITO_BUF_INCR sysconf(_SC_PAGESIZE)

cg_buf_t* cg_buf_build(void) {
  cg_buf_t *buffer = (cg_buf_t*) malloc(sizeof(cg_buf_t));
  if (buffer == NULL) {
    return NULL;
  }

  buffer->length = 0;
  buffer->capacity = COGITO_BUF_INCR;
  buffer->content = (char *) malloc(buffer->capacity);

  if (buffer->content == NULL) {
    free(buffer);
    return NULL;
  }

  buffer->content[0] = '\0';
  return buffer;
}

int cg_buf_append(cg_buf_t *buffer, const char *str) {
  size_t append_len = strlen(str);
  if (append_len == 0) {
    return 0;
  }

  size_t new_length = buffer->length + append_len;
  while (new_length >= buffer->capacity) {
    buffer->capacity += COGITO_BUF_INCR;
    buffer->content = (char *) realloc(buffer->content, buffer->capacity);
    if (buffer->content == NULL) {
      return 1;
    }
  }

  size_t idx;
  for (idx = 0; idx < append_len; idx++) {
    buffer->content[buffer->length++] = str[idx];
  }
  buffer->content[buffer->length] = '\0';

  return 0;
}

void cg_buf_free(cg_buf_t *buffer) {
  free(buffer->content);
  free(buffer);
}
