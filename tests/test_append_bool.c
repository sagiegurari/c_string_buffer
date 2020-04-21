#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(100, true);

  assert_true(string_buffer_append_bool(buffer, true));
  assert_true(string_buffer_append_bool(buffer, false));

  assert_num_equal(string_buffer_get_initial_size(buffer), 100);
  assert_num_equal(string_buffer_get_content_size(buffer), 9);
  assert_num_equal(string_buffer_get_max_size(buffer), 100);
  assert_string_equal(string_buffer_to_string(buffer), "truefalse");
}


int main()
{
  test_run(test_impl);
}

