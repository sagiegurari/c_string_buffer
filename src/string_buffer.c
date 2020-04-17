#include "string_buffer.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// private functions definitions
void _append_char(struct StringBuffer *, char);
bool _append_any_type(struct StringBuffer *, const char *, ...);

struct StringBuffer *string_buffer_new()
{
  return(string_buffer_new_with_size(10000));
}


struct StringBuffer *string_buffer_new_with_size(const long initial_size)
{
  long size = 1;

  if (initial_size >= 1)
  {
    size = initial_size;
  }

  struct StringBuffer *buffer = malloc(sizeof(struct StringBuffer));
  if (buffer == NULL)
  {
    return(NULL);
  }

  buffer->initial_size = size;
  buffer->content_size = -1;

  buffer->value = NULL;
  if (!string_buffer_clear(buffer))
  {
    return(NULL);
  }

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

  _append_char(buffer, character);
  return(true);
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

  int length = strlen(string);
  for (int index = 0; index < length; index++)
  {
    _append_char(buffer, string[index]);
  }

  return(true);
}


char *string_buffer_to_string(struct StringBuffer *buffer)
{
  if (buffer == NULL || buffer->content_size == 0)
  {
    return("");
  }

  unsigned long string_size  = buffer->content_size * sizeof(char);
  char          *string_copy = malloc(string_size);
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


void _append_char(struct StringBuffer *buffer, char character)
{
  if (buffer->content_size == buffer->max_size)
  {
    buffer->max_size = buffer->content_size * 2;
    buffer->value    = realloc(buffer->value, buffer->max_size);

    // put null at end
    buffer->value[buffer->content_size * 2] = 0;
  }

  buffer->value[buffer->content_size] = character;
  buffer->content_size++;
}


bool _append_any_type(struct StringBuffer *buffer, const char *format, ...)
{
  va_list args;

  va_start(args, format);
  int  size = vsnprintf(NULL, 0, format, args) + 1;
  char *str = malloc(size);

  vsnprintf(str, size, format, args);

  va_end(args);

  const bool output = string_buffer_append_string(buffer, str);
  free(str);

  return(output);
}

