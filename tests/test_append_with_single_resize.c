#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(2);

  assert_true(string_buffer_append(buffer, '1'));
  assert_true(string_buffer_append(buffer, '2'));
  assert_true(string_buffer_append(buffer, '3'));

  assert_num_equal(buffer->initial_size, 2);
  assert_num_equal(buffer->content_size, 3);
  assert_num_equal(buffer->max_size, 4);
  assert_string_equal(string_buffer_to_string(buffer), "123");
}


int main()
{
  test_run(test_impl);
}

