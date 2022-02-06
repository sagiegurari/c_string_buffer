#include "stringbuffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new();

  assert_true(!stringbuffer_append_string_with_options(buffer, "12345", 0, 100));

  assert_num_equal(stringbuffer_get_initial_size(buffer), STRINGBUFFER_INITIAL_BUFFER_SIZE);
  assert_num_equal(stringbuffer_get_content_size(buffer), 0);
  assert_num_equal(stringbuffer_get_max_size(buffer), stringbuffer_get_initial_size(buffer));

  char *content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "");

  stringbuffer_release(buffer);
  free(content);
}


int main()
{
  test_run(test_impl);
}

