#ifndef LAB2_LIB_HASH_TABLE_H
#define LAB2_LIB_HASH_TABLE_H

#include <cstddef>
#include <functional>
#include <stdexcept>

/**
 * Hash function for a given type.
 *
 * @tparam T Type to hash
 * @param key Value to hash
 * @return Hashed value
 */
template<typename T>
size_t hash(const T &key) {
    return std::hash<T>{}(key);
}

/**
 * Hash table class.
 *
 * @tparam T1 Key type
 * @tparam T2 Value type
 */
template<class T1, class T2> 
class THashTable {
public:
    /**
     * Node structure for the hash table.
     */
    class Node {
    public:
        /**
         * Key of the node.
         */
        T1 key;
        /**
         * Value of the node.
         */
        T2 value;
        /**
         * Default constructor of the node.
         */
        Node() = default;

        /**
         * Constructor with key, value, and indices.
         *
         * @param key Key of the node
         * @param value Value of the node
         * @param is_taken Whether the node is taken
         * @param prev Previous node with the same hash index
         * @param next Next node with the same hash index
         * @param is_last Whether the node is the last node
         */
        Node(const T1 &key, const T2 &value, bool is_taken, size_t prev, size_t next, bool is_last) : key(key), value(value), is_taken_(is_taken), prev_(prev), next_(next), is_last_(is_last) {}

        bool isTaken() const {
            return is_taken_;
        }

        bool isLast() const {
            return is_last_;
        }

        size_t getPrev() const {
            return prev_;
        }

        size_t getNext() const {
            return next_;
        }

        void setTaken() {
            is_taken_ = true;
        }

        void setNotTaken() {
            is_taken_ = false;
        }

        void setLast() {
            is_last_ = true;
        }

        void setNotLast() {
            is_last_ = false;
        }

        void setNext(size_t next) {
            next_ = next;
        }

        void setPrev(size_t prev) {
            prev_ = prev;
        }
    private:
        /**
         * Whether the node is taken.
         */
        bool is_taken_ = false;
        /**
         * Whether the node is the last node.
         */
        bool is_last_ = false;
        /**
         * Previous node with ths same hash index.
         */
        size_t prev_;
        /**
         * Next node with the same hash index.
         */
        size_t next_;

    };

    /**
     * Iterator class for the hash table.
     */
    class Iterator {
    public:
        /**
         * Returns the current node.
         *
         * @return Current node
         */
        virtual Node &operator*() const {
            return *ptr;
        }
        /**
         * Checks if two iterators are equal.
         *
         * @param other Iterator to compare with
         * @return Whether the iterators are equal
         */
        virtual bool operator==(const Iterator &other) const {
            return ptr == other.ptr;
        }
        /**
         * Checks if two iterators are not equal.
         *
         * @param other Iterator to compare with
         * @return Whether the iterators are not equal
         */
        virtual bool operator!=(const Iterator &other) const {
            return ptr != other.ptr;
        }
        /**
         * Increments the iterator to the next taken node.
         * If the iterator is at the end, it stays there.
         *
         * @return Reference to the iterator
         */
        virtual Iterator &operator++() {
            ++ptr;
            while (!(*ptr).isTaken() && !(*ptr).isLast()) {
                ++ptr;
            }
            return *this;
        }

        /**
         * Iterator destructor.
         */
        virtual ~Iterator() = default;

        /**
         * Iterator constructor with a node pointer.
         *
         * @param init_ptr Node pointer
         */
        Iterator(Node *init_ptr) : ptr(init_ptr) {}

    private:
        /**
         * Node pointer.
         */
        Node *ptr = nullptr;
    };

    /**
     * Returns a reference to the value associated with the given key.
     *
     * @param key Key to find
     * @return Reference to the value
     */
    virtual T2 &operator[](const T1 &key) {
        auto result = find(key);
        if (result == end()) {
            throw std::out_of_range("Key not found");
        }
        return (*result).value;
    }

