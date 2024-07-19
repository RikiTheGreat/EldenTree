//
// Created by mahdi on 7/19/24.
//

#include "et/eldentree.hpp"
#include <benchmark/benchmark.h>


static void BM_EldenTree(benchmark::State& state) {
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

    for (auto _ : state) {
        tree.addEvent(Medusa, "hi");
    }
}

BENCHMARK(BM_EldenTree);

BENCHMARK_MAIN();