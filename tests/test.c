#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#ifdef _WIN64
#define SIZET_FORMAT    PRIu64
#else
#define SIZET_FORMAT    PRIu32
#endif
#else
#define SIZET_FORMAT    "zu"
#endif


void test_run(void (*fn)(void))
{
  printf("Test ... ");
  fn();
  printf("Done\n");
}


void test_fail()
{
  printf(" Error\n");
  exit(1);
}


void assert_true(bool value)
{
  if (!value)
  {
    test_fail();
  }
}


void assert_num_equal(size_t value1, size_t value2)
{
  if (value1 != value2)
  {
    printf("Assert Failed, value: %" SIZET_FORMAT " not equals to value: %" SIZET_FORMAT, value1, value2);
    test_fail();
  }
}


void assert_string_equal(char *value1, char *value2)
{
  if (strcmp(value1, value2) != 0)
  {
    printf("Assert Failed, value: %s not equals to value: %s", value1, value2);
    test_fail();
  }
}
