#include "stringbuffer.h"
#include <stdio.h>


int main()
{
  // init the buffer with predefined size or with a provided size
  // use stringbuffer_new for predefined size
  struct StringBuffer *buffer = stringbuffer_new_with_options(
    1024, // initial size
    true  // allow resizing
    );

  // different append functions
  stringbuffer_append(buffer, 'A');
  stringbuffer_append_string(buffer, "12345");
  stringbuffer_append_bool(buffer, true);
  stringbuffer_append_short(buffer, 150);
  stringbuffer_append_unsigned_short(buffer, 150);
  stringbuffer_append_int(buffer, 150);
  stringbuffer_append_unsigned_int(buffer, 150);
  stringbuffer_append_long(buffer, 150);
  stringbuffer_append_unsigned_long(buffer, 150);
  stringbuffer_append_long_long(buffer, 150);
  stringbuffer_append_unsigned_long_long(buffer, 150);
  stringbuffer_append_string_with_options(
    buffer,
    "12345",
    1, // offset
    2  // length
    );

  // increase buffer size if needed to ensure capacity
  // and prevent multiple reallocations in case of many
  // append operations
  stringbuffer_ensure_capacity(buffer, 10240);

  // shrink the internal buffer to fit the exact value
  // of the current content and prevent using more memory
  // than needed.
  stringbuffer_shrink(buffer);

  // get a clone text value of the current buffer content
  char *text = stringbuffer_to_string(buffer);
  printf("The Text: %s\n", text);

  // we can clear the content we have so far and reuse the
  // string buffer instance
  stringbuffer_clear(buffer);

  bool is_empty = stringbuffer_is_empty(buffer);
  printf("Is Empty: %d\n", is_empty);

  // once done, free the buffer
  stringbuffer_release(buffer);
} /* main */
