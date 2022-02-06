#include "stringbuffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new_with_options(1, true);

  for (short index = 0; index < 20; index++)
  {
    const char char_value = (index % 10) + '0';
    assert_true(stringbuffer_append(buffer, char_value));
  }

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 20);
  assert_num_equal(stringbuffer_get_max_size(buffer), 32);

  char *content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "01234567890123456789");

  stringbuffer_release(buffer);
  free(content);
}


int main()
{
  test_run(test_impl);
}

