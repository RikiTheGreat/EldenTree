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
} // namespace et

#endif // ELDENTREE_HPP
