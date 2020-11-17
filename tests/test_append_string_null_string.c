#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new();

  assert_true(string_buffer_append_string(buffer, NULL));
  assert_true(string_buffer_is_empty(buffer));

  string_buffer_release(buffer);
}


int main()
{
  test_run(test_impl);
}

