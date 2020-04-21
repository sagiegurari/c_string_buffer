#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(1, true);

  for (short index = 0; index < 20; index++)
  {
    const char char_value = (index % 10) + '0';
    assert_true(string_buffer_append(buffer, char_value));
  }

  assert_num_equal(string_buffer_get_initial_size(buffer), 1);
  assert_num_equal(string_buffer_get_content_size(buffer), 20);
  assert_num_equal(string_buffer_get_max_size(buffer), 32);
  assert_string_equal(string_buffer_to_string(buffer), "01234567890123456789");
}


int main()
{
  test_run(test_impl);
}

