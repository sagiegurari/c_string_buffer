#include "stringbuffer.h"
#include "test.h"


void test_impl()
{
  assert_true(!stringbuffer_append_bool(NULL, true));
}


int main()
{
  test_run(test_impl);
}

