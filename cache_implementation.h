#ifndef CACHE_IMPLEMENTATION_H
#define CACHE_IMPLEMENTATION_H

#include <list>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <unordered_map>
#include <utility>

template <typename Key, typename Value>
class CacheImpl {
 public:
  CacheImpl(std::size_t capacity) : _capacity(capacity) {}

  std::optional<Value> get(const Key& key) {
    std::shared_lock<std::shared_mutex> read_lock(_mutex);

    auto it = _cache.find(key);
    if (it == _cache.end()) {
      return std::nullopt;
    }

    read_lock.unlock();
    std::unique_lock<std::shared_mutex> write_lock(_mutex);

    _keys.splice(_keys.begin(), _keys, it->second.second);
    return it->second.first;
  }

  void put(const Key& key, const Value& value) {
    std::unique_lock<std::shared_mutex> write_lock(_mutex);
    auto it = _cache.find(key);
    if (it != _cache.end()) {
      // Key already exists; update value and move to front
      it->second.first = value;
      _keys.splice(_keys.begin(), _keys, it->second.second);
    } else {
      // Insert a new key-value pair
      if (_keys.size() == _capacity) {
        // Evict the least recently used item
        Key key_to_remove = _keys.back();
        _keys.pop_back();
        _cache.erase(key_to_remove);
      }

      _keys.push_front(key);
      _cache[key] = {value, _keys.begin()};
    }
  }

 private:
  std::shared_mutex _mutex;
  const size_t _capacity;
  std::list<Key> _keys;
  std::unordered_map<
      Key, typename std::pair<Value, typename std::list<Key>::iterator>>
      _cache;
};

#endif  // CACHE_IMPLEMENTATION_H
