## CHANGELOG

### v0.2.1 (2023-02-03)

* New floating type append functions
* Updated header include guard macro name

### v0.2.0 (2022-02-06)

* \[**backward compatibility break**\] Renamed string_buffer to stringbuffer to be prevent conflict with external APIs
* Added static to internal functions
* Adding lint checks as part of build

### v0.1.6 (2021-09-24)

* New string_buffer_append_binary function
* Added void to no arg functions
* Removed internal release flag
* Added cargo-make makefile for simpler sharing of optional development build instructions

### v0.1.5 (2020-12-27)

* Change default initial buffer size to 64
* Support different default initial buffer size via STRING_BUFFER_INITIAL_BUFFER_SIZE define
* Free all memory in tests
* Test memory leaks in CI

### v0.1.4 (2020-11-07)

* Internal functions are now namespaced with \_string_buffer prefix
* Improved build setup (no need to list test names)

### v0.1.3 (2020-09-25)

* Fixed memory allocation.
* Update cmake build to use shared cmake utilities.

### v0.1.2 (2020-05-31)

* Memory copy changes to improve stability and performance.

### v0.1.1 (2020-04-23)

* New string_buffer_is_released function.
* New append_unsigned_xxxx functions.
* Reusing internal buffer for type conversion instead of reallocating a new buffer on every call.

### v0.1.0 (2020-04-22)

* Initial release
