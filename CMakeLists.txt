
cmake_minimum_required (VERSION 3.7)

project (string_buffer C)

# include shared utilities
if(NOT EXISTS "target/cmake-modules/src/utils.cmake")
  execute_process(COMMAND git clone https://github.com/sagiegurari/cmake-modules.git)
endif()
include("target/cmake-modules/src/utils.cmake")

set(CMAKE_BUILD_TYPE Release)
if(NOT WIN32)
  set(X_CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -Wcast-align -Wunused -Wshadow -Wpedantic")
endif()

set(X_CMAKE_PROJECT_ROOT_DIR ${CMAKE_BINARY_DIR}/..)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

# define all sources
file(GLOB SOURCES "src/*.c")
file(GLOB HEADER_SOURCES "include/*.h")
file(GLOB TEST_SOURCES "tests/*")
file(GLOB COMMON_TEST_SOURCES "tests/test.*")

# format code
if(DEFINED ENV{X_CMAKE_UNCRUSTIFY_ENABLED})
  add_custom_target(uncrustify ALL
    uncrustify
    -c ${X_CMAKE_PROJECT_ROOT_DIR}/uncrustify.cfg
    --no-backup ${SOURCES} ${HEADER_SOURCES} ${TEST_SOURCES})
endif()

# create static library
add_library(string_buffer STATIC ${SOURCES})
if(NOT WIN32)
  set_target_properties(string_buffer PROPERTIES COMPILE_FLAGS "${X_CMAKE_C_FLAGS} -Wconversion")
endif()

# tests
enable_testing()

utils_setup_c_test(
  NAME
    new
    new_with_size_zero
    new_with_size_positive
    new_without_resize
    append_no_resize
    append_without_resize
    append_with_single_resize
    append_with_multiple_resize
    append_null_buffer
    append_string_no_resize
    append_string_with_single_resize
    append_string_without_resize
    append_string_with_options_length_too_big
    append_string_with_options_offset_too_big
    append_string_with_options_partial
    append_string_null_buffer
    append_string_null_string
    append_bool
    append_bool_null_buffer
    append_short
    append_unsigned_short
    append_short_null_buffer
    append_int
    append_unsigned_int
    append_int_null_buffer
    append_int_negative
    append_long
    append_unsigned_long
    append_long_null_buffer
    append_long_long
    append_unsigned_long_long
    append_long_long_null_buffer
    shrink_no_need
    shrink_bigger
    shrink_no_resize_no_need
    shrink_no_resize_bigger
    ensure_capacity_smaller
    ensure_capacity_same
    ensure_capacity_bigger
    ensure_capacity_no_resize_same
    ensure_capacity_no_resize_bigger
    complex_flow
    append_string_stress
  ADDITIONAL_SOURCES "${COMMON_TEST_SOURCES}"
  COMPILATION_FLAGS "${X_CMAKE_C_FLAGS}"
  BINARY_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

