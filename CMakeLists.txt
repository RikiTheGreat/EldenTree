cmake_minimum_required(VERSION 3.20)
project(et VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(DO_TEST "enable testing" ON)
option(DO_DOC "enable generating documentation" ON)
option(DO_FORMAT "enable formatting" OFF)
option(DO_EXAMPLE "enable example" ON)
option(DO_TIDY "enable clang tidy " OFF)
option(DO_BENCH "enable benchmarking " ON)

if(DO_FORMAT)
    # appending cmake path to cmake module in case of including my clang format module
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
endif ()

add_subdirectory(src)
if(DO_EXAMPLE)
    add_subdirectory(example)
endif()

if(DO_TEST)
    add_subdirectory(tests)
endif ()

if(DO_DOC)
    add_subdirectory(doc)
endif ()

if(DO_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
endif ()

if(DO_BENCH)
  add_subdirectory(benchmark)
endif ()

