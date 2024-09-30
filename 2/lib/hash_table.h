#ifndef LAB2_LIB_HASH_TABLE_H
#define LAB2_LIB_HASH_TABLE_H

#include <cstddef>
#include <functional>
#include <stdexcept>

template<typename T>
size_t hash(const T &key) {
    return std::hash<T>{}(key);
}

template<class T1, class T2> 
class THashTable {
public:
    struct Node {
        T1 key;
        T2 value;
        bool is_taken = false;
        bool is_last = false;
        size_t prev;
        size_t next;

        Node() = default;
        Node(const T1 &key, const T2 &value, bool is_taken, size_t prev, size_t next, bool is_last) : key(key), value(value), is_taken(is_taken), prev(prev), next(next), is_last(is_last) {}
    };

    class Iterator {
    public:
        virtual Node &operator*() const {
            return *ptr;
        }
        virtual bool operator==(const Iterator &other) const {
            return ptr == other.ptr;
        }
        virtual bool operator!=(const Iterator &other) const {
            return ptr != other.ptr;
        }
        virtual Iterator &operator++() {
            ++ptr;
            while (!(*ptr).is_taken && !(*ptr).is_last) {
                ++ptr;
            }
            return *this;
        }

        virtual ~Iterator() = default;

        Iterator(Node *init_ptr) : ptr(init_ptr) {}

    private:
        Node *ptr = nullptr;
    };

        virtual T2 &operator[](const T1 &key) {
        return (*find(key)).value;
    }
    void operator=(THashTable &other) {
        table = new Node[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        for (auto &i : other) {
            insert(i.key, i.value);            
        }        
    };
    
    THashTable() = default;
    THashTable(size_t capacity) {
        table = new Node[capacity];
        capacity_ = capacity;
        for (size_t i = 0; i < capacity_; ++i) {
            table[i].next = table[i].prev = i;
        }
    }
    THashTable(THashTable &other) {
        table = new Node[other.capacity_];
        capacity_ = other.capacity_;
        for (auto &i : other) {
            insert(i.key, i.value);
        }
        size_ = other.size_;
    }
    THashTable(Node *table, size_t size, size_t capacity) : table(table), size_(size), capacity_(capacity) {}
    THashTable(THashTable &&other) : table(other.table), size_(other.size_), capacity_(other.capacity_) {
        other.table = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    virtual ~THashTable() {
        delete[] table;
        table = nullptr;
    }

    virtual Iterator begin() {
        for (size_t i = 0; i < capacity_; ++i) {
            if (table[i].is_taken) {
                return Iterator(table + i);
            }
        }
        return end();
    }
    virtual Iterator end() {
        return Iterator(table + capacity_);
    }
    virtual Iterator find(const T1 &key) {
        auto index = hash(key) % capacity_;
        while (table[index].key != key || !table[index].is_taken) {
            index = table[index].next;
            if (index == (hash(key) % capacity_)) {
                return end();
            }
        }
        return Iterator(table + index);
    }
    virtual void insert(const T1 &key, const T2 &value) {
        if (size_ == capacity_) {
            resize();
        }
        auto index = hash(key) % capacity_;
        auto prev_index = table[index].prev;
        auto next_index = index;
        while (table[index].is_taken) {
            index = (index + 1) % capacity_;
        }
        if (index == (hash(key) % capacity_)) {
            prev_index = index;
        }
        auto is_last = index == capacity() - 1;
        table[index] = Node(key, value, true, prev_index, next_index, is_last);
        ++size_;
    }
    virtual void remove(const T1 &key) {
        auto hash_index = hash(key) % capacity_;
        auto element = find(key);
        if ((*element).key == table[hash_index].key) {
            auto next = table[hash_index].next;
            table[hash_index].key = table[next].key;
            table[hash_index].value = table[next].value;
            table[hash_index].next = table[next].next;
            table[next].is_taken = false;
            auto new_next = table[hash_index].next;
            table[new_next].prev = hash_index;
            if (table[hash_index].is_last) {
                table[hash_index].is_last = false;
            }
        }
        else {
            auto new_next = table[(*element).next].next;
            table[new_next].prev = (*element).prev;
            table[(*element).key].is_taken = false;
        }
        --size_;
    }
    virtual bool contains(const T1 &key) {
        return find(key) != end();
    }
    virtual size_t size() const {
        return size_;
    }
    virtual size_t capacity() const {
        return capacity_;
    }
    virtual void clear() {
        size_ = 0;
        capacity_ = 0;
        delete[] table;
        table = nullptr;
    }
private:
    Node *table = nullptr;
    size_t capacity_ = 0;
    size_t size_ = 0;

    void resize() {
        capacity_ *= 2;
        auto *new_table = new Node[capacity_];
        auto *old_table = table;
        auto old_size = size_;
        table = new_table;
        size_ = 0;
        for (size_t i = 0; i < old_size; ++i) {
            insert(table[i].key, table[i].value);
        }
        for (size_t i = 0; i < size_; ++i) {
            if (!new_table[i].is_taken) {
                new_table[i].next = new_table[i].prev = i;                
            }       
        }
        delete[] old_table;
    }
};

#endif //LAB2_LIB_HASH_TABLE_H

