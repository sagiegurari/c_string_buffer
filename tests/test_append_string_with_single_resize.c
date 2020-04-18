#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(10);

  assert_true(string_buffer_append_string(buffer, "12345"));
  assert_true(string_buffer_append_string(buffer, "abcde"));
  assert_true(string_buffer_append_string(buffer, "ABCDE"));

  assert_num_equal(buffer->initial_size, 10);
  assert_num_equal(buffer->content_size, 15);
  assert_num_equal(buffer->max_size, 20);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDE");
}


int main()
{
  test_run(test_impl);
}

