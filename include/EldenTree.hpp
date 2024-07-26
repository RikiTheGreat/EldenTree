//
// Created by mahdi on 7/17/24.
//

#ifndef ELDENTREE_HPP
#define ELDENTREE_HPP

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <unordered_map>

#include "God.hpp"
#include "types.hpp"

namespace et {
/**
 * @class EldenTree
 * @brief Manages Gods and their events.
 */
class EldenTree final {
public:
  explicit EldenTree(land::iland32 landNumber = 1);
  ~EldenTree();

  /**
   * @brief Adds a God and associated action to the EldenTree.
   *
   * @param god The God to be added.
   * @param action The action associated with the God.
   * @throw std::runtime_error if the God is already present.
   */
  void addGod(god::God const &god, god::GodAction action);
  /**
   * @brief Adds an event related to a specific God.
   * @param god The God to be added.
   * @param event The event associated with the God.
   */
  void addEvent(god::God const &god, god::GodEvent const &event) noexcept;

  /**
   * @brief Adds an event related to a specific God (string version).
   * @param god The God to be added.
   * @param event The event associated with the God.
   */
  void addEvent(god::God const &god, std::string const &event) noexcept;

  /**
   * @brief stop the EldenTree.
   */
  void stop();

  /**
   * @brief  For waiting until events are processed
   * @note you should return this function from your main
   * @return int Exit status code for main
   */
  [[nodiscard]] int exec();

  /**
   * @brief Connect god1 and god2 events together
   * @param god1
   * @param god2
   */
  void connect(god::God const &god1, god::God const &god2);

private: // methods
  /**
   * @brief Enternal event loop
   */
  void eventLoop();

private:
  GodsWithActions _gods;
  EventQueue _eventQueues;
  god::GodConnection _connections;
  land::iland32 _landNumber{};
  land::Lands _lands;
  std::atomic<bool> _running;
  std::atomic<bool> _eventsPending;
  std::mutex _mutex;
  std::condition_variable _cv;
  std::condition_variable
      _eventsProcessed; // For waiting until events are processed
};

#if HAS_FOLD_EXPRESSIONS
#if HAS_CONCEPTS
template <typename FirstGod, typename SecondGod, typename... OtherGods>
  requires et::god::IsGod<FirstGod> && et::god::IsGod<SecondGod> &&
           (et::god::IsGod<OtherGods> && ...)
#else
template <typename FirstGod, typename SecondGod, typename... OtherGods,
          typename std::enable_if<
              std::is_same<FirstGod, god::God>::value &&
                  std::is_same<SecondGod, god::God>::value &&
                  (... && std::is_same<OtherGods, god::God>::value),
              int>::type = 0>
#endif
void connect(et::EldenTree &tree, FirstGod const &first,
             SecondGod const &second, OtherGods const &...other_gods) {
  tree.connect(first, second);
  // Connect the first god with each of the other gods
  (tree.connect(first, other_gods), ...);
  connect(tree, second,
          other_gods...); // Recur for the second god and remaining gods
}

#if HAS_CONCEPTS
template <typename LastGod>
  requires et::god::IsGod<LastGod>
#else
template <typename LastGod,
          typename std::enable_if<std::is_same<LastGod, god::God>::value,
                                  int>::type = 0>
#endif

void connect(et::EldenTree &tree, FirstGod const &first,
             SecondGod const &second, OtherGods... other_gods) {
  tree.connect(first, second);
  (tree.connect(first, other_gods),
   ...); // Connect the first god with each of the other gods
  connect(tree, second,
          other_gods...); // Recur for the second god and remaining gods
}

void connect(et::EldenTree &tree, LastGod const &god) {
  // only one god left that does nothing othing to connect, end recursion
}

#else

template <typename GodOne, typename GodTwo>
void connect(et::EldenTree &tree, const GodOne &god1, const GodTwo &god2) {
  tree.connect(god1, god2);
}

/**
 * @brief Connect multiple gods together
 * @note Recursive variadic template for three or more gods
 * @tparam FirstGod
 * @tparam SecondGod
 * @tparam ThirdGod
 * @tparam OtherGods
 * @param tree
 * @param god1
 * @param god2
 * @param god3
 * @param other_gods
 */
template <typename FirstGod, typename SecondGod, typename ThirdGod,
          typename... OtherGods>
void connect(et::EldenTree &tree, FirstGod const &god1, SecondGod const &god2,
             ThirdGod const &god3, OtherGods const &...other_gods) {
  tree.connect(god1, god2);
  if (sizeof...(other_gods) > 0) { // Check if there are more gods to process
    connect(tree, god1, god3,
            other_gods...); // Continue connecting the first god with all others
    connect(tree, god2, god3,
            other_gods...); // Continue the pattern for the second god
  } else {
    connect(tree, god1, god3); // Final connect for the trio of gods
    connect(tree, god2, god3); // Ensures all pairings are covered
  }
}

#endif
} // namespace et
#endif // ELDENTREE_HPP
