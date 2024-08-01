//
// Created by mahdi on 7/17/24.
//

#ifndef TYPES_HPP
#define TYPES_HPP

#include <map>
#include <queue>
#include <set>
#include <string>
#include <thread>
#include <vector>

#ifdef __has_include
#if __has_include(<thread> ) && __cplusplus >= 202002L
#if defined(__cpp_lib_jthread) && __cpp_lib_jthread >= 201911L
#define HAS_JTHREAD 1
#else
#define HAS_JTHREAD 0
#endif
#else
#define HAS_JTHREAD 0
#endif
#endif

#ifdef __has_include
#if __has_include(<concepts>) && __cplusplus >= 202002L
#if defined(__cpp_concepts) && __cpp_concepts >= 201907L
#define HAS_CONCEPTS 1
#else
#define HAS_CONCEPTs 0
#endif
#else
#define HAS_CONCEPTS 0
#endif
#endif

#ifdef __has_include
#if defined(__cplusplus) && __cplusplus >= 201703L
#define HAS_FOLD_EXPRESSIONS 1
#else
#define HAS_FOLD_EXPRESSIONS 0
#endif
#endif

namespace et::god {
struct God;
struct GodEvent;
using GodName = std::string;
using GodId = int;
// C style function pointer is faster than std::function
using GodAction = void (*)(GodEvent const &);
using GodConnection = std::unordered_map<god::God, std::set<god::God>>;

#if HAS_CONCEPTS
template <typename T>
concept IsGod = std::is_same_v<T, god::God>;
#endif

} // namespace et::god

namespace et {
using GodsWithActions = std::map<god::God, god::GodAction>;
using EventQueue = std::map<god::God, std::queue<god::GodEvent>>;

} // namespace et

namespace et::land {
#define NUMBER_OF_LANDS std::thread::hardware_concurrency()

#if HAS_JTHREAD
using Lands = std::vector<std::jthread>;
#else
using Lands = std::vector<std::thread>;
#endif

using iland32 = int;

} // namespace et::land

#endif
