#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  assert_true(!string_buffer_append(NULL, 'A'));
}


int main()
{
  test_run(test_impl);
}

