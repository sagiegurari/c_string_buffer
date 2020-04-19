# string_buffer

[![Continuous Integration](https://github.com/sagiegurari/c_string_buffer/workflows/Continuous%20Integration/badge.svg?branch=master)](https://github.com/sagiegurari/c_string_buffer/actions)
[![license](https://img.shields.io/github/license/sagiegurari/c_string_buffer.svg)](https://github.com/sagiegurari/c_string_buffer/blob/master/LICENSE)

> A simple string buffer for C.

* [Overview](#overview)
* [Usage](#usage)
* [API Documentation](https://sagiegurari.github.io/string_buffer/)
* [Contributing](.github/CONTRIBUTING.md)
* [Release History](CHANGELOG.md)
* [License](#license)

<a name="overview"></a>
## Overview
This library provides a simple string buffer which allows adding different basic data types.<br>
It can be used to generate large strings without the need to worry about memory allocation or type conversions.

<a name="usage"></a>
## Usage

```c
#include "string_buffer.h"

int main()
{
  // init the buffer with predefined size or with a provided size
  // use string_buffer_new for predefined size
  struct StringBuffer *buffer = string_buffer_new_with_size(1500);

  // different append functions
  string_buffer_append(buffer, 'A');
  string_buffer_append_string(buffer, "12345");
  string_buffer_append_bool(buffer, true);
  string_buffer_append_int(buffer, 123);
  string_buffer_append_long_long(buffer, 150);

  // increase buffer size if needed to ensure capacity
  // and prevent multiple reallocations in case of many
  // append operations
  string_buffer_ensure_capacity(buffer, 10000);

  // shrink the internal buffer to fit the exact value
  // of the current content and prevent using more memory
  // than needed.
  string_buffer_shrink(buffer);

  // get a clone text value of the current buffer content
  char* text = string_buffer_to_string(buffer);

  // we can clear the content we have so far and reuse the
  // string buffer instance
  string_buffer_clear(buffer);

  // once done, free the buffer
  string_buffer_release(buffer);
}
```

## API Documentation
See full docs at: [API Docs](https://sagiegurari.github.io/string_buffer/)

## Contributing
See [contributing guide](.github/CONTRIBUTING.md)

<a name="history"></a>
## Release History

See [Changelog](CHANGELOG.md)

<a name="license"></a>
## License
Developed by Sagie Gur-Ari and licensed under the Apache 2 open source license.