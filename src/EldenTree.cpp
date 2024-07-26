//
// Created by mahdi on 7/17/24.
//

#include "EldenTree.hpp"
#include "logger.hpp"

et::EldenTree::EldenTree(land::iland32 landNumber)
    : _landNumber(landNumber), _running(true), _eventsPending(false) {
#if HAS_JTHREAD
  for (int i{}; i < _landNumber; ++i) {
    _lands.emplace_back(&EldenTree::eventLoop, this);
  }

#else
  for (int i = 0; i < _landNumber; ++i) {
    _lands.emplace_back(std::thread(&EldenTree::eventLoop, this));
  }

#endif
}

et::EldenTree::~EldenTree() { this->stop(); }

void et::EldenTree::addGod(god::God const &god, god::GodAction action) {
  std::unique_lock<std::mutex> lock(this->_mutex);
  if (_gods.find(god) != _gods.end()) {
    throw std::runtime_error("Adding a God Twice");
  }

  _gods[god] = action;
}

void et::EldenTree::addEvent(god::God const &god,
                             god::GodEvent const &event) noexcept {
  std::unique_lock<std::mutex> lock(this->_mutex);

  if (!_connections[god].empty()) {
    for (auto const &g : _connections[god])
      _eventQueues[g].emplace(event);
  } else {
    _eventQueues[god].emplace(event);
  }

  _eventsPending.store(true);
  _cv.notify_one();
}

void et::EldenTree::addEvent(god::God const &god,
                             std::string const &event) noexcept {
  std::unique_lock<std::mutex> lock(this->_mutex);
  god::GodEvent tmp_event;
  tmp_event.info = event;

  if (!_connections[god].empty()) {
    for (auto const &g : _connections[god])
      _eventQueues[g].emplace(tmp_event);
  } else {
    _eventQueues[god].emplace(tmp_event);
  }
  _eventsPending.store(true);
  _cv.notify_one();
}

void et::EldenTree::stop() {
  if (!_running.exchange(false)) {
#if HAS_SOURCE_LOCATION
    log("program has already stopped");
#else
    LOG("program has alreay stopped");
#endif
    return;
  }

  _cv.notify_all();

#if HAS_JTHREAD == 0
  for (auto &l : _lands) {
    if (l.joinable()) {
      l.join();
    }
  }

#endif
}

int et::EldenTree::exec() {
  std::unique_lock<std::mutex> lock(this->_mutex);
  _eventsProcessed.wait(lock,
                        [this]() { return !this->_eventsPending.load(); });
  return 0;
}

void et::EldenTree::connect(god::God const &god1, god::God const &god2) {
  std::lock_guard<std::mutex> lock(_mutex);
  _connections[god1].emplace(god2);
  _connections[god2].emplace(god1); // For bidirectional connection
}

void et::EldenTree::eventLoop() {
  while (_running) {
    std::map<god::God, std::queue<god::GodEvent>> localEventQueues;

    {
      std::unique_lock<std::mutex> lock(this->_mutex);
      _cv.wait(lock, [this]() { return !_eventQueues.empty() || !_running; });

      if (!_running && _eventQueues.empty()) {
        return; // Exit thread if stopping and no events are left
      }

      localEventQueues.swap(_eventQueues); // Swap queues to process them
                                           // without holding the mutex
      if (!localEventQueues.empty()) {
        _eventsPending.store(false);
      }
    }

    for (auto &pair : localEventQueues) {
      const god::God &g = pair.first;
      auto &queue = pair.second;

      while (!queue.empty()) {
        god::GodEvent event = queue.front();
        queue.pop();

        if (_gods.find(g) != _gods.end()) {
          _gods[g](event); // Process event
        }
      }
    }

    {
      std::unique_lock<std::mutex> lock(this->_mutex);
      if (_eventQueues.empty()) {
        _eventsProcessed.notify_all(); // Notify that all events are processed
      }
    }
  }
}
