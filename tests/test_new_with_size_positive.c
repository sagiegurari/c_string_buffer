#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(1024, true);

  assert_true(string_buffer_is_empty(buffer));
  assert_true(string_buffer_is_allow_resize(buffer));
  assert_num_equal(string_buffer_get_initial_size(buffer), 1024);
  assert_num_equal(string_buffer_get_content_size(buffer), 0);
  assert_num_equal(string_buffer_get_max_size(buffer), string_buffer_get_initial_size(buffer));
  assert_string_equal(string_buffer_to_string(buffer), "");
}


int main()
{
  test_run(test_impl);
}

