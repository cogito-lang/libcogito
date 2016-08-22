#ifndef __SMART_STRING_H__
#define __SMART_STRING_H__

#include <stddef.h>
#include <stdbool.h>

#define SMART_STRING_FUNC(name, ...) \
  smart_string_##name(SmartString* ss, __VA_ARGS__)

#if defined _WIN32
  #define FORMAT_ATTR(x, y)
#else
  #define FORMAT_ATTR(x, y) __attribute__ ((format (printf, x, y)))
#endif

typedef struct SmartString {
  size_t length;
  size_t capacity;
  char* buffer;
} SmartString;


#if defined _WIN32
  #define SMART_STRING_PUBLIC __declspec(dllexport)
#else
  #define SMART_STRING_PUBLIC __attribute__ ((visibility("default")))
#endif

#define SMART_STRING_API SMART_STRING_PUBLIC

extern SMART_STRING_API SmartString* smart_string_new(void);
extern SMART_STRING_API bool smart_string_append(SmartString* ss, const char* str);
extern SMART_STRING_API bool FORMAT_ATTR(2, 3) smart_string_append_sprintf(SmartString* ss, const char* format, ...);
extern SMART_STRING_API void smart_string_destroy(SmartString* ss);

#endif
