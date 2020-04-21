
cmake_minimum_required (VERSION 3.7)

project (string_buffer C)

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
file(GLOB HEADER_SORUCES "include/*.h")
file(GLOB TEST_SOURCES "tests/*")
file(GLOB COMMON_TEST_SOURCES "tests/test.*")

# format code
if(DEFINED ENV{X_CMAKE_UNCRUSTIFY_ENABLED})
  add_custom_target(uncrustify ALL
    uncrustify
    -c ${X_CMAKE_PROJECT_ROOT_DIR}/uncrustify.cfg
    --no-backup ${SOURCES} ${HEADER_SORUCES} ${TEST_SOURCES})
endif()

# create static library
add_library(string_buffer STATIC ${SOURCES})
if(NOT WIN32)
  set_target_properties(string_buffer PROPERTIES COMPILE_FLAGS "${X_CMAKE_C_FLAGS} -Wconversion")
endif()

# tests
enable_testing()

macro(setup_test)
  message("Adding Test: ${ARGV0}")
  add_executable(test_${ARGV0} tests/test_${ARGV0}.c ${COMMON_TEST_SOURCES})
  target_link_libraries(test_${ARGV0} string_buffer)
  set_target_properties(test_${ARGV0} PROPERTIES COMPILE_FLAGS "${X_CMAKE_C_FLAGS}")
  add_test(NAME ${ARGV0}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMAND test_${ARGV0})
endmacro(setup_test)

setup_test("new")
setup_test("new_with_size_zero")
setup_test("new_with_size_positive")
setup_test("new_without_resize")
setup_test("append_no_resize")
setup_test("append_without_resize")
setup_test("append_with_single_resize")
setup_test("append_with_multiple_resize")
setup_test("append_null_buffer")
setup_test("append_string_no_resize")
setup_test("append_string_with_single_resize")
setup_test("append_string_without_resize")
setup_test("append_string_with_options_length_too_big")
setup_test("append_string_with_options_offset_too_big")
setup_test("append_string_with_options_partial")
setup_test("append_string_null_buffer")
setup_test("append_string_null_string")
setup_test("append_bool")
setup_test("append_short")
setup_test("append_int")
setup_test("append_int_null_buffer")
setup_test("append_int_negative")
setup_test("append_long")
setup_test("append_long_long")
setup_test("shrink_no_need")
setup_test("shrink_bigger")
setup_test("shrink_no_resize_no_need")
setup_test("shrink_no_resize_bigger")
setup_test("ensure_capacity_smaller")
setup_test("ensure_capacity_same")
setup_test("ensure_capacity_bigger")
setup_test("ensure_capacity_no_resize_same")
setup_test("ensure_capacity_no_resize_bigger")
setup_test("complex_flow")
setup_test("append_string_stress")

