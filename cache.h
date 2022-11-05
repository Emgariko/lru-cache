#pragma once

#include <utility>
#include <list>
#include <unordered_map>
#include <optional>

struct LRUCache {
    explicit LRUCache(int capacity);

    void put(int key, int value);
    std::optional<int> get(int key);
private:
    using iter = std::list<std::pair<int, int>>::iterator;
    std::unordered_map<int, iter> table;
    std::list<std::pair<int, int>> elems;
    int capacity;
};