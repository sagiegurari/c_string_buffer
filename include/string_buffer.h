#ifndef __STRING_BUFFER_H__
#define __STRING_BUFFER_H__

#include <stdbool.h>

struct StringBuffer
{
  unsigned long initial_size;
  unsigned long content_size;
  unsigned long max_size;
  char          *value;
};

struct StringBuffer *string_buffer_new();
struct StringBuffer *string_buffer_new_with_size(const long initial_size);

bool string_buffer_clear(struct StringBuffer *buffer);
void string_buffer_release(struct StringBuffer *buffer);

bool string_buffer_append(struct StringBuffer *buffer, char character);
bool string_buffer_append_string(struct StringBuffer *buffer, char *string);
bool string_buffer_append_string_with_size(struct StringBuffer *buffer, char *string, int size);

char *string_buffer_to_string(struct StringBuffer *buffer);

#endif

