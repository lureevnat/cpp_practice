# `std::vector` — Operations, Explanations & Complexities

`std::vector<T>` is a **dynamic contiguous array**.

```cpp
std::vector<int> v = {10, 20, 30, 40, 50};
```

Conceptually, memory looks like:

```text
Address →   1000   1004   1008   1012   1016
             ↓      ↓      ↓      ↓      ↓
           [ 10 ] [ 20 ] [ 30 ] [ 40 ] [ 50 ]
             0      1      2      3      4
```

Because elements are contiguous, accessing an element by index is very fast.

---

## 1. Accessing Elements

### `operator[]`

```cpp
int x = v[2];
```

Returns the element at index `2`.

### Complexity: **O(1)**

The vector can calculate the address directly:

```text
address = beginning + index × sizeof(T)
```

It does not need to scan the vector.

```cpp
v[0]    // O(1)
v[1]    // O(1)
v[100]  // O(1)
```

### Important

`operator[]` does **not** perform bounds checking.

```cpp
v[1000];  // Undefined behavior if index is invalid
```

---

## 2. `at()`

```cpp
int x = v.at(2);
```

Similar to `operator[]`, but performs bounds checking.

```cpp
v.at(1000);
```

throws `std::out_of_range` if the index is invalid.

### Complexity: **O(1)**

The bounds check is constant time.

```text
if (index >= size)
    throw exception;

return element[index];
```

So:

```text
v[i]       → O(1)
v.at(i)    → O(1)
```

The difference is safety, not asymptotic complexity.

---

## 3. `front()`

```cpp
int x = v.front();
```

Returns the first element.

Conceptually equivalent to:

```cpp
v[0]
```

### Complexity: **O(1)**

The first element is always at the beginning of the vector.

---

## 4. `back()`

```cpp
int x = v.back();
```

Returns the last element.

Conceptually:

```cpp
v[v.size() - 1]
```

### Complexity: **O(1)**

The vector knows where its end is.

---

## 5. `data()`

```cpp
int* p = v.data();
```

Returns a pointer to the underlying contiguous array.

For:

```cpp
std::vector<int> v = {10, 20, 30};
```

roughly:

```text
v.data()
   ↓
[10][20][30]
```

### Complexity: **O(1)**

It simply returns the stored pointer.

---

## 6. `size()`

```cpp
size_t n = v.size();
```

Returns the number of elements.

### Complexity: **O(1)**

A vector does not count its elements every time. It maintains its size information.

---

## 7. `empty()`

```cpp
if (v.empty()) {
    // ...
}
```

Checks whether the vector contains zero elements.

### Complexity: **O(1)**

Conceptually:

```cpp
return v.size() == 0;
```

---

## 8. `capacity()`

```cpp
size_t c = v.capacity();
```

Returns the number of elements the vector can currently hold **without allocating new memory**.

For example:

```text
size     = 5
capacity = 8
```

means:

```text
[10][20][30][40][50][ ][ ][ ]
 ↑────── size ──────↑
 ↑──────── capacity ─────────↑
```

### Complexity: **O(1)**

The vector stores this information.

---

# Adding Elements

## 9. `push_back()`

```cpp
v.push_back(60);
```

Adds an element to the end.

### Usually: **O(1)**

If there is enough capacity:

```text
size = 5
capacity = 8

[10][20][30][40][50][ ][ ][ ]
```

Adding an element:

```text
[10][20][30][40][50][60][ ][ ]
```

does not require moving existing elements.

Therefore: **O(1)**.

### Why can it be O(n)?

Suppose:

```text
size = 8
capacity = 8
```

and we execute:

```cpp
v.push_back(90);
```

There is no free space. The vector must allocate a larger memory block and move/copy the existing elements:

```text
Old memory:

[10][20][30][40][50][60][70][80]

New memory:

[10][20][30][40][50][60][70][80][90]
```

Moving the existing elements takes **O(n)**.

Therefore:

```text
Best case       O(1)
Amortized       O(1)
Worst case      O(n)
```

### Why is `push_back()` amortized O(1)?

Although occasional insertions require O(n) reallocation, most insertions are O(1). Across a large sequence of insertions, the average cost per insertion is constant.

---

## 10. `emplace_back()`

```cpp
v.emplace_back(10);
```

