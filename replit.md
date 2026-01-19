# DSA - Data Structures and Algorithms

## Overview
A C++ collection of Data Structures and Algorithms implementations for learning and reference. Originally a Visual Studio project, adapted for Replit.

## Project Structure
- `main.cpp` - Demo program showcasing binary search and merge sort
- `Makefile` - Build configuration using clang++
- `DSA/` - Contains various DSA implementations organized by topic:
  - `Arrays/` - Array operations and 2D arrays
  - `DP/` - Dynamic programming problems
  - `Graph/` - Graph traversal algorithms
  - `LinkedList/` - Linked list operations (traversal, reversal, circular)
  - `PatternPrinting/` - Console pattern printing
  - `Queues/` - Queue implementations
  - `Recursion/` - Recursive algorithms and backtracking
  - `Searching/` - Binary and linear search
  - `Sorting/` - Merge sort and other sorting algorithms
  - `Stack/` - Stack implementations (array and STL)
  - `Strings/` - String algorithms (KMP, recursion)
  - `Trees/` - Binary tree operations and problems
  - `Tries/` - Trie data structure

## Build System
- Language: C++17
- Compiler: clang++
- Build command: `make`
- Run command: `./main`

## How to Run
Click "Run" to compile and execute the demo program. To run individual DSA examples, edit `main.cpp` or compile specific files with:
```bash
clang++ -std=c++17 -o program DSA/<folder>/<file>.cpp && ./program
```

## Recent Changes
- January 2026: Adapted for Replit environment with Makefile and demo main.cpp
