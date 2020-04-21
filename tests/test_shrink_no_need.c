#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(5, true);

  assert_true(string_buffer_append_string(buffer, "12345"));

  assert_num_equal(string_buffer_get_initial_size(buffer), 5);
  assert_num_equal(string_buffer_get_content_size(buffer), 5);
  assert_num_equal(string_buffer_get_max_size(buffer), 5);
  assert_string_equal(string_buffer_to_string(buffer), "12345");

  assert_true(string_buffer_shrink(buffer));

  assert_num_equal(string_buffer_get_initial_size(buffer), 5);
  assert_num_equal(string_buffer_get_content_size(buffer), 5);
  assert_num_equal(string_buffer_get_max_size(buffer), 5);
  assert_string_equal(string_buffer_to_string(buffer), "12345");
}


int main()
{
  test_run(test_impl);
}

