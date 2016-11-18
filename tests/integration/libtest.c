#include <cogito.h>

int main() {
  cg_buf_t *buffer = cg_buf_build();
  int response_code = cg_to_json(buffer, "allow a on b;");

  if (!response_code) {
    printf("%s\n", buffer->content);
  }
  return response_code;
}
