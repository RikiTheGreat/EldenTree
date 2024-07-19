//
// Created by mahdi on 7/17/24.
//

#include "EldenTree.hpp"

#include "logger.hpp"

et::EldenTree::EldenTree()
    : _running(true), _eventsPending(false) {
#if HAS_JTHREAD
    _worker = std::jthread(&EldenTree::eventLoop, this);
#else
    _worker = std::thread(&EldenTree::eventLoop, this);
#endif
}

et::EldenTree::~EldenTree() {
    this->stop();
}

void et::EldenTree::addGod(god::God const &god, god::GodAction action) {
    std::unique_lock<std::mutex> lock(this->_mutex);
    if (_gods.find(god) != _gods.end())
        throw std::runtime_error("Adding a God Twice");

    _gods[god] = action;
}

void et::EldenTree::addEvent(god::God const &god, god::GodEvent const &event) noexcept {
    std::unique_lock<std::mutex> lock(this->_mutex);
    if (!_connections.empty()) {
        _eventQueues[_connections[god].at(0)].push(event);

    } else
        _eventQueues[god].push(event);

    _eventsPending.store(true);
    _cv.notify_one();
}

void et::EldenTree::addEvent(god::God const &god, std::string const &event) noexcept {
    std::unique_lock<std::mutex> lock(this->_mutex);
    god::GodEvent e;
    e.info = event;

    _eventQueues[god].push(e);
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
        std::exit(-1);
    }

    _cv.notify_all();

#if HAS_JTHREAD == 0
    if (_worker.joinable())
        _worker.join();
#endif
}

int et::EldenTree::exec() {
    std::unique_lock<std::mutex> lock(this->_mutex);
    _eventsProcessed.wait(lock, [this]() { return !this->_eventsPending.load(); });
    return 0;
}

void et::EldenTree::connect(god::God const &god1, god::God const &god2) {
    std::lock_guard<std::mutex> lock(_mutex);
    _connections[god1].push_back(god2);
    _connections[god2].push_back(god1);  // For bidirectional connection
}

void et::EldenTree::eventLoop() {
    while (_running) {
        std::unique_lock<std::mutex> lock(this->_mutex);
        _cv.wait(lock, [this]() {
            return !this->_eventQueues.empty() || !this->_running;
        });

        for (auto it = _eventQueues.begin(); it != _eventQueues.end();) {
            god::God g = it->first;
            std::queue<god::GodEvent> &queue = it->second;

            while (!queue.empty()) {
                god::GodEvent event = queue.front();
                queue.pop();
                lock.unlock();
                if (_gods.find(g) != _gods.end()) {
                    _gods[g](event);
                }
                lock.lock();
            }

            if (queue.empty()) {
                it = _eventQueues.erase(it);  // Remove the pair from the map and move to next element
            } else {
                ++it;  // Move to the next element in the iteration
            }
        }

        if (_eventQueues.empty()) {
            _eventsPending.store(false);  // No events pending
            _eventsProcessed.notify_all();
        }
    }
}