#include "string_buffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new();

  assert_true(string_buffer_append_string(buffer, "12345"));
  assert_true(string_buffer_append_string(buffer, "abcde"));
  assert_true(string_buffer_append_string(buffer, "ABCDE"));

  assert_num_equal(string_buffer_get_initial_size(buffer), STRING_BUFFER_INITIAL_BUFFER_SIZE);
  assert_num_equal(string_buffer_get_content_size(buffer), 15);
  assert_num_equal(string_buffer_get_max_size(buffer), string_buffer_get_initial_size(buffer));

  char *content = string_buffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDE");

  string_buffer_release(buffer);
  free(content);
}


int main()
{
  test_run(test_impl);
}

