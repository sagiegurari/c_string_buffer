#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new();

  assert_true(string_buffer_append_string_with_options(buffer, "12345", 1, 2));

  assert_num_equal(string_buffer_get_initial_size(buffer), 10000);
  assert_num_equal(string_buffer_get_content_size(buffer), 2);
  assert_num_equal(string_buffer_get_max_size(buffer), string_buffer_get_initial_size(buffer));
  assert_string_equal(string_buffer_to_string(buffer), "23");
}


int main()
{
  test_run(test_impl);
}

