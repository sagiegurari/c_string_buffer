#include "stringbuffer.h"
#include "test.h"


void test_impl()
{
  assert_true(!stringbuffer_append_long_long(NULL, 1));
}


int main()
{
  test_run(test_impl);
}