Constructs an object directly at the end of the vector.

Example:

```cpp
std::vector<std::string> v;

v.emplace_back("hello");
```

### Complexity

**O(1) amortized**, **O(n) worst case**

The same vector reallocation rules apply as with `push_back()`.

The main difference between `emplace_back()` and `push_back()` is generally about **object construction**, not asymptotic complexity.

---

## 11. `pop_back()`

```cpp
v.pop_back();
```

Removes the last element.

```text
Before:

[10][20][30][40][50]

pop_back()

After:

[10][20][30][40]
```

No elements need to shift.

### Complexity: **O(1)**

For non-trivial objects, the destructor of the removed element runs. In typical complexity analysis this is treated as O(1), assuming element destruction is constant time.

---

## 12. `insert()`

Example:

```cpp
v.insert(v.begin() + 2, 99);
```

Before:

```text
[10][20][30][40][50]
          ↑
       position
```

After:

```text
[10][20][99][30][40][50]
```

Elements after the insertion point may need to move.

```text
30 → new position
40 → new position
50 → new position
```

### Complexity: **O(n)**

For normal DSA analysis:

```text
insert at beginning → O(n)
insert in middle     → O(n)
insert at end        → O(1) amortized
```

More generally, inserting `k` elements involves work proportional to the number of elements shifted plus the number inserted.

---

## 13. `emplace()`

```cpp
v.emplace(v.begin() + 2, 99);
```

Constructs an element at the specified position.

### Complexity: **O(n)**

Elements after the insertion position may need to be shifted.

`emplace()` can avoid an intermediate object construction in appropriate cases, but it does not make middle insertion O(1).

---

# Removing Elements

## 14. `erase()`

```cpp
v.erase(v.begin() + 2);
```

Suppose:

```text
[10][20][30][40][50]
          ↑
        erase
```

After:

```text
[10][20][40][50]
```

Elements after `30` must shift left:

```text
40 → position of 30
50 → position of 40
```

### Complexity: **O(n)**

More precisely, the work is proportional to the number of elements after the erased range.

---

## 15. Erasing the Last Element

```cpp
v.erase(v.end() - 1);
```

No shifting is necessary.

### Complexity: **O(1)**

For simply removing the final element, `pop_back()` is normally clearer.

---

## 16. `clear()`

```cpp
v.clear();
```

Removes all elements.

```text
Before:

[10][20][30][40][50]

After:

[]
```

The vector must destroy its elements.

### Complexity: **O(n)**

### Important

`clear()` normally makes:

```cpp
v.size() == 0
```

but does **not necessarily reduce `capacity()`**.

Example:

```text
Before:
size     = 100
capacity = 128

clear()

After:
size     = 0
capacity = 128
```

---

## 17. `resize()`

### Shrinking

```cpp
v.resize(3);
```

From:

```text
[10][20][30][40][50]
```

to:

```text
[10][20][30]
```

The removed elements are destroyed.

### Complexity

**O(number of elements removed)**.

Worst case: **O(n)**.

### Growing

```cpp
v.resize(10);
```

New elements are value-initialized.

### Complexity

**O(number of elements added)**.

Worst case: **O(n)**.

---

# Memory and Capacity

## 18. `reserve()`

```cpp
v.reserve(1000);
```

Requests enough capacity for at least 1000 elements.

Suppose:

```text
size = 100
capacity = 100
```

After:

```cpp
v.reserve(1000);
```

you might have:

```text
size = 100
capacity >= 1000
```

If reallocation is necessary, existing elements must be moved/copied.

### Complexity

If reallocation occurs:

**O(n)**

If the requested capacity is already available:

**O(1)**

### Why use `reserve()`?

If you know approximately how many elements will be inserted:

```cpp
std::vector<int> v;
v.reserve(1'000'000);

for (int i = 0; i < 1'000'000; ++i)
    v.push_back(i);
```

This can avoid repeated reallocations.

Without `reserve()`, capacity may grow repeatedly:

```text
1
2
4
8
16
32
...
```

Each reallocation may require moving existing elements.

---

## 19. `shrink_to_fit()`

```cpp
v.shrink_to_fit();
```

Requests that the vector reduce its capacity to something closer to its size.

Example:

```text
Before:

size     = 10
capacity = 1000
```

