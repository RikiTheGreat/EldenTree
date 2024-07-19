message("Benchmarking enabled")
find_package(benchmark CONFIG REQUIRED)
add_executable(bench benchmark.cpp)

target_link_libraries(bench PRIVATE benchmark::benchmark benchmark::benchmark_main EldenTree)
