#include "string_buffer.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_BUFFER_WORK_BUFFER_SIZE    21

struct StringBuffer
{
  size_t initial_size;
  size_t content_size;
  size_t max_size;
  char   *value;
  bool   allow_resize;
  char   *work_buffer;
};

// private functions definitions
static bool _string_buffer_clear(struct StringBuffer *);
static bool _string_buffer_set_capacity(struct StringBuffer *, const size_t);
static bool _string_buffer_add_numeric_type(struct StringBuffer *, const char *, ...);

struct StringBuffer *string_buffer_new()
{
  return(string_buffer_new_with_options(STRING_BUFFER_INITIAL_BUFFER_SIZE, true));
}


struct StringBuffer *string_buffer_new_with_options(const size_t initial_size, const bool allow_resize)
{
  size_t size = 1;

  if (initial_size > 0)
  {
    size = initial_size;
  }

  struct StringBuffer *buffer = malloc(sizeof(struct StringBuffer));

  if (buffer == NULL)
  {
    return(NULL);
  }

  buffer->initial_size = size;
  buffer->content_size = 0;
  buffer->work_buffer  = malloc(STRING_BUFFER_WORK_BUFFER_SIZE * sizeof(char));

  buffer->value = NULL;
  if (!_string_buffer_clear(buffer))
  {
    string_buffer_release(buffer);
    return(NULL);
  }

  // set lock/unlock to the content size
  buffer->allow_resize = allow_resize;

  return(buffer);
}


bool string_buffer_is_empty(struct StringBuffer *buffer)
{
  return(buffer->content_size == 0);
}


size_t string_buffer_get_initial_size(struct StringBuffer *buffer)
{
  return(buffer->initial_size);
}


size_t string_buffer_get_content_size(struct StringBuffer *buffer)
{
  return(buffer->content_size);
}


size_t string_buffer_get_max_size(struct StringBuffer *buffer)
{
  return(buffer->max_size);
}


bool string_buffer_is_allow_resize(struct StringBuffer *buffer)
{
  return(buffer->allow_resize);
}


bool string_buffer_clear(struct StringBuffer *buffer)
{
  if (buffer == NULL)
  {
    return(false);
  }

  // already empty
  if (buffer->content_size == 0)
  {
    return(true);
  }

  return(_string_buffer_clear(buffer));
}


bool string_buffer_ensure_capacity(struct StringBuffer *buffer, const size_t size)
{
  if (buffer == NULL)
  {
    return(false);
  }

  if (size <= buffer->max_size)
  {
    return(true);
  }

  return(_string_buffer_set_capacity(buffer, size));
}


bool string_buffer_shrink(struct StringBuffer *buffer)
{
  if (buffer == NULL)
  {
    return(false);
  }

  if (buffer->content_size == buffer->max_size)
  {
    return(true);
  }

  return(_string_buffer_set_capacity(buffer, buffer->content_size));
}


void string_buffer_release(struct StringBuffer *buffer)
{
  if (buffer == NULL)
  {
    return;
  }

  if (buffer->value != NULL)
  {
    free(buffer->value);
    buffer->value = NULL;
  }

  if (buffer->work_buffer != NULL)
  {
    free(buffer->work_buffer);
    buffer->work_buffer = NULL;
  }

  free(buffer);
}


bool string_buffer_append(struct StringBuffer *buffer, char character)
{
  if (buffer == NULL)
  {
    return(false);
  }

  if (buffer->content_size == buffer->max_size)
  {
    const size_t new_size = buffer->content_size * 2;
    if (!_string_buffer_set_capacity(buffer, new_size))
    {
      return(false);
    }
  }

  buffer->value[buffer->content_size] = character;
  buffer->content_size++;
  buffer->value[buffer->content_size] = 0;

  return(true);
}


bool string_buffer_append_string(struct StringBuffer *buffer, char *string)
{
  if (string == NULL)
  {
    return(true);
  }

  const size_t length = strlen(string);

  return(string_buffer_append_string_with_options(buffer, string, 0, length));
}


bool string_buffer_append_string_with_options(struct StringBuffer *buffer, char *string, const size_t offset, const size_t length)
{
  if (buffer == NULL)
  {
    return(false);
  }

  if (string == NULL)
  {
    return(true);
  }

  const size_t string_length = strlen(string);
  if (offset >= string_length)
  {
    return(false);
  }

  if ((string_length - offset) < length)
  {
    return(false);
  }

  return(string_buffer_append_binary(buffer, string, offset, length));
} /* string_buffer_append_string_with_options */