    /**
     * Assigns the contents of another hash table to this hash table.
     *
     * @param other Hash table to assign from
     */
    void operator=(THashTable &other) {
        try { table = new Node[other.capacity_]; }
        catch (...) {
            other.~THashTable();
            throw std::bad_alloc();
        }
        capacity_ = other.capacity_;
        size_ = other.size_;
        for (auto &i : other) {
            insert(i.key, i.value);            
        }        
    }

    /**
     * Assigns the contents of another const hash table to this hash table.
     *
     * @param other Hash table to assign from
     */
    void operator=(const THashTable &other) {
        try { table = new Node[other.capacity_]; }
        catch (...) {
            other.~THashTable();
            throw std::bad_alloc();
        }
        capacity_ = other.capacity_;
        size_ = other.size_;
        for (auto &i : other) {
            insert(i.key, i.value);            
        }        
    }
    
    /**
     * Default constructor.
     */
    THashTable() = default;
    /**
     * Constructor with a capacity.
     *
     * @param capacity Capacity of the hash table
     */
    THashTable(size_t capacity) {
        table = new Node[capacity];
        capacity_ = capacity;
        for (size_t i = 0; i < capacity_; ++i) {
            table[i].setNext(i);
            table[i].setPrev(i);
        }
    }
    /**
     * Copy constructor.
     *
     * @param other Hash table to copy from
     */
    THashTable(THashTable &other) {
        try { table = new Node[other.capacity_]; }
        catch (...) {
            other.~THashTable();
            throw std::bad_alloc();
        }
        capacity_ = other.capacity_;
        for (auto &i : other) {
            insert(i.key, i.value);
        }
        size_ = other.size();
    }

    /**
     * Constructor with a node array, size, and capacity.
     *
     * @param table Node array
     * @param size Size of the hash table
     * @param capacity Capacity of the hash table
     */
    THashTable(Node *table, size_t size, size_t capacity) : table(table), size_(size), capacity_(capacity) {}

