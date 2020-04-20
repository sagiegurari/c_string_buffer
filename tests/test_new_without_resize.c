#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  const size_t        size    = 600;
  struct StringBuffer *buffer = string_buffer_new_with_options(size, false);

  assert_true(!buffer->allow_resize);
  assert_num_equal(buffer->initial_size, size);
  assert_num_equal(buffer->content_size, 0);
  assert_num_equal(buffer->max_size, buffer->initial_size);
  assert_string_equal(string_buffer_to_string(buffer), "");
}


int main()
{
  test_run(test_impl);
}