bool string_buffer_append_binary(struct StringBuffer *buffer, char *content, const size_t offset, const size_t length)
{
  if (buffer == NULL)
  {
    return(false);
  }

  if (content == NULL)
  {
    return(true);
  }

  const size_t loop_end = length + offset;

  const size_t size_left = buffer->max_size - buffer->content_size;
  if (size_left < length)
  {
    const size_t min_new_size = buffer->content_size + length;
    size_t       new_size     = buffer->max_size * 2;
    while (new_size < min_new_size)
    {
      new_size = new_size * 2;
    }

    if (!_string_buffer_set_capacity(buffer, new_size))
    {
      return(false);
    }
  }

  for (size_t index = offset, content_index = 0; index < loop_end; index++, content_index++)
  {
    buffer->value[buffer->content_size] = content[index];
    buffer->content_size++;
  }

  buffer->value[buffer->content_size] = 0;

  return(true);
}


char *string_buffer_to_string(struct StringBuffer *buffer)
{
  if (buffer == NULL || buffer->content_size == 0)
  {
    char *string_copy = malloc(sizeof(char));
    if (string_copy == NULL)
    {
      return(NULL);
    }
    string_copy[0] = 0;
    return(string_copy);
  }

  size_t content_size = buffer->content_size;
  size_t memory_size  = (content_size + 1) * sizeof(char);
  char   *string_copy = malloc(memory_size);
  if (string_copy == NULL)
  {
    return(NULL);
  }

  buffer->value[content_size] = 0;
  string_copy[content_size]   = 0;

  memcpy(string_copy, buffer->value, memory_size);
  string_copy[content_size] = 0;

  return(string_copy);
}


bool string_buffer_append_bool(struct StringBuffer *buffer, bool value)
{
  char *string = value ? "true" : "false";

  return(string_buffer_append_string(buffer, string));
}


bool string_buffer_append_short(struct StringBuffer *buffer, short value)
{
  return(_string_buffer_add_numeric_type(buffer, "%hi", value));
}


bool string_buffer_append_int(struct StringBuffer *buffer, int value)
{
  return(_string_buffer_add_numeric_type(buffer, "%i", value));
}


bool string_buffer_append_long(struct StringBuffer *buffer, long value)
{
  return(_string_buffer_add_numeric_type(buffer, "%li", value));
}


bool string_buffer_append_long_long(struct StringBuffer *buffer, long long value)
{
  return(_string_buffer_add_numeric_type(buffer, "%lli", value));
}


bool string_buffer_append_unsigned_short(struct StringBuffer *buffer, unsigned short value)
{
  return(_string_buffer_add_numeric_type(buffer, "%hu", value));
}


bool string_buffer_append_unsigned_int(struct StringBuffer *buffer, unsigned int value)
{
  return(_string_buffer_add_numeric_type(buffer, "%u", value));
}


bool string_buffer_append_unsigned_long(struct StringBuffer *buffer, unsigned long value)
{
  return(_string_buffer_add_numeric_type(buffer, "%lu", value));
}


bool string_buffer_append_unsigned_long_long(struct StringBuffer *buffer, unsigned long long value)
{
  return(_string_buffer_add_numeric_type(buffer, "%llu", value));
}


static bool _string_buffer_clear(struct StringBuffer *buffer)
{
  if (buffer == NULL)
  {
    return(false);
  }

  if (buffer->value != NULL)
  {
    free(buffer->value);
    buffer->value = NULL;
  }

  buffer->max_size     = buffer->initial_size;
  buffer->content_size = 0;

  buffer->value = malloc((buffer->max_size + 1) * sizeof(char));
  if (buffer->value == NULL)
  {
    string_buffer_release(buffer);
    return(false);
  }

  buffer->value[0]                = 0;
  buffer->value[buffer->max_size] = 0;

  return(true);
}


static bool _string_buffer_set_capacity(struct StringBuffer *buffer, const size_t size)
{
  if (!buffer->allow_resize)
  {
    return(false);
  }

  buffer->max_size = size;
  buffer->value    = realloc(buffer->value, (buffer->max_size + 1) * sizeof(char));

  // put null at end
  buffer->value[buffer->content_size] = 0;
  buffer->value[buffer->max_size]     = 0;

  return(true);
}


static bool _string_buffer_add_numeric_type(struct StringBuffer *buffer, const char *format, ...)
{
  if (buffer == NULL)
  {
    return(false);
  }

  va_list   args;
  va_start(args, format);
  const int length = vsnprintf(buffer->work_buffer, STRING_BUFFER_WORK_BUFFER_SIZE, format, args);
  va_end(args);

  if (length <= 0)
  {
    return(false);
  }

  const bool result = string_buffer_append_string_with_options(buffer, buffer->work_buffer, 0, (size_t)length);

  return(result);
}

