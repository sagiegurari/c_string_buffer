#include "string_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// helper functions
void run_test(void (*fn)(), const char *name);
void fail();
void assert_equal(unsigned long, unsigned long);


void test_new()
{
  struct StringBuffer *buffer = string_buffer_new();

  assert_equal(buffer->initial_size, 10000);
  assert_equal(buffer->content_size, 0);
  assert_equal(buffer->max_size, buffer->initial_size);
}


void test_new_with_size_zero()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(0);

  assert_equal(buffer->initial_size, 1);
  assert_equal(buffer->content_size, 0);
  assert_equal(buffer->max_size, buffer->initial_size);
}


void test_new_with_size_negative()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(-1);

  assert_equal(buffer->initial_size, 1);
  assert_equal(buffer->content_size, 0);
  assert_equal(buffer->max_size, buffer->initial_size);
}


void test_new_with_size_positive()
{
  const int           size    = 600;
  struct StringBuffer *buffer = string_buffer_new_with_size(size);

  assert_equal(buffer->initial_size, size);
  assert_equal(buffer->content_size, 0);
  assert_equal(buffer->max_size, buffer->initial_size);
}


void fail()
{
  printf("Test Failed.\n");
  exit(1);
}


void assert_equal(unsigned long value1, unsigned long value2)
{
  if (value1 != value2)
  {
    printf("\nAssert Failed, value: %lu it not equal to %lu\n", value1, value2);
    fail();
  }
}


void run_test(void (*fn)(void), const char *name)
{
  printf("Test: %s ... ", name);
  fn();
  printf("Done\n");
}


int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Missing Test Name.");
    fail();
  }

  const char *test_name = argv[1];

  if (strcmp("new", test_name) == 0)
  {
    run_test(test_new, test_name);
  }
  else if (strcmp("new_with_size_zero", test_name) == 0)
  {
    run_test(test_new_with_size_zero, test_name);
  }
  else if (strcmp("new_with_size_negative", test_name) == 0)
  {
    run_test(test_new_with_size_negative, test_name);
  }
  else if (strcmp("new_with_size_positive", test_name) == 0)
  {
    run_test(test_new_with_size_positive, test_name);
  }
  else
  {
    printf("Unknown Test: %s", test_name);
    fail();
  }

  return(0);
}

