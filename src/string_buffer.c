#include "string_buffer.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// private functions definitions
bool _clear(struct StringBuffer *);
bool _set_capacity(struct StringBuffer *, const size_t);
bool _append_char(struct StringBuffer *, char);
bool _append_any_type(struct StringBuffer *, const char *, ...);

struct StringBuffer *string_buffer_new()
{
  return(string_buffer_new_with_options(10000, true));
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

  buffer->value = NULL;
  if (!_clear(buffer))
  {
    return(NULL);
  }

  // set lock/unlock to the content size
  buffer->allow_resize = allow_resize;

  return(buffer);
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

  return(_clear(buffer));
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

  return(_set_capacity(buffer, size));
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

  return(_set_capacity(buffer, buffer->content_size));
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

  free(buffer);
}


bool string_buffer_append(struct StringBuffer *buffer, char character)
{
  if (buffer == NULL)
  {
    return(false);
  }

  return(_append_char(buffer, character));
}


bool string_buffer_append_string(struct StringBuffer *buffer, char *string)
{
  if (buffer == NULL)
  {
    return(false);
  }

  if (string == NULL)
  {
    return(true);
  }

  const size_t length = strlen(string);
  for (size_t index = 0; index < length; index++)
  {
    if (!_append_char(buffer, string[index]))
    {
      return(false);
    }
  }

  return(true);
}


char *string_buffer_to_string(struct StringBuffer *buffer)
{
  if (buffer == NULL || buffer->content_size == 0)
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
  return(_append_any_type(buffer, "%hi", value));
}


bool string_buffer_append_int(struct StringBuffer *buffer, int value)
{
  return(_append_any_type(buffer, "%i", value));
}


bool string_buffer_append_long(struct StringBuffer *buffer, long value)
{
  return(_append_any_type(buffer, "%li", value));
}


bool string_buffer_append_long_long(struct StringBuffer *buffer, long long value)
{
  return(_append_any_type(buffer, "%lli", value));
}


bool _clear(struct StringBuffer *buffer)
{
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
  buffer->value    = realloc(buffer->value, buffer->max_size);

  // put null at end
  buffer->value[buffer->max_size] = 0;

  return(true);
}


bool _append_char(struct StringBuffer *buffer, char character)
{
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

  return(true);
}


bool _append_any_type(struct StringBuffer *buffer, const char *format, ...)
{
  va_list args;

  va_start(args, format);
  const int result = vsnprintf(NULL, 0, format, args) + 1;
  if (result < 0)
  {
    va_end(args);
    return(false);
  }

  const size_t size = (size_t)result;
  char         *str = malloc(size);

  vsnprintf(str, size, format, args);

  va_end(args);

  const bool output = string_buffer_append_string(buffer, str);
  free(str);

  return(output);
}

