#include <cogito.h>

int main() {
  response_t* response = cg_to_json("allow a on b;");
  printf("%s\n", response->message);
  return 0;
}
