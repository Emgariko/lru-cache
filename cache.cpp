#include "cache.h"
#include <cassert>

LRUCache::LRUCache(int capacity_) : capacity(capacity_) {};

void LRUCache::put(int key, int val) {
    assert(table.size() <= capacity);
    assert(elems.size() <= capacity);

    auto it = table.find(key);
    if (it == table.end()) {
        if (elems.size() == capacity) {
            std::pair<int, int> lst = elems.back();
            table.erase(lst.first);
            elems.pop_back();
        }
        auto newly_inserted_elem_it = elems.insert(elems.begin(), {key, val});
        table[key] = newly_inserted_elem_it;
    } else {
        elems.erase(it->second);
        elems.push_front({key, val});
        table[key] = elems.begin();
    }

    assert(table.size() <= capacity);
    assert(elems.size() <= capacity);

    assert(elems.front() == std::make_pair(key, val));
}

std::optional<int> LRUCache::get(int key) {
    assert(table.size() <= capacity);
    assert(elems.size() <= capacity);

    auto it = table.find(key);
    if (it == table.end()) {
        return {};
    } else {
        int value = it->second->second;
        elems.erase(it->second);
        elems.push_front({key, value});
        table[key] = elems.begin();

        assert(elems.front() == std::make_pair(key, value));

        return value;
    }

    assert(table.size() <= capacity);
    assert(elems.size() <= capacity);
}