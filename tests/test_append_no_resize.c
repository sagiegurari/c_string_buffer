#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new();

  assert_true(string_buffer_append(buffer, '1'));
  assert_true(string_buffer_append(buffer, '2'));
  assert_true(string_buffer_append(buffer, '3'));

  assert_true(string_buffer_is_allow_resize(buffer));
  assert_num_equal(string_buffer_get_initial_size(buffer), 10240);
  assert_num_equal(string_buffer_get_content_size(buffer), 3);
  assert_num_equal(string_buffer_get_max_size(buffer), string_buffer_get_initial_size(buffer));
  assert_string_equal(string_buffer_to_string(buffer), "123");
}


int main()
{
  test_run(test_impl);
}