After a successful reduction:

```text
size     = 10
capacity ≈ 10
```

### Complexity

Potentially **O(n)**.

### Important

`shrink_to_fit()` is a **non-binding request**. The implementation is not required to reduce the capacity.

---

## 20. `swap()`

```cpp
v1.swap(v2);
```

Example:

```text
v1 = [1, 2, 3]
v2 = [10, 20, 30, 40, 50]
```

After:

```cpp
v1.swap(v2);
```

```text
v1 = [10, 20, 30, 40, 50]
v2 = [1, 2, 3]
```

Vectors generally exchange their internal pointers/metadata rather than copying every element.

### Complexity: **O(1)**

---

## 21. `assign()`

```cpp
v.assign(5, 100);
```

Produces:

```text
[100][100][100][100][100]
```

### Complexity: **O(n)**

Elements need to be created or assigned.

You can also assign from a range:

```cpp
v.assign(other.begin(), other.end());
```

If `other` contains `n` elements:

**O(n)**.

---

# Construction

## 22. Constructing with `n` Elements

```cpp
std::vector<int> v(1000);
```

Creates 1000 elements.

### Complexity: **O(n)**

Each element needs to be initialized.

---

## 23. Range Construction

```cpp
std::vector<int> v(other.begin(), other.end());
```

If `other` contains `n` elements:

### Complexity: **O(n)**

Each element needs to be copied/moved into the new vector.

---

# Iterators

## 24. `begin()`, `end()`, `rbegin()`, `rend()`

```cpp
auto it = v.begin();
auto end = v.end();

auto rit = v.rbegin();
auto rend = v.rend();
```

### Complexity: **O(1)**

Vector iterators are random-access iterators and are typically implemented similarly to pointers.

---

## 25. Iterator Arithmetic

Vector iterators support:

```cpp
it + 5
it - 3
it += 5
it -= 3
it[5]
it1 - it2
```

### Complexity: **O(1)**

For example:

```cpp
auto it = v.begin();
it += 500000;
```

does not walk through 500,000 elements.

It calculates the address directly.

This is possible because `std::vector` provides **random access iterators**.

---

# Searching and Algorithms

These are not member functions of `vector`, but they are commonly used with it.

## 26. `std::find`

```cpp
auto it = std::find(v.begin(), v.end(), 50);
```

Searches sequentially:

```text
[10][20][30][40][50]
 ↑   ↑   ↑   ↑   ↑
```

In the worst case, every element must be checked.

### Complexity: **O(n)**

---

## 27. `std::count`

```cpp
int n = std::count(v.begin(), v.end(), 50);
```

Must inspect every element to know how many matches exist.

### Complexity: **O(n)**

---

## 28. `std::binary_search`

```cpp
std::binary_search(v.begin(), v.end(), 50);
```

Requires the vector to be sorted.

Example:

```text
[10 20 30 40 50 60 70 80]
             ↑
           middle
```

It repeatedly halves the search range.

### Complexity: **O(log n)**

---

## 29. `std::lower_bound`

```cpp
auto it = std::lower_bound(v.begin(), v.end(), x);
```

Finds the first position where `x` can be inserted while maintaining sorted order.

Example:

```text
v = [10 20 30 30 40 50]

lower_bound(30)
          ↓
[10 20 30 30 40 50]
       ↑
```

### Complexity: **O(log n)**

for vector/random-access iterators.

---

## 30. `std::upper_bound`

```cpp
auto it = std::upper_bound(v.begin(), v.end(), 30);
```

Finds the first element **greater than** `30`.

```text
[10 20 30 30 40 50]
             ↑
```

### Complexity: **O(log n)**

---

# Sorting and Other Algorithms

## 31. `std::sort`

```cpp
std::sort(v.begin(), v.end());
```

Sorts the vector.

### Complexity: **O(n log n)**

The standard implementation is typically based on introsort, combining ideas from quicksort, heapsort, and insertion sort.

---

## 32. `std::reverse`

```cpp
std::reverse(v.begin(), v.end());
```

Example:

```text
[1 2 3 4 5]

↓

[5 4 3 2 1]
```

### Complexity: **O(n)**

---

## 33. `std::min_element`

```cpp
auto it = std::min_element(v.begin(), v.end());
```

