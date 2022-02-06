#ifndef __STRINGBUFFER_H__
#define __STRINGBUFFER_H__

#include <stdbool.h>
#include <stddef.h>

#ifndef STRINGBUFFER_INITIAL_BUFFER_SIZE
#define STRINGBUFFER_INITIAL_BUFFER_SIZE    64
#endif

struct StringBuffer;

struct StringBuffer *stringbuffer_new(void);
struct StringBuffer *stringbuffer_new_with_options(const size_t /* initial_size */, const bool /* allow_resize */);

bool stringbuffer_is_empty(struct StringBuffer *);
size_t stringbuffer_get_initial_size(struct StringBuffer *);
size_t stringbuffer_get_content_size(struct StringBuffer *);
size_t stringbuffer_get_max_size(struct StringBuffer *);
bool  stringbuffer_is_allow_resize(struct StringBuffer *);

bool stringbuffer_clear(struct StringBuffer *);
void stringbuffer_release(struct StringBuffer *);

bool stringbuffer_ensure_capacity(struct StringBuffer *, const size_t /* size */);
bool stringbuffer_shrink(struct StringBuffer *);

char *stringbuffer_to_string(struct StringBuffer *);

bool stringbuffer_append(struct StringBuffer *, char);
bool stringbuffer_append_string(struct StringBuffer *, char *);
bool stringbuffer_append_string_with_options(struct StringBuffer *, char *, const size_t /* offset */, const size_t /* length */);
bool stringbuffer_append_binary(struct StringBuffer *, char *, const size_t /* offset */, const size_t /* length */);
bool stringbuffer_append_bool(struct StringBuffer *, bool);
bool stringbuffer_append_short(struct StringBuffer *, short);
bool stringbuffer_append_int(struct StringBuffer *, int);
bool stringbuffer_append_long(struct StringBuffer *, long);
bool stringbuffer_append_long_long(struct StringBuffer *, long long);
bool stringbuffer_append_unsigned_short(struct StringBuffer *, unsigned short);
bool stringbuffer_append_unsigned_int(struct StringBuffer *, unsigned int);
bool stringbuffer_append_unsigned_long(struct StringBuffer *, unsigned long);
bool stringbuffer_append_unsigned_long_long(struct StringBuffer *, unsigned long long);

#endif

