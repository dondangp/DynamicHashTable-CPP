# Dynamic Hash Table in C++

## Overview
This repository contains a C++ implementation of a hash table that utilizes a custom doubly linked list for handling collisions through chaining. The implementation features dynamic resizing capabilities—doubling the size when full and halving when a quarter of the capacity is unused. The hash function combines both multiplication and division methods to distribute keys evenly across the array.

## Features
- **Custom Doubly Linked List**: Uses a manually implemented doubly linked list to manage collisions, providing append, find, and remove functionalities.
- **Dynamic Resizing**: Automatically adjusts the size of the hash table based on the current load, enhancing performance and space efficiency.
- **Combination Hash Function**: Implements a hash function that uses both multiplication and division methods to optimize key distribution.

## Getting Started

### Prerequisites
To compile and run this implementation, ensure you have a C++ compiler installed on your system. This code is standard C++ and should compile with any compliant C++ compiler like GCC or Clang.

### Compilation and Execution
To compile the `HashTable.cpp` file, you can use the following command if using GCC:

```bash
g++ -o HashTable HashTable.cpp
./HashTable