Must inspect the elements to determine the minimum.

### Complexity: **O(n)**

---

## 34. `std::max_element`

```cpp
auto it = std::max_element(v.begin(), v.end());
```

### Complexity: **O(n)**

---

## 35. `std::accumulate`

```cpp
int sum = std::accumulate(v.begin(), v.end(), 0);
```

Conceptually:

```cpp
sum = 0;

for (auto x : v)
    sum += x;
```

### Complexity: **O(n)**

---

## 36. `std::copy`

```cpp
std::copy(v.begin(), v.end(), destination);
```

If there are `n` elements:

### Complexity: **O(n)**

Every element needs to be copied.

---

## 37. `std::move`

```cpp
std::move(v.begin(), v.end(), destination);
```

For `n` elements:

### Complexity: **O(n)**

The algorithm still visits every element.

---

# Complete Complexity Cheat Sheet

| Operation | Complexity |
|---|---:|
| `v[i]` | **O(1)** |
| `v.at(i)` | **O(1)** |
| `v.front()` | **O(1)** |
| `v.back()` | **O(1)** |
| `v.data()` | **O(1)** |
| `v.size()` | **O(1)** |
| `v.empty()` | **O(1)** |
| `v.capacity()` | **O(1)** |
| `v.begin()` | **O(1)** |
| `v.end()` | **O(1)** |
| Iterator `+/-` | **O(1)** |
| `push_back()` | **O(1) amortized** |
| `emplace_back()` | **O(1) amortized** |
| `pop_back()` | **O(1)** |
| `insert()` at end | **O(1) amortized** |
| `insert()` beginning/middle | **O(n)** |
| `emplace()` beginning/middle | **O(n)** |
| `erase()` beginning/middle | **O(n)** |
| `erase()` last | **O(1)** |
| `clear()` | **O(n)** |
| `resize()` | **O(n)** worst case |
| `reserve()` | **O(n)** if reallocating |
| `shrink_to_fit()` | **O(n)** potentially |
| `swap()` | **O(1)** |
| `assign()` | **O(n)** |
| `find()` | **O(n)** |
| `count()` | **O(n)** |
| `binary_search()` | **O(log n)** |
| `lower_bound()` | **O(log n)** |
| `upper_bound()` | **O(log n)** |
| `sort()` | **O(n log n)** |
| `reverse()` | **O(n)** |
| `min_element()` | **O(n)** |
| `max_element()` | **O(n)** |
| `accumulate()` | **O(n)** |

# The Mental Model

Think of `vector` as:

```text
             RANDOM ACCESS
                  ↓
        [10][20][30][40][50]
         ↑                ↑
       begin             end

       contiguous memory
```

Therefore:

### 1. Access → O(1)

```cpp
v[i]
```

The address can be calculated directly.

### 2. Add/remove at the end → O(1)

```cpp
push_back()
pop_back()
```

Nothing after the position needs to move.

`push_back()` is **O(1) amortized** because occasional reallocations make individual operations O(n).

### 3. Add/remove in the middle → O(n)

```cpp
insert()
erase()
```

Elements may have to be shifted.

### 4. Search → O(n)

```cpp
find()
```

An unsorted vector may require checking every element.

### 5. Sorted search → O(log n)

```cpp
binary_search()
lower_bound()
upper_bound()
```

Binary search repeatedly halves the search range.

### 6. Sorting → O(n log n)

```cpp
sort()
```

Sorting requires substantially more work than direct access or insertion at the end.

---

# Most Important Operations to Memorize

For DSA and C++ interviews, remember this core table:

| Operation | Complexity |
|---|---:|
| Random access | **O(1)** |
| Search | **O(n)** |
| Binary search (sorted) | **O(log n)** |
| `push_back()` | **O(1) amortized** |
| `pop_back()` | **O(1)** |
| Insert at beginning | **O(n)** |
| Insert in middle | **O(n)** |
| Insert at end | **O(1) amortized** |
| Erase at beginning | **O(n)** |
| Erase in middle | **O(n)** |
| Erase at end | **O(1)** |
| `size()` | **O(1)** |
| `sort()` | **O(n log n)** |

The key reason behind almost all of these complexities is **contiguous storage**: vectors provide extremely fast random access, but inserting or erasing away from the end can require shifting many elements.
