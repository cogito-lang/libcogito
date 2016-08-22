#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "smart_string.h"

#define D_SMART_STRING_SIZE 16

SMART_STRING_API SmartString* smart_string_new(void)
{

  SmartString* ss;
  if ((ss = (SmartString* )malloc(sizeof(SmartString))) == NULL) {
    return NULL;
  }
  ss->length = 0;
  ss->capacity = D_SMART_STRING_SIZE;
  if ((ss->buffer = (char *)malloc(ss->capacity)) == NULL) {
    free(ss);
    return NULL;
  }
  ss->buffer[ss->length] = '\0';
  return ss;
}

SMART_STRING_API
bool SMART_STRING_FUNC(append, const char* str)
{
  if (ss == NULL) { return false; }
  if (str == NULL) { return false; }

  size_t part_length = strlen(str);
  size_t i;
  size_t current_position;
  size_t new_length;

  if (part_length == 0) {
    return true;
  }

  new_length = part_length + ss->length;
  current_position = ss->length;

  if (new_length >= ss->capacity) {
    while (new_length >= ss->capacity) {
      ss->capacity *= 2;
      if ((ss->buffer = (char *)realloc(ss->buffer, ss->capacity)) == NULL) {
        return false;
      }
    }
  }

  for (i = 0; i < part_length; i++) {
    ss->buffer[current_position++] = str[i];
  }

  ss->length = new_length;
  ss->buffer[current_position] = '\0';

  return true;
}

SMART_STRING_API
bool FORMAT_ATTR(2, 3) SMART_STRING_FUNC(append_sprintf, const char* format, ...)
{
  if ((ss == NULL) || (format == NULL)) { return false; }
  if (strlen(format) == 0) {
    return true;
  }

  va_list args;
  int buffer_size = D_SMART_STRING_SIZE;
  char* buffer, *buffer2;
  int n;
  if ((buffer = (char *)malloc(buffer_size)) == NULL) {
    return false;
  }

  for (;;) {
    va_start(args, format);
    #ifdef _WIN32
        n = vsprintf_s(buffer, buffer_size, format, args);
    #else
        n = vsnprintf(buffer, buffer_size, format, args);
    #endif
    va_end(args);

    if (n < 0) {
      free(buffer);
      return false;
    }

    if (n < buffer_size) {
      smart_string_append(ss, buffer);
      free(buffer);
      return true;
    }

    buffer_size = buffer_size + 1;

    if ((buffer2 = (char *)realloc(buffer, buffer_size)) == NULL) {
      free(buffer);
      return false;
    }
    else {
      buffer = buffer2;
    }
  }

  return false;

}

SMART_STRING_API
void smart_string_destroy(SmartString* ss)
{
  if (ss == NULL) {
    return;
  }
  #ifdef DEBUG
  printf("%s(): destroying SmartString instance : \n", __func__);
  printf("SmartString {\n");
  printf("\tlength   = %zu\n", ss->length);
  printf("\tcapacity = %zu\n", ss->capacity);
  if (ss->buffer != NULL) {
    printf("\tbuffer   = \"%s\"\n", ss->buffer);
  }
  printf("}\n");
  #endif
  if (ss->buffer != NULL) {
    free(ss->buffer);
  }

  free(ss);
}
