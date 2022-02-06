#include "stringbuffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new_with_options(10000, false);

  assert_true(stringbuffer_append(buffer, '1'));
  assert_true(stringbuffer_append(buffer, '2'));
  assert_true(stringbuffer_append(buffer, '3'));

  assert_true(!stringbuffer_is_allow_resize(buffer));
  assert_num_equal(stringbuffer_get_initial_size(buffer), 10000);
  assert_num_equal(stringbuffer_get_content_size(buffer), 3);
  assert_num_equal(stringbuffer_get_max_size(buffer), stringbuffer_get_initial_size(buffer));

  char *content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "123");

  stringbuffer_release(buffer);
  free(content);
}


int main()
{
  test_run(test_impl);
}

