# Lecture 7: Mar 2 2020

## Iterators

- But wait, how do we actually use a `list` besides accessing the front and back?

[`iterator1.cpp`](iterator1.cpp)

- Iterators are objects that denote an element from a sequence of elements.
- Containers all have a type member `::iterator` (and `::const_iterator`) for the type of its iterator.
- All containers have the `begin()` and `end()` (and `cbegin()` and `cend()` for const iterators) member functions to expose iterators to the beginning of the sequence and _one past the end_ of its sequence, respectively.
  - This is what the range based for loop (`for (int i : l)`) uses.
- To use iterators, dereference them using `*` or `->`. This doesn't mean iterators are pointers (though sometimes they are!).

[`iterator2.cpp`](iterator2.cpp)

- There is a hierarchy of iterator types, though iterators don't use a class hierarchy.
  - They use template arguments instead (next lecture) for performance.
- Here is a simplified description of the hierarchy:
  - All iterators can increment (`++`) through its sequence, be compared for equality (`==`, `!=`), and access its element of the sequence (`*`, `->`). If they are not `const` iterators, they can also be assigned to (`*it = ...`). Iterators that can _only_ do this are _forward iterators_.
    - e.g. `forward_list`
  - Bidirectional iterators can also decrement (`--`)
    - e.g. `list`
  - Random access iterators can go forwards and backwards any number of steps in constant time (`+`, `-`, `+=`, `-=`), and can be compared for inequality (`<`, `<=`, `>`, `>=`).
    - e.g. `vector`, `deque`
- Note that pointers are valid random access iterators (which also means they are valid instances of all the possible types of iterators).
- Note that also some of these operations can be simulated.
  - e.g. `advance(it, n)` in `<iterator>` just performs `++` on `it` `n` times.
    - Note that random access iterators can do this in constant time, while forward iterators will need linear time.
  - `distance(first, last)` returns the number of `++` required to get from `first` to `last`. If the iterators are not random access iterators, is undefined behavior if `last` is not reachable from `first`.

[`iterator3.cpp`](iterator3.cpp)

- All sequence containers provide `insert`, which inserts before an iterator.
- Iterators can be _invalidated_ when the container changes. This depends on the container.
- See [chart](https://en.cppreference.com/w/cpp/container) for a summary of the invalidation rules

[`iterator4.cpp`](iterator4.cpp)

- All sequence containers provide `erase` as well, which deletes the element at an iterator.
- `array` iterators never get invalidated, since the size cannot change.

### Stream Iterators

[`ostream.cpp`](ostream.cpp)

- Iterators are elements of _sequences_, not containers.
- Iterators can be made from streams as well.
- `ostream_iterator` can write to an `ostream` with the same interface as a container.
  - `ostream_iterator` cannot be read from. What I said earlier about all iterators having `*` and `->` was a simplication. There are _input_ and _output_ iterators, and `ostream_iterator`s are output iterators only.

[`istream.cpp`](istream.cpp)

- Each time an `istream_iterator` is incremented, it will read from its stream.
- When it is dereferenced, it will return the value last read.
- The default-constructed `istream_iterator` represents the end-of-stream iterator.

## Associative containers

- Containers that store a collection of key-value pairs (or something similar), which are not ordered by the user.

### First: `pair`

[`pair.cpp`](pair.cpp)

- Combines two objects of any type.
- In `<utility>`.
- Use `make_pair` to avoid typing out the types.
- Access the elements using `.first` and `.second` (note these are member _objects_, not member _functions_).
- Generalized by `tuple`.
- One possible implementation for an associative container is just a sequence container of `pair`s.

### `map`

[`map1.cpp`](map1.cpp)

- Typically implemented using a balanced BST like a red-black tree.
- `[]` returns a reference to the value corresponding to a key, if the key exists in the map. If the key doesn't exist in the map, it will be created.
- Other familiar member functions are also available:
  - `at` accesses a key's value. If the key doesn't exist, an exception is thrown.
  - `empty`, `size`, `clear`, `erase`.
  - `insert` and `emplace` are just like the functions on sequential containers, except they take a `pair` (no iterator required, since we don't need to manage the order ourselves).
- Iterating through the container will always go in sorted order.

[`map2.cpp`](map2.cpp)

- If your key is a custom class, you'll need to specify an ordering to use.
  - By default `map` uses `<`.
  - You can customize this by passing in a comparison _function object_ (more on this later) as a template argument.
    - The standard library has a few built in: `less<Key>`, which uses `operator<` for your class (if your class is named `Key`), is the default.
    - Others include `greater<Key>`, `less_equal<Key>`, and `greater_equal<Key>`.
- `map` doesn't use `operator==` to check for equality; we _only_ require an ordering.
  - If `!(a < b) && !(b < a)` then `less` considers `a` and `b` equivalent.

### `unordered_map`

[`unordered_map.cpp`](unordered_map.cpp)

- `map` uses a BST, with logarithmic complexity for its operations.
- Hash tables can do better, and that's what `unordered_map` is.
  - Amortized constant time complexity of its operations.
- Otherwise, `unordered_map` has basically the same interface as `map`.
- What should we do for custom key types?

### `hash`

- Other languages have hash codes built in to the language.
  - This requires a common base class.
  - But not everything in C++ is an object!
  - Also a virtual call may be required if we use a hash code method. This forced overhead is really not in the spirit of C++.
- This also uses a comparison object (so we'll talk about it in a later lecture).
- `unordered_map` also needs `operator==`, to deal with hash collisions.

### `set` and `unordered_set`

- These containers are basically the `map` and `unordered_map` containers, but without a value attached to the keys.

### `multi` variants

- There are also the `multimap`, `unordered_multimap`, `multiset`, and `unordered_multiset` classes for associative containers that can have multiple copies of a key.
- These containers can return a sequence of results (a start and end iterator).

## Some miscellaneous material

### `static`
  1. `static` local variables are basically global variables. They are initialized the first time they are used, but their values persist after the local scope ends.
  2. `static` class members are basically global functions/variables
	 - `static` member functions are basically a free (global) function in the class.
	 - `static` member variables are shared by all instances of the class.
	   - Note that you should still _define_ these in the `.cpp`
  3. `static` global variables and functions are only accessible in the file they are defined in. This is more of a C thing, and if you want this in C++ it is more idiomatic to use an _anonymous namespace_: `namespace { local functions and global variables... } rest of file`
