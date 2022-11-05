#include "gtest/gtest.h"
#include "../cache.h"

TEST(BasicTests, empty) {
    LRUCache cache(1);

    EXPECT_EQ(cache.get(1), std::nullopt);
    EXPECT_EQ(cache.get(2), std::nullopt);

}

TEST(BasicTests, put) {
    LRUCache cache(1);

    cache.put(1, 1);

    EXPECT_EQ(cache.get(1), 1);
    EXPECT_EQ(cache.get(2), std::nullopt);
}

TEST(BasicTests, change_value_for_key) {
    LRUCache cache(1);

    cache.put(1, 1);
    EXPECT_EQ(cache.get(1), 1);

    cache.put(1, 2);
    EXPECT_EQ(cache.get(1), 2);
}

TEST(BasicTests, oversize) {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);

    EXPECT_EQ(cache.get(1), 1);
    EXPECT_EQ(cache.get(2), 2);

    cache.put(3, 3);

    EXPECT_EQ(cache.get(1), std::nullopt);
    EXPECT_EQ(cache.get(2), 2);
    EXPECT_EQ(cache.get(3), 3);
}

TEST(BasicTests, change_value_for_key_and_oversize) {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(1, 3);

    EXPECT_EQ(cache.get(1), 3);
    EXPECT_EQ(cache.get(2), 2);
}

TEST(BasicTests, key_value_pair_pops_up) {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);

    EXPECT_EQ(cache.get(1), 1);

    cache.put(3, 3);

    EXPECT_EQ(cache.get(2), std::nullopt);
    EXPECT_EQ(cache.get(3), 3);
    EXPECT_EQ(cache.get(1), 1);
}

TEST(BasicTests, common) {
    LRUCache cache(2);

    EXPECT_EQ(cache.get(1), std::nullopt);

    cache.put(1, 1);
    EXPECT_EQ(cache.get(1), 1);

    cache.put(2, 2);
    cache.put(3, 3);

    EXPECT_EQ(cache.get(1), std::nullopt);
    EXPECT_EQ(cache.get(3), 3);

    cache.put(4, 4);

    EXPECT_EQ(cache.get(2), std::nullopt);
    EXPECT_EQ(cache.get(4), 4);
}
