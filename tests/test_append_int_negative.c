#include "stringbuffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new_with_options(100, true);

  int                 value = -123456;

  assert_true(stringbuffer_append_int(buffer, value));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 100);
  assert_num_equal(stringbuffer_get_content_size(buffer), 7);
  assert_num_equal(stringbuffer_get_max_size(buffer), 100);

  char *text = stringbuffer_to_string(buffer);
  assert_string_equal(text, "-123456");
  free(text);
  stringbuffer_release(buffer);
}


int main()
{
  test_run(test_impl);
}

