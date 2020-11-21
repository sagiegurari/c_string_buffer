## CHANGELOG

### v0.1.5

* Free all memory in tests
* Add memory test via cmake support

### v0.1.4 (2020-11-07)

* Internal functions are now namespaced with _string_buffer prefix.
* Improved build setup (no need to list test names).

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
