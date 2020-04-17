
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

