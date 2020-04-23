#include "string_buffer.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StringBuffer
{
  bool   released;
  size_t initial_size;
  size_t content_size;
  size_t max_size;
  char   *value;
  bool   allow_resize;
  char   *work_buffer;
};

// private functions definitions
bool _clear(struct StringBuffer *);
bool _set_capacity(struct StringBuffer *, const size_t);
bool _add_numeric_type(struct StringBuffer *, const size_t, const char *, ...);

struct StringBuffer *string_buffer_new()
{
  return(string_buffer_new_with_options(10240, true));
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

  buffer->released     = false;
  buffer->initial_size = size;
  buffer->content_size = 0;
  buffer->work_buffer  = malloc(21 * sizeof(char));

  buffer->value = NULL;
  if (!_clear(buffer))
  {
    string_buffer_release(buffer);
    return(NULL);
  }

  // set lock/unlock to the content size
  buffer->allow_resize = allow_resize;

  return(buffer);
}


bool string_buffer_is_released(struct StringBuffer *buffer)
{
  return(buffer == NULL || buffer->released);
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


bool  string_buffer_is_allow_resize(struct StringBuffer *buffer)
{
  return(buffer->allow_resize);
}


bool string_buffer_clear(struct StringBuffer *buffer)
{
  if (string_buffer_is_released(buffer))
  {
    return(false);
  }

  // already empty
  if (buffer->content_size == 0)
  {
    return(true);
  }

  return(_clear(buffer));
}


bool string_buffer_ensure_capacity(struct StringBuffer *buffer, const size_t size)
{
  if (string_buffer_is_released(buffer))
  {
    return(false);
  }

  if (size <= buffer->max_size)
  {
    return(true);
  }

  return(_set_capacity(buffer, size));
}


bool string_buffer_shrink(struct StringBuffer *buffer)
{
  if (string_buffer_is_released(buffer))
  {
    return(false);
  }

  if (buffer->content_size == buffer->max_size)
  {
    return(true);
  }

  return(_set_capacity(buffer, buffer->content_size));
}


void string_buffer_release(struct StringBuffer *buffer)
{
  if (string_buffer_is_released(buffer))
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

  buffer->released = true;

  free(buffer);
}


bool string_buffer_append(struct StringBuffer *buffer, char character)
{
  if (string_buffer_is_released(buffer))
  {
    return(false);
  }

  if (buffer->content_size == buffer->max_size)
  {
    const size_t new_size = buffer->content_size * 2;
    if (!_set_capacity(buffer, new_size))
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
  if (string_buffer_is_released(buffer))
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

    if (!_set_capacity(buffer, new_size))
    {
      return(false);
    }
  }

  for (size_t index = offset, content_index = 0; index < loop_end; index++, content_index++)
  {
    buffer->value[buffer->content_size] = string[index];
    buffer->content_size++;
  }

  buffer->value[buffer->content_size] = 0;

  return(true);
} /* string_buffer_append_string_with_options */


char *string_buffer_to_string(struct StringBuffer *buffer)
{
  if (string_buffer_is_released(buffer) || buffer->content_size == 0)
  {
    return("");
  }

  size_t string_size  = buffer->content_size * sizeof(char);
  char   *string_copy = malloc(string_size);
  if (string_copy == NULL)
  {
    return(NULL);
  }

  buffer->value[string_size] = 0;

  string_copy              = strcpy(string_copy, buffer->value);
  string_copy[string_size] = 0;

  return(string_copy);
}


bool string_buffer_append_bool(struct StringBuffer *buffer, bool value)
{
  char *string = value ? "true" : "false";

  return(string_buffer_append_string(buffer, string));
}


bool string_buffer_append_short(struct StringBuffer *buffer, short value)
{
  return(_add_numeric_type(buffer, 7, "%hi", value));
}


bool string_buffer_append_int(struct StringBuffer *buffer, int value)
{
  return(_add_numeric_type(buffer, 12, "%i", value));
}


bool string_buffer_append_long(struct StringBuffer *buffer, long value)
{
  return(_add_numeric_type(buffer, 12, "%li", value));
}


bool string_buffer_append_long_long(struct StringBuffer *buffer, long long value)
{
  return(_add_numeric_type(buffer, 21, "%lli", value));
}


bool _clear(struct StringBuffer *buffer)
{
  if (string_buffer_is_released(buffer))
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

  buffer->value = malloc(buffer->max_size * sizeof(char));
  if (buffer->value == NULL)
  {
    string_buffer_release(buffer);
    return(false);
  }

  buffer->value[buffer->max_size] = 0;

  return(true);
}


bool _set_capacity(struct StringBuffer *buffer, const size_t size)
{
  if (!buffer->allow_resize)
  {
    return(false);
  }

  buffer->max_size = size;
  buffer->value    = realloc(buffer->value, buffer->max_size * sizeof(char));

  // put null at end
  buffer->value[buffer->max_size] = 0;

  return(true);
}


bool _add_numeric_type(struct StringBuffer *buffer, const size_t size, const char *format, ...)
{
  if (string_buffer_is_released(buffer))
  {
    return(false);
  }

  va_list   args;
  va_start(args, format);
  const int length = vsnprintf(buffer->work_buffer, size, format, args);
  va_end(args);

  if (length <= 0)
  {
    return(false);
  }

  const bool result = string_buffer_append_string_with_options(buffer, buffer->work_buffer, 0, (size_t)length);

  return(result);
}

