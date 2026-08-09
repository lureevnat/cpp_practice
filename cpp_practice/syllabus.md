# C++ Course Syllabus

## 1. C++ Fundamentals

- C vs C++
- Compilation and linking
- `main()`
- Variables and data types
- `const`
- Literals
- Type aliases
- Scope and lifetime
- `sizeof`
- Stack vs heap vs static storage
- Comments and namespaces

## 2. Initialization & Type Conversions

- Default initialization
- Value initialization
- Copy initialization
- Direct initialization
- Direct-list initialization
- Copy-list initialization
- Aggregate initialization
- Narrowing vs non-narrowing conversions
- Implicit conversions
- Explicit conversions
- `static_cast`
- `const_cast`
- `reinterpret_cast`
- `dynamic_cast`
- `auto`
- `decltype`

Example:

```cpp
int a;
int b = 10;
int c(10);
int d{10};
int e = {10};
```

## 3. Operators & Expressions

- Arithmetic operators
- Relational operators
- Logical operators
- Bitwise operators
- Increment/decrement
- Assignment operators
- Operator precedence
- Short-circuit evaluation
- Ternary operator
- Comma operator

## 4. Control Flow

- `if / else`
- `switch`
- `for`
- `while`
- `do while`
- `break`
- `continue`
- `goto`
- Range-based `for`

## 5. Functions

- Function declaration/definition
- Parameters
- Return values
- Pass-by-value
- Pass-by-reference
- Pointers as parameters
- `const` parameters
- Default arguments
- Function overloading
- Inline functions
- Recursion
- Function pointers
- Lambdas

## 6. Pointers & References

- Addresses
- Pointers
- Dereferencing
- Pointer arithmetic
- `nullptr`
- References
- `const` pointers
- Pointer to `const`
- `const` pointer to `const`
- Pointer-to-pointer
- Arrays and pointers
- Function pointers
- References vs pointers
- Dangling pointers
- Null pointers
- Ownership

Example:

```cpp
int x = 10;

int* p = &x;
int& r = x;
```

# Object-Oriented C++

## 7. Classes & Objects

- Class definition
- Objects
- Data members
- Member functions
- Access specifiers
- `public`
- `private`
- `protected`
- `this`
- Constructors
- Destructors
- Constructor initialization lists
- `explicit`
- `static` members

Example:

```cpp
class MyClass {
public:
    MyClass(int x) : x_(x) {}

private:
    int x_;
};
```

## 8. Inheritance

- Base/derived classes
- Public inheritance
- Protected inheritance
- Private inheritance
- Constructor/destructor order
- Function overriding
- `virtual`
- Pure virtual functions
- Abstract classes
- Virtual destructors
- Multiple inheritance
- Diamond problem

## 9. Polymorphism

- Compile-time polymorphism
- Runtime polymorphism
- Virtual functions
- Vtables
- Vtable pointers
- Dynamic dispatch
- `override`
- `final`
- Object slicing

## 10. Special Member Functions

- Default constructor
- Destructor
- Copy constructor
- Copy assignment
- Move constructor
- Move assignment
- Rule of 0
- Rule of 3
- Rule of 5

Example:

```cpp
class A {
public:
    A();
    ~A();

    A(const A&);
    A& operator=(const A&);

    A(A&&);
    A& operator=(A&&);
};
```

# STL

## 11. Standard Containers

- `std::array`
- `std::vector`
- `std::deque`
- `std::list`
- `std::forward_list`
- `std::stack`
- `std::queue`
- `std::priority_queue`
- `std::set`
- `std::multiset`
- `std::map`
- `std::multimap`
- `std::unordered_set`
- `std::unordered_map`

Understand:

- Memory layout
- Complexity
- Iterator invalidation
- When to use each container

## 12. Iterators

- Iterator basics
- `begin/end`
- `cbegin/cend`
- Reverse iterators
- Iterator categories
- Iterator invalidation
- Range-based loops

## 13. STL Algorithms

- `sort`
- `find`
- `find_if`
- `count`
- `count_if`
- `transform`
- `copy`
- `remove`
- `remove_if`
- `lower_bound`
- `upper_bound`
- `binary_search`
- `accumulate`
- `min_element`
- `max_element`

Understand the **algorithm + iterator + container** model.

# Modern C++

## 14. Smart Pointers

- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr`
- Ownership
- Reference counting
- Cyclic references
- `make_unique`
- `make_shared`
- Custom deleters

## 15. Move Semantics

- lvalues
- rvalues
- lvalue references
- rvalue references
- `std::move`
- Move constructor
- Move assignment
- Perfect forwarding
- `std::forward`

## 16. Templates

- Function templates
- Class templates
- Template parameters
- Template specialization
- Partial specialization
- Variadic templates
- Parameter packs
- Fold expressions
- Type traits
- SFINAE
- Concepts

## 17. Lambdas & Functional C++

- Lambda syntax
- Capture by value
- Capture by reference
- Generic lambdas
- Mutable lambdas
- `std::function`
- Function objects
- `bind`
- `invoke`

## 18. Operator Overloading

- Arithmetic operators
- Comparison operators
- Assignment operators
- Stream operators

Especially:

```cpp
std::ostream& operator<<(std::ostream& os,
                         const MyClass& obj);
