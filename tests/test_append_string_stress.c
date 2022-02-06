#include "stringbuffer.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new_with_options(1, true);

  for (size_t index = 0; index < 1000; index++)
  {
    assert_true(stringbuffer_append_string(buffer, "12345"));
  }

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 1000 * 5);

  char *content = stringbuffer_to_string(buffer);
  stringbuffer_release(buffer);

  assert_num_equal(strlen(content), 1000 * 5);
  free(content);
}


int main()
{
  test_run(test_impl);
}

