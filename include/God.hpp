//
// Created by mahdi on 7/17/24.
//

#ifndef GOD_HPP
#define GOD_HPP

#include <string>

#include "types.hpp"

#if defined(__cpp_impl_three_way_comparison) &&                                \
    __cpp_impl_three_way_comparison >= 201711L
#include <compare>
#define HAS_SPACESHIP_OPERATOR 1
#else
#define HAS_SPACESHIP_OPERATOR 0
#endif

namespace et::god {
struct God {
  GodName name;
  GodId id;

#if HAS_SPACESHIP_OPERATOR

  auto operator<=>(God const &other) const noexcept {
    return this->id <=> other.id;
  }

  bool operator==(const God &other) const { return id == other.id; }
#else

  bool operator<(God const &other) const { return this->id < other.id; }
  bool operator>(God const &other) const { return this->id > other.id; }
  bool operator<=(God const &other) const { return !(*this > other); }
  bool operator>=(God const &other) const { return !(*this < other); }
  bool operator==(God const &other) const { return this->id == other.id; }
  bool operator!=(God const &other) const { return !(*this == other); }
#endif
};

struct GodEvent {
  std::string info;
};

} // namespace et::god

// Custom hash function for god::God
namespace std {
template <> struct hash<et::god::God> {
  std::size_t operator()(const et::god::God &god) const noexcept {
    return std::hash<int>{}(god.id);
  }
};
} // namespace std
#endif // GOD_HPP
