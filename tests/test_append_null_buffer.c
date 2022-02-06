#include "stringbuffer.h"
#include "test.h"


void test_impl()
{
  assert_true(!stringbuffer_append(NULL, 'A'));
}


int main()
{
  test_run(test_impl);
}

