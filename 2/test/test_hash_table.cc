#include "gtest/gtest.h"
#include "../lib/hash_table.h"

struct TestStruct {
    int *value_;
    TestStruct() : value_(new int(0)) {}
    TestStruct(int value) : value_(new int(value)) {}
    TestStruct(const TestStruct &other) : value_(new int(*other.value_)) {}
    TestStruct(TestStruct &&other) : value_(other.value_) {
        other.value_ = nullptr;
    }

    TestStruct &operator=(const TestStruct &other) {
        if (this == &other) {
            return *this;
        }
        delete value_;
        value_ = new int(*other.value_);
        return *this;
    }

    TestStruct &operator=(TestStruct &&other) {
        if (this == &other) {
            return *this;
        }
        delete value_;
        value_ = other.value_;
        other.value_ = nullptr;
        return *this;
    }
    TestStruct &operator=(int value) {
        delete value_;
        value_ = new int(value);
        return *this;
    }
    ~TestStruct() {
        delete value_;
    }

    int operator*() {
        return *value_;
    }


};

TEST(THashTableTest, DefaultConstructor) {
    THashTable<int, TestStruct> table;
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.capacity(), 0);
}

TEST(THashTableTest, ParameterizedConstructor) {
    THashTable<int, TestStruct> table(10);
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.capacity(), 10);
}

TEST(THashTableTest, Insert) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_EQ(table.size(), 2);
    EXPECT_EQ(table.capacity(), 10);
    EXPECT_EQ(*((*(table.find(1))).value_), 1);
    EXPECT_EQ(*((*(table.find(2))).value_), 2);
}

TEST(THashTableTest, RemoveExistingKey_FirstElement) {
    THashTable<int, TestStruct> hashTable(10);
    hashTable.insert(1, 1);
    hashTable.insert(2, 2);
    hashTable.insert(3, 3);

    hashTable.remove(1);

    EXPECT_EQ(hashTable.size(), 2);
    EXPECT_THROW(hashTable[1], std::out_of_range);
}

TEST(THashTableTest, RemoveExistingKey_NotFirstElement) {
    THashTable<int, TestStruct> hashTable(10);
    hashTable.insert(1, 1);
    hashTable.insert(2, 2);
    hashTable.insert(3, 3);

    hashTable.remove(2);

    EXPECT_EQ(hashTable.size(), 2);
    EXPECT_THROW(hashTable[2], std::out_of_range);
}

TEST(THashTableTest, RemoveNonExistingKey) {
    THashTable<int, TestStruct> hashTable(10);
    hashTable.insert(1, 1);
    hashTable.insert(2, 2);

    EXPECT_THROW(hashTable.remove(3), std::out_of_range);
    EXPECT_EQ(hashTable.size(), 2);
}

TEST(THashTableTest, Contains) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_TRUE(table.contains(1));
    EXPECT_TRUE(table.contains(2));
    EXPECT_FALSE(table.contains(3));
}

TEST(THashTableTest, Size) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_EQ(table.size(), 2);
}

TEST(THashTableTest, Capacity) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_EQ(table.capacity(), 10);
}

TEST(THashTableTest, Clear) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    table.clear();
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.capacity(), 0);
}

TEST(THashTableTest, Resize) {
    THashTable<int, TestStruct> table(2);
    table.insert(1, 1);
    table.insert(2, 2);
    table.insert(3, 3);
    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(table.capacity(), 4);
}

TEST(THashTableTest, Iterator) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    auto it = table.begin();
    EXPECT_EQ((*it).key_, 1);
    EXPECT_EQ(*((*it).value_), 1);
    ++it;
    EXPECT_EQ((*it).key_, 2);
    EXPECT_EQ(*((*it).value_), 2);
}

TEST(THashTableTest, End) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    auto it = table.end();
    EXPECT_NE(it, table.begin());
}

TEST(THashTableTest, Find) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    auto it = table.find(1);
    EXPECT_EQ((*it).key_, 1);
    EXPECT_EQ(*((*it).value_), 1);
}

TEST(THashTableTest, OperatorBracket) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(2, 2);
    EXPECT_EQ(*(table[1]), 1);
    EXPECT_EQ(*(table[2]), 2);
}

