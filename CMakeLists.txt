cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE /home/mahdi/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(et VERSION 2.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
            -Wall        # Enable all warnings
            -Wextra      # Enable extra warnings
    )
elseif(MSVC)
    add_compile_options(
            /W4         # Enable level 4 warnings in MSVC
    )
endif()

option(DO_TEST "enable testing" ON)
option(DO_DOC "enable generating documentation" ON)
option(DO_FORMAT "enable formatting" ON)
option(DO_EXAMPLE "enable example" ON)
option(DO_TIDY "enable clang tidy " ON)
option(DO_BENCH "enable benchmarking " ON)

if(DO_FORMAT)
    # appending cmake path to cmake module in case of including my clang format module
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
endif ()
if(DO_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=clang-diagnostic-*,-clang-diagnostic-unused-value,clang-analyzer-*,performance-*,readability-*,\
-readability-braces-around-statements, -readability-named-parameter")
endif ()



if(DO_EXAMPLE)
    add_subdirectory(example)
endif()

if(DO_TEST)
    add_subdirectory(tests)
endif ()

if(DO_DOC)
    add_subdirectory(doc)
endif ()

if(DO_BENCH)
  add_subdirectory(benchmark)
endif ()

add_subdirectory(src)