#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(10, false);

  assert_true(string_buffer_append_string(buffer, "12345"));
  assert_true(string_buffer_append_string(buffer, "abcde"));
  assert_true(!string_buffer_append_string(buffer, "ABCDE"));

  assert_num_equal(string_buffer_get_initial_size(buffer), 10);
  assert_num_equal(string_buffer_get_content_size(buffer), 10);
  assert_num_equal(string_buffer_get_max_size(buffer), 10);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcde");
}


int main()
{
  test_run(test_impl);
}

