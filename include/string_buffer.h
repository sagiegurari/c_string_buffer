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
struct StringBuffer *string_buffer_new_with_size(const long);

bool string_buffer_clear(struct StringBuffer *);
void string_buffer_release(struct StringBuffer *);

bool string_buffer_append(struct StringBuffer *, char);
bool string_buffer_append_string(struct StringBuffer *, char *);
bool string_buffer_append_bool(struct StringBuffer *, bool);
bool string_buffer_append_short(struct StringBuffer *, short);
bool string_buffer_append_int(struct StringBuffer *, int);
bool string_buffer_append_long(struct StringBuffer *, long);
bool string_buffer_append_long_long(struct StringBuffer *, long long);

char *string_buffer_to_string(struct StringBuffer *);

#endif

