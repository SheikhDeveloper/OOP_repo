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
     * Node class for the hash table.
     */
    class Node {
    public:
        /**
         * Key of the node.
         */
        T1 key_;
        /**
         * Value of the node.
         */
        T2 value_;
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
        Node(const T1 &key, const T2 &value, bool is_taken, bool is_last, size_t prev, size_t next) : key_(key), value_(value), is_taken_(is_taken), is_last_(is_last), prev_(prev), next_(next) {}

        /**
         * Default destructor of the node.
         */
        ~Node() = default;

        /**
         * Checks if the node is taken.
         */
        bool isTaken() const {
            return is_taken_;
        }

        /**
         * Checks if the node is the last node.
         */
        bool isLast() const {
            return is_last_;
        }

        /**
         * Returns the previous node with the same hash index.
         */
        size_t getPrev() const {
            return prev_;
        }

        /**
         * Returns the next node with the same hash index.
         */
        size_t getNext() const {
            return next_;
        }

        /**
         * Sets the node as taken.
         */
        void setTaken() {
            is_taken_ = true;
        }

        /**
         * Sets the node as not taken.
         */
        void setNotTaken() {
            is_taken_ = false;
        }

        /**
         * Sets the node as the last node.
         */
        void setLast() {
            is_last_ = true;
        }

        /**
         * Sets the node as not the last node.
         */
        void setNotLast() {
            is_last_ = false;
        }

        /**
         * Sets the next node with the same hash index.
         */
        void setNext(size_t next) {
            next_ = next;
        }

        /**
         * Sets the previous node with the same hash index.
         */
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
            if ((*ptr).isLast()) {
                ++ptr;
                return *this;
            }
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
        return (*result).value_;
    }


    /**
     * Assigns the contents of another hash table to this hash table.
     *
     * @param other Hash table to assign from
     *
     * @return A reference to this object
     */
    THashTable &operator=(const THashTable &other) {
        clear();
        try { table_ = new Node[other.capacity_]; }
        catch (std::exception &e) {
            throw std::bad_alloc();
        }
        capacity_ = other.capacity_;
        size_ = 0;
        auto other_not_const = const_cast<THashTable &>(other);
        for (auto &i : other_not_const) {
            insert(i.key_, i.value_);            
        }        
        return *this;
    }

    /**
     * Move assignment operator.
     *
     * Assigns the contents of another THashTable object to this object, transferring ownership.
     *
     * @param other The THashTable object to move from.
     * @return A reference to this object.
     *
     * @note This function leaves the other object in a valid but unspecified state.
     */
    THashTable &operator=(THashTable &&other) {
        if (this != &other) {
            clear();
            table_ = other.table_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            other.table_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
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
        table_ = new Node[capacity];
        capacity_ = capacity;
        for (size_t i = 0; i < capacity_; ++i) {
            table_[i].setNext(i);
            table_[i].setPrev(i);
        }
    }

    /**
     * Copy constructor.
     *
     * @param other Hash table to copy from
     */
    THashTable(THashTable &other) {
        try { table_ = new Node[other.capacity_]; }
        catch (std::exception &e) {
            throw std::bad_alloc();
        }
        capacity_ = other.capacity_;
        for (auto &i : other) {
            insert(i.key_, i.value_);
        }
        size_ = other.size();
    }

    /**
     * Move constructor.
     * 
     * Constructs a new THashTable object by moving the contents of another THashTable object.
     * 
     * @param other The THashTable object to move from.
     */
    THashTable(THashTable &&other) : table_(other.table_), capacity_(other.capacity_), size_(other.size_) {
        other.table_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    /**
     * Destructor.
     * 
     * Releases the memory allocated for the hash table.
     */
    virtual ~THashTable() {
        clear();
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
            if (table_[i].isTaken()) {
                return Iterator(table_ + i);
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
        return Iterator(table_ + capacity_);
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
        if (size_ == 0) {
            return end();
        }
        auto index = hash(key) % capacity_;
        while (table_[index].key_ != key || !table_[index].isTaken()) {
            index = table_[index].getNext();
            if (index == (hash(key) % capacity_)) {
                return end();
            }
        }
        return Iterator(table_ + index);
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
        auto hash_index = index;
        auto prev_index = table_[index].getPrev();
        auto next_index = index;
        while (table_[index].isTaken()) {
            index = (index + 1) % capacity_;
        }
        if (index == (hash(key) % capacity_)) {
            prev_index = index;
        }
        auto is_last_ = (index == capacity() - 1) ? true : false;
        table_[index] = Node(key, value, true, is_last_, prev_index, next_index);
        if (table_[hash_index].getPrev() != hash_index) {
            auto pre_hash_index = table_[hash_index].getPrev();
            table_[pre_hash_index].setNext(index);
        }
        table_[hash_index].setPrev(index);
        if (table_[hash_index].getNext() == hash_index) {
            table_[hash_index].setNext(index);
        }
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
        if ((*element).key_ == table_[hash_index].key_) {
            auto next = table_[hash_index].getNext();
            table_[hash_index].key_ = table_[next].key_;
            table_[hash_index].value_ = table_[next].value_;
            table_[hash_index].setNext(table_[next].getNext());
            table_[next].setNotTaken();
            auto new_next = table_[hash_index].getNext();
            table_[new_next].setPrev(hash_index);
        }
        else {
            auto next = (*element).getNext();
            table_[next].setPrev((*element).getPrev());
            (*element).setNotTaken();
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
        delete[] table_;
        table_ = nullptr;
    }
private:
    /**
     * The table of nodes in the hash table.
     * 
     * Each node represents an element in the hash table, and contains a key, value, and pointers to the next and previous nodes.
     */
    Node *table_ = nullptr;

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
        auto old_capacity = capacity_;
        if (capacity_ == 0)
            capacity_ = 1;
        else capacity_ *= 2;
        Node *new_table;
        try { new_table = new Node[capacity_]; }
        catch (...) { 
            delete[] table_;
            throw std::bad_alloc(); 
        }
        auto *old_table = table_;
        table_ = new_table;
        size_ = 0;
        for (size_t i = 0; i < old_capacity; ++i) {
            insert(old_table[i].key_, old_table[i].value_);
        }
        for (size_t i = 0; i < capacity_; ++i) {
            if (!table_[i].isTaken()) {
                table_[i].setNext(i);
                table_[i].setPrev(i);                
            }       
        }
        table_[capacity_ - 1].setLast();
        delete[] old_table;
    }
};

#endif //LAB2_LIB_HASH_TABLE_H
