#include "stringbuffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new_with_options(100, true);

  assert_true(stringbuffer_append_bool(buffer, true));
  assert_true(stringbuffer_append_bool(buffer, false));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 100);
  assert_num_equal(stringbuffer_get_content_size(buffer), 9);
  assert_num_equal(stringbuffer_get_max_size(buffer), 100);

  char *content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "truefalse");

  stringbuffer_release(buffer);
  free(content);
}


int main()
{
  test_run(test_impl);
}

