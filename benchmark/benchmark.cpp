//
// Created by mahdi on 7/19/24.
//

#include "et/eldentree.hpp"
#include <benchmark/benchmark.h>


static void BM_SomeFunction(benchmark::State& state) {
    // Perform setup here
    et::god::God const Medusa{
        .name = "Medusa",
        .id = 2
    };

    et::god::God const Z{
        .name = "Z",
        .id = 1
    };
    et::EldenTree tree;
    tree.connect(Z, Medusa);

    for (auto _ : state) {
        tree.addEvent(Medusa, "hi");
        tree.addEvent(Z, "bye");
    }
    BENCHMARK_DONT_OPTIMIZE;
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);
// Run the benchmark
BENCHMARK_MAIN();