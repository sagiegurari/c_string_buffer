#include "string_buffer.h"
#include "test.h"


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new_with_options(1, true);

  assert_true(string_buffer_append_string(buffer, "12345"));
  assert_true(string_buffer_append_string(buffer, "abcde"));
  assert_true(string_buffer_append_string(buffer, "ABCDE"));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 15);
  assert_num_equal(buffer->max_size, 16);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDE");

  assert_true(string_buffer_append_bool(buffer, true));
  assert_true(string_buffer_append_bool(buffer, false));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 24);
  assert_num_equal(buffer->max_size, 32);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDEtruefalse");

  assert_true(string_buffer_append_int(buffer, -123));
  assert_true(string_buffer_append_long_long(buffer, 150));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 31);
  assert_num_equal(buffer->max_size, 32);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDEtruefalse-123150");

  string_buffer_clear(buffer);
  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 0);
  assert_num_equal(buffer->max_size, 1);
  assert_string_equal(string_buffer_to_string(buffer), "");

  assert_true(string_buffer_append_string(buffer, "12345"));
  assert_true(string_buffer_append_string(buffer, "abcde"));
  assert_true(string_buffer_append_string(buffer, "ABCDE"));
  assert_true(string_buffer_append_bool(buffer, true));
  assert_true(string_buffer_append_bool(buffer, false));
  assert_true(string_buffer_append_int(buffer, -123));
  assert_true(string_buffer_append_long_long(buffer, 150));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 31);
  assert_num_equal(buffer->max_size, 32);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDEtruefalse-123150");

  assert_true(string_buffer_shrink(buffer));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 31);
  assert_num_equal(buffer->max_size, 31);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDEtruefalse-123150");

  assert_true(string_buffer_append(buffer, '9'));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 32);
  assert_num_equal(buffer->max_size, 62);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDEtruefalse-1231509");

  assert_true(string_buffer_ensure_capacity(buffer, 10));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 32);
  assert_num_equal(buffer->max_size, 62);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDEtruefalse-1231509");

  assert_true(string_buffer_ensure_capacity(buffer, 100));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 32);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDEtruefalse-1231509");

  assert_true(string_buffer_append_string(buffer, "12345"));
  assert_true(string_buffer_append_string(buffer, "abcde"));
  assert_true(string_buffer_append_string(buffer, "ABCDE"));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 47);
  assert_num_equal(buffer->max_size, 100);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDEtruefalse-123150912345abcdeABCDE");

  assert_true(string_buffer_shrink(buffer));

  assert_num_equal(buffer->initial_size, 1);
  assert_num_equal(buffer->content_size, 47);
  assert_num_equal(buffer->max_size, 47);
  assert_string_equal(string_buffer_to_string(buffer), "12345abcdeABCDEtruefalse-123150912345abcdeABCDE");
} /* test_impl */


int main()
{
  test_run(test_impl);
}

