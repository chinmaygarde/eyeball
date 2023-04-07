cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CCACHE_PROGRAM NAMES ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools")

project(eyeball)

enable_testing()

add_subdirectory(third_party/googletest)
add_subdirectory(third_party/fml)
set(GOOGLETEST_PATH "third_party/googletest")
set(BENCHMARK_ENABLE_TESTING FALSE)
add_subdirectory(third_party/googlebenchmark)

include(GoogleTest)

add_library(eyeball
  src/image.h
  src/image.cc
)

target_compile_options(eyeball
  PRIVATE
    -Werror
    -Wall
    -Wextra
    -Wno-unused-parameter
    -Wno-missing-field-initializers
)

target_compile_definitions(eyeball
  PUBLIC
    -D_CRT_SECURE_NO_WARNINGS
)

target_link_libraries(eyeball fml)

target_include_directories(eyeball
  PUBLIC
    src
    third_party/stb
)

add_executable(eyeball_unittests
  src/unittests.cc
)

target_link_libraries(eyeball_unittests eyeball gtest_main)

get_filename_component(EYEBALL_ASSETS_LOCATION assets ABSOLUTE)
configure_file(src/fixtures_location.h.in fixtures_location.h @ONLY)
target_include_directories(eyeball_unittests PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

gtest_discover_tests(eyeball_unittests)

add_executable(eyeball_benchmarks
  src/benchmarks.cc
)

target_link_libraries(eyeball_benchmarks eyeball benchmark::benchmark)
target_include_directories(eyeball_benchmarks PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
