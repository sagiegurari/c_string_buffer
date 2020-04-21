#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(1, true);

  for (size_t index = 0; index < 1000; index++)
  {
    assert_true(string_buffer_append_string(buffer, "12345"));
  }

  assert_num_equal(string_buffer_get_initial_size(buffer), 1);
  assert_num_equal(string_buffer_get_content_size(buffer), 1000 * 5);
}


int main()
{
  test_run(test_impl);
}

