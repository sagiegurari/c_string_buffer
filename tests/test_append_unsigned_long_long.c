#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(100, true);

  assert_true(string_buffer_append_unsigned_long_long(buffer, 150));

  assert_num_equal(string_buffer_get_initial_size(buffer), 100);
  assert_num_equal(string_buffer_get_content_size(buffer), 3);
  assert_num_equal(string_buffer_get_max_size(buffer), 100);
  assert_string_equal(string_buffer_to_string(buffer), "150");
}


int main()
{
  test_run(test_impl);
}
