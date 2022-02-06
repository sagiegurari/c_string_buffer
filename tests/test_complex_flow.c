#include "stringbuffer.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new_with_options(1, true);

  assert_true(stringbuffer_is_empty(buffer));

  assert_true(stringbuffer_append_string(buffer, "12345"));
  assert_true(stringbuffer_append_string(buffer, "abcde"));
  assert_true(stringbuffer_append_string(buffer, "ABCDE"));

  assert_true(!stringbuffer_is_empty(buffer));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 15);
  assert_num_equal(stringbuffer_get_max_size(buffer), 16);

  char *content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDE");
  free(content);

  assert_true(stringbuffer_append_bool(buffer, true));
  assert_true(stringbuffer_append_bool(buffer, false));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 24);
  assert_num_equal(stringbuffer_get_max_size(buffer), 32);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDEtruefalse");
  free(content);

  assert_true(stringbuffer_append_int(buffer, -123));
  assert_true(stringbuffer_append_long_long(buffer, 150));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 31);
  assert_num_equal(stringbuffer_get_max_size(buffer), 32);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDEtruefalse-123150");
  free(content);

  stringbuffer_clear(buffer);
  assert_true(stringbuffer_is_empty(buffer));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 0);
  assert_num_equal(stringbuffer_get_max_size(buffer), 1);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "");
  free(content);

  assert_true(stringbuffer_append_string(buffer, "12345"));
  assert_true(stringbuffer_append_string(buffer, "abcde"));
  assert_true(stringbuffer_append_string(buffer, "ABCDE"));
  assert_true(stringbuffer_append_bool(buffer, true));
  assert_true(stringbuffer_append_bool(buffer, false));
  assert_true(stringbuffer_append_int(buffer, -123));
  assert_true(stringbuffer_append_long_long(buffer, 150));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 31);
  assert_num_equal(stringbuffer_get_max_size(buffer), 32);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDEtruefalse-123150");
  free(content);

  assert_true(stringbuffer_shrink(buffer));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 31);
  assert_num_equal(stringbuffer_get_max_size(buffer), 31);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDEtruefalse-123150");
  free(content);

  assert_true(stringbuffer_append(buffer, '9'));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 32);
  assert_num_equal(stringbuffer_get_max_size(buffer), 62);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDEtruefalse-1231509");
  free(content);

  assert_true(stringbuffer_ensure_capacity(buffer, 10));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 32);
  assert_num_equal(stringbuffer_get_max_size(buffer), 62);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDEtruefalse-1231509");
  free(content);

  assert_true(stringbuffer_ensure_capacity(buffer, 100));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 32);
  assert_num_equal(stringbuffer_get_max_size(buffer), 100);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDEtruefalse-1231509");
  free(content);

  assert_true(stringbuffer_append_string(buffer, "12345"));
  assert_true(stringbuffer_append_string(buffer, "abcde"));
  assert_true(stringbuffer_append_string(buffer, "ABCDE"));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 47);
  assert_num_equal(stringbuffer_get_max_size(buffer), 100);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDEtruefalse-123150912345abcdeABCDE");
  free(content);

  assert_true(stringbuffer_shrink(buffer));

  assert_num_equal(stringbuffer_get_initial_size(buffer), 1);
  assert_num_equal(stringbuffer_get_content_size(buffer), 47);
  assert_num_equal(stringbuffer_get_max_size(buffer), 47);

  content = stringbuffer_to_string(buffer);
  assert_string_equal(content, "12345abcdeABCDEtruefalse-123150912345abcdeABCDE");

  stringbuffer_release(buffer);
  free(content);
} /* test_impl */


int main()
{
  test_run(test_impl);
}

