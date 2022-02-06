#include "stringbuffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new_with_options(5, false);

  assert_true(stringbuffer_append_string(buffer, "12345"));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 5);
  assert_num_equal(stringbuffer_get_content_size(buffer), 5);
  assert_num_equal(stringbuffer_get_max_size(buffer), 5);

  char *content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345");

  free(content);

  assert_true(stringbuffer_shrink(buffer));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 5);
  assert_num_equal(stringbuffer_get_content_size(buffer), 5);
  assert_num_equal(stringbuffer_get_max_size(buffer), 5);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345");

  stringbuffer_release(buffer);
  free(content);
}


int main()
{
  test_run(test_impl);
}

