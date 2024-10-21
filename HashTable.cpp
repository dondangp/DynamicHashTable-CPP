#include <iostream>
#include <cmath>
#include <functional>

// Node structure for doubly linked list
struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

// Doubly linked list class
class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Add node to the end of the list
    void append(int key, int value) {
        Node* newNode = new Node(key, value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Remove node from the list
    void remove(Node* node) {
        if (!node) return;
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        delete node;
    }

    // Find a node with given key
    Node* find(int key) {
        Node* current = head;
        while (current) {
            if (current->key == key) return current;
            current = current->next;
        }
        return nullptr;
    }

    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }
};

// Hash table class
class HashTable {
    DoublyLinkedList* table;
    int capacity;
    int size;
    std::function<int(int, int)> hashFunction;  // Hash function as a std::function

public:
    HashTable(int cap = 8, std::function<int(int, int)> func = nullptr) : capacity(cap), size(0) {
        table = new DoublyLinkedList[capacity];
        if (func) {
            hashFunction = func;
        } else {
            // Default hash function if none provided
            hashFunction = [this](int key, int cap) {
                float A = 0.6180339887; // Fractional part of the golden ratio
                int hash1 = std::floor(cap * (key * A - std::floor(key * A)));
                int hash2 = key % cap;
                return (hash1 + hash2) % cap;
            };
        }
    }

    // Resize the hash table
    void resize(int new_capacity) {
        DoublyLinkedList* new_table = new DoublyLinkedList[new_capacity];
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i].head;
            while (current) {
                int new_index = hashFunction(current->key, new_capacity);
                new_table[new_index].append(current->key, current->value);
                current = current->next;
            }
        }
        delete[] table;
        table = new_table;
        capacity = new_capacity;
    }

    // Insert key-value pair
    void insert(int key, int value) {
        int index = hashFunction(key, capacity);
        Node* node = table[index].find(key);
        if (node) {
            node->value = value; // Update existing key
        } else {
            if (size == capacity) {
                resize(capacity * 2); // Double size
                index = hashFunction(key, capacity); // Re-hash the key
            }
            table[index].append(key, value);
            size++;
        }
    }

    // Delete key
    void remove(int key) {
        int index = hashFunction(key, capacity);
        Node* node = table[index].find(key);
        if (node) {
            table[index].remove(node);
            size--;
            if (size <= capacity / 4) {
                resize(capacity / 2); // Half size
            }
        }
    }

    // Get value by key
    int get(int key) {
        int index = hashFunction(key, capacity);
        Node* node = table[index].find(key);
        if (node) {
            return node->value;
        }
        return -1; // Key not found
    }

    ~HashTable() {
        delete[] table;
    }
};

int main() {
    HashTable ht;

    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(3, 30);

    std::cout << "Value at key 3: " << ht.get(3) << std::endl; // Output should be 30

    ht.remove(2);

    std::cout << "Value at key 2: " << ht.get(2) << std::endl; // Output should be -1 (not found)

    return 0;
}
