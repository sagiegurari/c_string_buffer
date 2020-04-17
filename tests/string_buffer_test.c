#include "string_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// helper functions
void run_test(void (*fn)(), const char *name);
void fail();
void assert_true(bool);
void assert_num_equal(long, long);
void assert_string_equal(char *, char *);


void test_new()
{
  struct StringBuffer *buffer = string_buffer_new();

  assert_num_equal(buffer->initial_size, 10000);
  assert_num_equal(buffer->content_size, 0);
  assert_num_equal(buffer->max_size, buffer->initial_size);
  assert_string_equal(string_buffer_to_string(buffer), "");
}


void test_new_with_size_zero()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(0);

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 0);
  assert_num_equal(buffer->max_size, buffer->initial_size);
  assert_string_equal(string_buffer_to_string(buffer), "");
}


void test_new_with_size_negative()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(-1);

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 0);
  assert_num_equal(buffer->max_size, buffer->initial_size);
  assert_string_equal(string_buffer_to_string(buffer), "");
}


void test_new_with_size_positive()
{
  const int           size    = 600;
  struct StringBuffer *buffer = string_buffer_new_with_size(size);

  assert_num_equal(buffer->initial_size, size);
  assert_num_equal(buffer->content_size, 0);
  assert_num_equal(buffer->max_size, buffer->initial_size);
  assert_string_equal(string_buffer_to_string(buffer), "");
}


void test_append_no_resize()
{
  struct StringBuffer *buffer = string_buffer_new();

  assert_true(string_buffer_append(buffer, '1'));
  assert_true(string_buffer_append(buffer, '2'));
  assert_true(string_buffer_append(buffer, '3'));

  assert_num_equal(buffer->initial_size, 10000);
  assert_num_equal(buffer->content_size, 3);
  assert_num_equal(buffer->max_size, buffer->initial_size);
  assert_string_equal(string_buffer_to_string(buffer), "123");
}


void test_append_with_single_resize()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(2);

  assert_true(string_buffer_append(buffer, '1'));
  assert_true(string_buffer_append(buffer, '2'));
  assert_true(string_buffer_append(buffer, '3'));

  assert_num_equal(buffer->initial_size, 2);
  assert_num_equal(buffer->content_size, 3);
  assert_num_equal(buffer->max_size, 4);
  assert_string_equal(string_buffer_to_string(buffer), "123");
}


void test_append_with_multiple_resize()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(1);

  for (short index = 0; index < 20; index++)
  {
    short next = index % 10;
    assert_true(string_buffer_append(buffer, next + '0'));
  }

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 20);
  assert_num_equal(buffer->max_size, 32);
  assert_string_equal(string_buffer_to_string(buffer), "01234567890123456789");
}


void test_append_string_no_resize()
{
  struct StringBuffer *buffer = string_buffer_new();

  assert_true(string_buffer_append_string(buffer, "12345"));
  assert_true(string_buffer_append_string(buffer, "abcde"));
  assert_true(string_buffer_append_string(buffer, "ABCDE"));

  assert_num_equal(buffer->initial_size, 10000);
  assert_num_equal(buffer->content_size, 15);
  assert_num_equal(buffer->max_size, buffer->initial_size);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDE");
}


void test_append_string_with_single_resize()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(10);

  assert_true(string_buffer_append_string(buffer, "12345"));
  assert_true(string_buffer_append_string(buffer, "abcde"));
  assert_true(string_buffer_append_string(buffer, "ABCDE"));

  assert_num_equal(buffer->initial_size, 10);
  assert_num_equal(buffer->content_size, 15);
  assert_num_equal(buffer->max_size, 20);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDE");
}


void test_append_bool()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(100);

  assert_true(string_buffer_append_bool(buffer, true));
  assert_true(string_buffer_append_bool(buffer, false));

  assert_num_equal(buffer->initial_size, 100);
  assert_num_equal(buffer->content_size, 9);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "truefalse");
}


void test_append_short()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(100);

  short               value = 150;

  assert_true(string_buffer_append_short(buffer, value));

  assert_num_equal(buffer->initial_size, 100);
  assert_num_equal(buffer->content_size, 3);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "150");
}


void test_append_int()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(100);

  int                 value = 150;

  assert_true(string_buffer_append_int(buffer, value));

  assert_num_equal(buffer->initial_size, 100);
  assert_num_equal(buffer->content_size, 3);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "150");
}


void test_append_int_negative()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(100);

  int                 value = -123456;

  assert_true(string_buffer_append_int(buffer, value));

  assert_num_equal(buffer->initial_size, 100);
  assert_num_equal(buffer->content_size, 7);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "-123456");
}


void test_append_long()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(100);

  long                value = 150;

  assert_true(string_buffer_append_long(buffer, value));

  assert_num_equal(buffer->initial_size, 100);
  assert_num_equal(buffer->content_size, 3);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "150");
}


void test_append_long_long()
{
  struct StringBuffer *buffer = string_buffer_new_with_size(100);

  long long           value = 150;

  assert_true(string_buffer_append_long_long(buffer, value));

  assert_num_equal(buffer->initial_size, 100);
  assert_num_equal(buffer->content_size, 3);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "150");
}


void fail()
{
  printf(" Error\n");
  exit(1);
}


void assert_true(bool value)
{
  if (!value)
  {
    fail();
  }
}


void assert_num_equal(long value1, long value2)
{
  if (value1 != value2)
  {
    printf("Assert Failed, value: %li not equals to value: %li", value1, value2);
    fail();
  }
}


void assert_string_equal(char *value1, char *value2)
{
  if (strcmp(value1, value2) != 0)
  {
    printf("Assert Failed, value: %s not equals to value: %s", value1, value2);
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
  else if (strcmp("append_no_resize", test_name) == 0)
  {
    run_test(test_append_no_resize, test_name);
  }
  else if (strcmp("append_with_single_resize", test_name) == 0)
  {
    run_test(test_append_with_single_resize, test_name);
  }
  else if (strcmp("append_with_multiple_resize", test_name) == 0)
  {
    run_test(test_append_with_multiple_resize, test_name);
  }
  else if (strcmp("append_string_no_resize", test_name) == 0)
  {
    run_test(test_append_string_no_resize, test_name);
  }
  else if (strcmp("append_string_with_single_resize", test_name) == 0)
  {
    run_test(test_append_string_with_single_resize, test_name);
  }
  else if (strcmp("append_bool", test_name) == 0)
  {
    run_test(test_append_bool, test_name);
  }
  else if (strcmp("append_short", test_name) == 0)
  {
    run_test(test_append_short, test_name);
  }
  else if (strcmp("append_int", test_name) == 0)
  {
    run_test(test_append_int, test_name);
  }
  else if (strcmp("append_int_negative", test_name) == 0)
  {
    run_test(test_append_int_negative, test_name);
  }
  else if (strcmp("append_long", test_name) == 0)
  {
    run_test(test_append_long, test_name);
  }
  else if (strcmp("append_long_long", test_name) == 0)
  {
    run_test(test_append_long_long, test_name);
  }
  else
  {
    printf("Unknown Test: %s", test_name);
    fail();
  }

  return(0);
} /* main */

