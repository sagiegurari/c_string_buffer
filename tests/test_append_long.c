#include "string_buffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(100, true);

  long                value = 150;

  assert_true(string_buffer_append_long(buffer, value));

  assert_num_equal(string_buffer_get_initial_size(buffer), 100);
  assert_num_equal(string_buffer_get_content_size(buffer), 3);
  assert_num_equal(string_buffer_get_max_size(buffer), 100);

  char *content = string_buffer_to_string(buffer);
  assert_string_equal(content, "150");

  string_buffer_release(buffer);
  free(content);
}


int main()
{
  test_run(test_impl);
}

