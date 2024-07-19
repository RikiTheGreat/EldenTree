//
// Created by mahdi on 7/17/24.
//

#ifndef TYPES_HPP
#define TYPES_HPP

#include <map>
#include <queue>
#include <string>

namespace et::god {
struct God;
struct GodEvent;
using GodName = std::string;
using GodId = int;
using GodAction = void (*)(GodEvent const &);  // C style function pointer is faster than std::function

}  // namespace et::god

namespace et {
using GodsWithActions = std::map<god::God, god::GodAction>;
using EventQueue = std::map<god::God, std::queue<god::GodEvent>>;
}  // namespace et
#endif  // TYPES_HPP