```

## 19. Exceptions

- `try`
- `catch`
- `throw`
- Standard exceptions
- Custom exceptions
- Exception safety
- RAII
- `noexcept`

# Advanced C++

## 20. Memory Management

- Stack
- Heap
- Static storage
- Alignment
- Padding
- Object lifetime
- Placement `new`
- Allocators
- Memory pools
- Custom allocators
- Cache locality
- False sharing

## 21. Concurrency

- Threads
- `std::thread`
- `std::mutex`
- `std::lock_guard`
- `std::unique_lock`
- `std::condition_variable`
- Atomics
- Memory ordering
- Futures
- Promises
- `async`
- Thread pools

## 22. Advanced Type System

- `const` correctness
- `constexpr`
- `consteval`
- `constinit`
- Type deduction
- `decltype`
- `std::is_same`
- Type traits
- `std::enable_if`
- Concepts
- `requires`

## 23. File & Stream I/O

- `iostream`
- `istream`
- `ostream`
- `fstream`
- `ifstream`
- `ofstream`
- String streams
- Stream states
- `good()`
- `fail()`
- `bad()`
- `eof()`
- Binary files
- Serialization basics

## 24. Preprocessor & Compilation

- `#include`
- `#define`
- Macros
- Include guards
- `#pragma once`
- Conditional compilation
- Translation units
- Header files
- ODR
- Linkage
- Static libraries
- Shared libraries

# Systems-Level C++

## 25. Compilation Pipeline

Understand:

```text
.cpp
  ↓
Preprocessor
  ↓
Compiler
  ↓
Assembly
  ↓
Assembler
  ↓
Object file
  ↓
Linker
  ↓
Executable
```

Learn:

- `gcc/g++`
- `clang/clang++`
- `-E`
- `-S`
- `-c`
- Linking
- Symbol tables
- Static linking
- Dynamic linking
- ABI

## 26. Debugging & Profiling

- `gdb`
- `lldb`
- Breakpoints
- Watchpoints
- Stack traces
- Core dumps
- Sanitizers
  - ASan
  - UBSan
  - TSan
- Valgrind
- `perf`
- Profiling
- Assembly inspection

## 27. Build Systems

- Make
- CMake
- Targets
- Libraries
- Dependencies
- `find_package`
- CMake toolchains
- Cross compilation

## 28. Data Structures & Algorithms in C++

- Complexity analysis
- Arrays
- Linked lists
- Stacks
- Queues
- Trees
- BST
- Heaps
- Hash tables
- Graphs
- BFS
- DFS
- Topological sort
- Dijkstra
- Union-Find
- Sorting
- Searching

# Expert-Level Topics

## 29. C++ Object Model

- Object lifetime
- Storage duration
- Object representation
- Alignment
- Padding
- Strict aliasing
- Effective types
- Pointer provenance
- Undefined behavior
- Lifetime extension
- Temporary objects
- Copy elision
- RVO/NRVO

## 30. Templates Deep Dive

- Two-phase lookup
- Dependent names
- SFINAE
- Detection idiom
- Concepts
- CRTP
- Template metaprogramming
- Compile-time computation

## 31. Performance

- Cache hierarchy
- Cache locality
- Branch prediction
- SIMD
- Memory bandwidth
- Allocation overhead
- Zero-copy
- Data-oriented design
- Lock-free programming
- Benchmarking

# Recommended Learning Order

For a strong C++ foundation:

```text
1. Fundamentals
       ↓
2. Initialization + conversions
       ↓
3. Pointers + references
       ↓
4. Classes + constructors/destructors
       ↓
5. Copy/move semantics
       ↓
6. STL
       ↓
7. Smart pointers
       ↓
8. Templates
       ↓
9. Operator overloading
       ↓
10. Streams + file I/O
       ↓
11. Exceptions + RAII
       ↓
12. Concurrency
       ↓
13. Memory model + object lifetime
       ↓
14. Compilation + linking
       ↓
15. Performance + assembly
```

# Priority for ML Systems / Low-Level C++

## Must Master

- Pointers
- References
- Classes
- RAII
- Copy/move semantics
- STL
- Smart pointers
- Templates
- Memory management
- Concurrency
- Compilation/linking
- Debugging

## Important

- Operator overloading
- Streams
- Exceptions
- Lambdas
- Type traits
- Concepts
- CMake

## Advanced

- C++ object model
- Allocators
- Atomics and memory ordering
- Lock-free programming
- ABI
- Cache/performance optimization
- Template metaprogramming
