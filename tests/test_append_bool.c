#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(100, true);

  assert_true(string_buffer_append_bool(buffer, true));
  assert_true(string_buffer_append_bool(buffer, false));

  assert_num_equal(buffer->initial_size, 100);
  assert_num_equal(buffer->content_size, 9);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "truefalse");
}


int main()
{
  test_run(test_impl);
}

