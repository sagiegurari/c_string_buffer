#ifndef __STRING_BUFFER_H__
#define __STRING_BUFFER_H__

#include <stdbool.h>
#include <stddef.h>

#ifndef STRING_BUFFER_INITIAL_BUFFER_SIZE
#define STRING_BUFFER_INITIAL_BUFFER_SIZE    64
#endif

struct StringBuffer;

struct StringBuffer *string_buffer_new(void);
struct StringBuffer *string_buffer_new_with_options(const size_t /* initial_size */, const bool /* allow_resize */);

bool string_buffer_is_empty(struct StringBuffer *);
size_t string_buffer_get_initial_size(struct StringBuffer *);
size_t string_buffer_get_content_size(struct StringBuffer *);
size_t string_buffer_get_max_size(struct StringBuffer *);
bool  string_buffer_is_allow_resize(struct StringBuffer *);

bool string_buffer_clear(struct StringBuffer *);
void string_buffer_release(struct StringBuffer *);

bool string_buffer_ensure_capacity(struct StringBuffer *, const size_t /* size */);
bool string_buffer_shrink(struct StringBuffer *);

char *string_buffer_to_string(struct StringBuffer *);

bool string_buffer_append(struct StringBuffer *, char);
bool string_buffer_append_string(struct StringBuffer *, char *);
bool string_buffer_append_string_with_options(struct StringBuffer *, char *, const size_t /* offset */, const size_t /* length */);
bool string_buffer_append_bool(struct StringBuffer *, bool);
bool string_buffer_append_short(struct StringBuffer *, short);
bool string_buffer_append_int(struct StringBuffer *, int);
bool string_buffer_append_long(struct StringBuffer *, long);
bool string_buffer_append_long_long(struct StringBuffer *, long long);
bool string_buffer_append_unsigned_short(struct StringBuffer *, unsigned short);
bool string_buffer_append_unsigned_int(struct StringBuffer *, unsigned int);
bool string_buffer_append_unsigned_long(struct StringBuffer *, unsigned long);
bool string_buffer_append_unsigned_long_long(struct StringBuffer *, unsigned long long);

#endif

