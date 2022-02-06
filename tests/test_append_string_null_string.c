#include "stringbuffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new();

  assert_true(stringbuffer_append_string(buffer, NULL));
  assert_true(stringbuffer_is_empty(buffer));

  stringbuffer_release(buffer);
}


int main()
{
  test_run(test_impl);
}

