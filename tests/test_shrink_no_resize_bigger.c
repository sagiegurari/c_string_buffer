#include "string_buffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(100, false);

  assert_true(string_buffer_append_string(buffer, "12345"));

  assert_num_equal(string_buffer_get_initial_size(buffer), 100);
  assert_num_equal(string_buffer_get_content_size(buffer), 5);
  assert_num_equal(string_buffer_get_max_size(buffer), 100);

  char *content = string_buffer_to_string(buffer);
  assert_string_equal(content, "12345");

  free(content);

  assert_true(!string_buffer_shrink(buffer));

  assert_num_equal(string_buffer_get_initial_size(buffer), 100);
  assert_num_equal(string_buffer_get_content_size(buffer), 5);
  assert_num_equal(string_buffer_get_max_size(buffer), 100);

  content = string_buffer_to_string(buffer);
  assert_string_equal(content, "12345");

  string_buffer_release(buffer);
  free(content);
}


int main()
{
  test_run(test_impl);
}