    /**
     * Move constructor.
     * 
     * Constructs a new THashTable object by moving the contents of another THashTable object.
     * 
     * @param other The THashTable object to move from.
     */
    THashTable(THashTable &&other) : table(other.table), size_(other.size_), capacity_(other.capacity_) {
        other.table = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    /**
     * Destructor.
     * 
     * Releases the memory allocated for the hash table.
     */
    virtual ~THashTable() {
        delete[] table;
        table = nullptr;
    }

    /**
     * Returns an iterator pointing to the beginning of the hash table.
     * 
     * The iterator points to the first element in the hash table, or to the end of the hash table if it is empty.
     * 
     * @return An iterator pointing to the beginning of the hash table.
     */
    virtual Iterator begin() {
        for (size_t i = 0; i < capacity_; ++i) {
            if (table[i].isTaken()) {
                return Iterator(table + i);
            }
        }
        return end();
    }

    /**
     * Returns an iterator pointing to the end of the hash table.
     * 
     * The iterator points to a position one past the last element in the hash table.
     * 
     * @return An iterator pointing to the end of the hash table.
     */
    virtual Iterator end() {
        return Iterator(table + capacity_);
    }

    /**
     * Finds an element in the hash table with the given key.
     * 
     * If the key is found, the iterator points to the corresponding element. Otherwise, the iterator points to the end of the hash table.
     * 
     * @param key The key to search for.
     * @return An iterator pointing to the element with the given key, or to the end of the hash table if the key is not found.
     */
    virtual Iterator find(const T1 &key) {
        auto index = hash(key) % capacity_;
        while (table[index].key != key || !table[index].isTaken()) {
            index = table[index].getNext();
            if (index == (hash(key) % capacity_)) {
                return end();
            }
        }
        return Iterator(table + index);
    }

    /**
     * Inserts a new element into the hash table.
     * 
     * If the hash table is full, it is resized to accommodate the new element.
     * 
     * @param key The key of the new element.
     * @param value The value of the new element.
     */
    virtual void insert(const T1 &key, const T2 &value) {
        if (size_ == capacity_) {
            resize();
        }
        auto index = hash(key) % capacity_;
        auto prev_index = table[index].getPrev();
        auto next_index = index;
        while (table[index].isTaken()) {
            index = (index + 1) % capacity_;
        }
        if (index == (hash(key) % capacity_)) {
            prev_index = index;
        }
        auto is_last_ = index == capacity() - 1;
        table[index] = Node(key, value, true, prev_index, next_index, is_last_);
        ++size_;
    }

    /**
     * Removes an element from the hash table with the given key.
     * 
     * If the key is found, the element is removed and the size of the hash table is decreased.
     * 
     * @param key The key of the element to remove.
     */
    virtual void remove(const T1 &key) {
        auto hash_index = hash(key) % capacity_;
        auto element = find(key);
        if (element == end()) {
            throw std::out_of_range("Key not found");
        }
        if ((*element).key == table[hash_index].key) {
            auto next = table[hash_index].getNext();
            table[hash_index].key = table[next].key;
            table[hash_index].value = table[next].value;
            table[hash_index].setNext(table[next].getNext());
            table[next].setNotTaken();
            auto new_next = table[hash_index].getNext();
            table[new_next].setPrev(hash_index);
            if (table[hash_index].isLast()) {
                table[hash_index].setNotLast();
            }
        }
        else {
            auto new_next_ = table[(*element).getNext()].getNext();
            table[new_next_].setPrev((*element).getPrev());
            table[(*element).key].setNotTaken();
        }
        --size_;
    }

    /**
     * Checks if the hash table contains an element with the given key.
     * 
     * @param key The key to search for.
     * @return True if the key is found, false otherwise.
     */
    virtual bool contains(const T1 &key) {
        return find(key) != end();
    }

    /**
     * Returns the number of elements in the hash table.
     * 
     * @return The size of the hash table.
     */
    virtual size_t size() const {
        return size_;
    }

    /**
     * Returns the capacity of the hash table.
     * 
     * @return The capacity of the hash table.
     */
    virtual size_t capacity() const {
        return capacity_;
    }

    /**
     * Clears the hash table.
     * 
     * All elements are removed and the size and capacity of the hash table are reset to 0.
     */
    virtual void clear() {
        size_ = 0;
        capacity_ = 0;
        delete[] table;
        table = nullptr;
    }
private:
    /**
     * The table of nodes in the hash table.
     * 
     * Each node represents an element in the hash table, and contains a key, value, and pointers to the next and previous nodes.
     */
    Node *table = nullptr;

    /**
     * The capacity of the hash table.
     * 
     * The capacity is the maximum number of elements that the hash table can hold.
     */
    size_t capacity_ = 0;

    /**
     * The current size of the hash table.
     * 
     * The size is the number of elements currently stored in the hash table.
     */
    size_t size_ = 0;

    /**
     * Resizes the hash table to twice its current capacity.
     * 
     * All elements are reinserted into the new hash table.
     * 
     * This function is called when the hash table is full and a new element needs to be inserted.
     */
    void resize() {
        capacity_ *= 2;
        Node *new_table;
        try { new_table = new Node[capacity_]; }
        catch (...) { 
            delete[] table;
            throw std::bad_alloc(); 
        }
        auto *old_table = table;
        auto old_size = size_;
        table = new_table;
        size_ = 0;
        for (size_t i = 0; i < old_size; ++i) {
            insert(table[i].key, table[i].value);
        }
        for (size_t i = 0; i < size_; ++i) {
            if (!new_table[i].isTaken()) {
                new_table[i].setNext(i);
                new_table[i].setPrev(i);                
            }       
        }
        delete[] old_table;
    }
};

#endif //LAB2_LIB_HASH_TABLE_H
