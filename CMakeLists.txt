
cmake_minimum_required (VERSION 3.7)

project (string_buffer C)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(X_CMAKE_PROJECT_ROOT_DIR ${CMAKE_BINARY_DIR}/..)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

# define all sources
file(GLOB SOURCES "src/*.c")
file(GLOB HEADER_SORUCES "include/*.h")
file(GLOB TEST_SOURCES "tests/*.c")

# format code
if(NOT DEFINED ENV{X_CMAKE_UNCRUSTIFY_DISABLED})
  add_custom_target(uncrustify ALL
    uncrustify
    -c ${X_CMAKE_PROJECT_ROOT_DIR}/uncrustify.cfg
    --no-backup ${SOURCES} ${HEADER_SORUCES} ${TEST_SOURCES})
endif()

# create static library
add_library(string_buffer STATIC ${SOURCES})

# tests
enable_testing()
add_executable(test_string_buffer ${TEST_SOURCES})
target_link_libraries(test_string_buffer string_buffer)
add_test(NAME new
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer new)
add_test(NAME new_with_size_zero
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer new_with_size_zero)
add_test(NAME new_with_size_negative
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer new_with_size_negative)
add_test(NAME new_with_size_positive
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer new_with_size_positive)
add_test(NAME append_no_resize
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_no_resize)
add_test(NAME append_with_single_resize
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_with_single_resize)
add_test(NAME append_with_multiple_resize
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_with_multiple_resize)
add_test(NAME append_string_no_resize
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_string_no_resize)
add_test(NAME append_string_with_single_resize
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_string_with_single_resize)
add_test(NAME append_bool
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_bool)
add_test(NAME append_short
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_short)
add_test(NAME append_int
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_int)
add_test(NAME append_int_negative
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_int_negative)
add_test(NAME append_long
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_long)
add_test(NAME append_long_long
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND test_string_buffer append_long_long)

