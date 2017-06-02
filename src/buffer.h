#ifndef COGITO_BUFFER
#define COGITO_BUFFER

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * A struct representing an expandable string. Contains the current length of
 * the string, the current capacity of the string, and a pointer to the string
 * itself.
 */
typedef struct {
  size_t length;
  size_t capacity;
  char *content;
} cg_buf_t;

/**
 * Initialize and return a new cg_buf_t struct.
 * @return A newly allocated and initialized buffer struct
 */
cg_buf_t* cg_buf_build(void);

/**
 * Copy a given string onto the given buffer, expanding if necessary.
 * @param buffer The buffer on which to append
 * @param str The string to append onto the buffer
 * @return An integer describing success (0 for success, 1 for failure)
 */
int cg_buf_append(cg_buf_t *buffer, const char *str);

/**
 * Free the allocated buffer and its associated string.
 * @param buffer The buffer to free
 */
void cg_buf_free(cg_buf_t *buffer);

#endif
