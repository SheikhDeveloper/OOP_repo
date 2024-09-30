#include "gtest/gtest.h"
#include "../lib/hash_table.h"

TEST(THashTableTest, DefaultConstructor) {
    THashTable<int, int> table;
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.capacity(), 0);
}

TEST(THashTableTest, ParameterizedConstructor) {
    THashTable<int, int> table(10);
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.capacity(), 10);
}

TEST(THashTableTest, CopyConstructor) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    THashTable<int, int> copy(table);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.capacity(), 10);
    EXPECT_EQ((*(copy.find(1))).value, 1);
    EXPECT_EQ((*(copy.find(2))).value, 2);
}

TEST(THashTableTest, MoveConstructor) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    THashTable<int, int> moved(std::move(table));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved.capacity(), 10);
    EXPECT_EQ((*(moved.find(1))).value, 1);
    EXPECT_EQ((*(moved.find(2))).value, 2);
}

TEST(THashTableTest, Insert) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_EQ(table.size(), 2);
    EXPECT_EQ(table.capacity(), 10);
    EXPECT_EQ((*(table.find(1))).value, 1);
    EXPECT_EQ((*(table.find(2))).value, 2);
}

TEST(THashTableTest, Remove) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    table.remove(1);
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.capacity(), 10);
    EXPECT_EQ((*(table.find(2))).value, 2);
}

TEST(THashTableTest, Contains) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_TRUE(table.contains(1));
    EXPECT_TRUE(table.contains(2));
    EXPECT_FALSE(table.contains(3));
}

TEST(THashTableTest, Size) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_EQ(table.size(), 2);
}

TEST(THashTableTest, Capacity) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_EQ(table.capacity(), 10);
}

TEST(THashTableTest, Clear) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    table.clear();
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.capacity(), 0);
}

TEST(THashTableTest, Resize) {
    THashTable<int, int> table(2);
    table.insert(1, 1);
    table.insert(2, 2);
    table.insert(3, 3);
    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(table.capacity(), 4);
}

TEST(THashTableTest, Iterator) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    auto it = table.begin();
    EXPECT_EQ((*it).key, 1);
    EXPECT_EQ((*it).value, 1);
    ++it;
    EXPECT_EQ((*it).key, 2);
    EXPECT_EQ((*it).value, 2);
}

TEST(THashTableTest, End) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    auto it = table.end();
    EXPECT_NE(it, table.begin());
}

TEST(THashTableTest, Find) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    auto it = table.find(1);
    EXPECT_EQ((*it).key, 1);
    EXPECT_EQ((*it).value, 1);
}

TEST(THashTableTest, OperatorBracket) {
    THashTable<int, int> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_EQ(table[1], 1);
    EXPECT_EQ(table[2], 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
