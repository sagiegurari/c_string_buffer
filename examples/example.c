#include "string_buffer.h"
#include <stdio.h>


int main()
{
  // init the buffer with predefined size or with a provided size
  // use string_buffer_new for predefined size
  struct StringBuffer *buffer = string_buffer_new_with_options(
    1024, // initial size
    true  // allow resizing
    );

  // different append functions
  string_buffer_append(buffer, 'A');
  string_buffer_append_string(buffer, "12345");
  string_buffer_append_bool(buffer, true);
  string_buffer_append_short(buffer, 150);
  string_buffer_append_unsigned_short(buffer, 150);
  string_buffer_append_int(buffer, 150);
  string_buffer_append_unsigned_int(buffer, 150);
  string_buffer_append_long(buffer, 150);
  string_buffer_append_unsigned_long(buffer, 150);
  string_buffer_append_long_long(buffer, 150);
  string_buffer_append_unsigned_long_long(buffer, 150);
  string_buffer_append_string_with_options(
    buffer,
    "12345",
    1, // offset
    2  // length
    );

  // increase buffer size if needed to ensure capacity
  // and prevent multiple reallocations in case of many
  // append operations
  string_buffer_ensure_capacity(buffer, 10240);

  // shrink the internal buffer to fit the exact value
  // of the current content and prevent using more memory
  // than needed.
  string_buffer_shrink(buffer);

  // get a clone text value of the current buffer content
  char *text = string_buffer_to_string(buffer);
  printf("The Text: %s", text);

  // we can clear the content we have so far and reuse the
  // string buffer instance
  string_buffer_clear(buffer);

  bool is_empty = string_buffer_is_empty(buffer);
  printf("Is Empty: %d", is_empty);

  // once done, free the buffer
  string_buffer_release(buffer);
} /* main */
