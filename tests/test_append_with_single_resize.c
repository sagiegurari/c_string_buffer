#include "string_buffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(2, true);

  assert_true(string_buffer_append(buffer, '1'));
  assert_true(string_buffer_append(buffer, '2'));
  assert_true(string_buffer_append(buffer, '3'));

  assert_num_equal(string_buffer_get_initial_size(buffer), 2);
  assert_num_equal(string_buffer_get_content_size(buffer), 3);
  assert_num_equal(string_buffer_get_max_size(buffer), 4);

  char *content = string_buffer_to_string(buffer);
  assert_string_equal(content, "123");

  string_buffer_release(buffer);
  free(content);
}


int main()
{
  test_run(test_impl);
}