TEST(THashTableTest, CopyAssignment) {
    // Create a hash table
    THashTable<int, TestStruct> hashTable{};

    // Insert some elements
    hashTable.insert(-1, 1);
    hashTable.insert(-2, 2);

    // Create another hash table
    THashTable<int, TestStruct> anotherHashTable{};

    // Assign the first hash table to the second
    anotherHashTable = hashTable;

    // Check if the assignment was successful
    EXPECT_EQ(anotherHashTable.size(), 2);
    EXPECT_EQ(*(anotherHashTable[-1]), 1);
    EXPECT_EQ(*(anotherHashTable[-2]), 2);

    // Modify the first hash table
    hashTable.insert(-3, 3);

    // Check if the second hash table remains unchanged
    EXPECT_EQ(anotherHashTable.size(), 2);
    EXPECT_EQ(*(anotherHashTable[-1]), 1);
    EXPECT_EQ(*(anotherHashTable[-2]), 2);
}

TEST(THashTableTest, MoveAssignment) {
    // Create a hash table
    THashTable<int, TestStruct> hashTable{};

    // Insert some elements
    hashTable.insert(-1, 1);
    hashTable.insert(-2, 2);

    // Create another hash table
    THashTable<int, TestStruct> anotherHashTable{};

    // Move assign the first hash table to the second
    anotherHashTable = std::move(hashTable);

    // Check if the move assignment was successful
    EXPECT_EQ(anotherHashTable.size(), 2);
    EXPECT_EQ(*(anotherHashTable[-1]), 1);
    EXPECT_EQ(*(anotherHashTable[-2]), 2);

    // Check if the first hash table is in a valid but unspecified state
    EXPECT_EQ(hashTable.size(), 0);
}

TEST(THashTableTest, CopyConstructor) {
    // Create a hash table
    THashTable<int, TestStruct> hashTable{};

    // Insert some elements
    hashTable.insert(-1, 1);
    hashTable.insert(-2, 2);

    // Create another hash table by copying the first
    THashTable anotherHashTable(hashTable);

    // Check if the copy was successful
    EXPECT_EQ(anotherHashTable.size(), 2);
    EXPECT_EQ(*(anotherHashTable[-1]), 1);
    EXPECT_EQ(*(anotherHashTable[-2]), 2);

    // Modify the first hash table
    hashTable.insert(-3, 3);

    // Check if the second hash table remains unchanged
    EXPECT_EQ(anotherHashTable.size(), 2);
    EXPECT_EQ(*(anotherHashTable[-1]), 1);
    EXPECT_EQ(*(anotherHashTable[-2]), 2);
}

TEST(THashTableTest, MoveConstructor) {
    // Create a hash table
    THashTable<int, TestStruct> hashTable{};

    // Insert some elements
    hashTable.insert(-1, 1);
    hashTable.insert(-2, 2);

    // Create another hash table by moving the first
    THashTable anotherHashTable(std::move(hashTable));

    // Check if the move was successful
    EXPECT_EQ(anotherHashTable.size(), 2);
    EXPECT_EQ(*(anotherHashTable[-1]), 1);
    EXPECT_EQ(*(anotherHashTable[-2]), 2);

    // Check if the first hash table is in a valid but unspecified state
    EXPECT_EQ(hashTable.size(), 0);
}

TEST(THashTableTest, AddMultipleElementsWithTheSameHash) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(11, 2);
    table.insert(21, 3);
    table.insert(31, 4);
    EXPECT_EQ(table.size(), 4);
    EXPECT_EQ(*(table[1]), 1);
    EXPECT_EQ(*(table[11]), 2);
    EXPECT_EQ(*(table[21]), 3);
    EXPECT_EQ(*(table[31]), 4);
}

TEST(THashTableTest, RemoveOneOfElementsWithTheSameHash) {
    THashTable<int, TestStruct> table(10);
    table.insert(1, 1);
    table.insert(11, 2);
    table.insert(21, 3);
    table.insert(31, 4);
    table.remove(11);
    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(*(table[1]), 1);
    EXPECT_EQ(*(table[21]), 3);
    EXPECT_EQ(*(table[31]), 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
