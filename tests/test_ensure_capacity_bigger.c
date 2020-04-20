#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(1, true);

  assert_true(string_buffer_append_string(buffer, "12345"));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 5);
  assert_num_equal(buffer->max_size, 8);
  assert_string_equal(string_buffer_to_string(buffer), "12345");

  assert_true(string_buffer_ensure_capacity(buffer, 100));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 5);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "12345");
}


int main()
{
  test_run(test_impl);
}

