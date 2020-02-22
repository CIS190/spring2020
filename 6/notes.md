# Lecture 6: Feb 24 2020

## Exception examples

[`exception.cpp`](exception.cpp)

- More concrete example about exceptions.
- Using a `finally` construct as in other languages would require us to have one for every object that must be cleaned up, whenever there is any risk of exceptions.
  - RAII allows us to avoid writing this cleanup code everywhere, and instead just once in the destructor.

## Throwing constructors

[`ctor1.cpp`](ctor1.cpp)

- If something goes wrong in a constructor, you should throw an exception, since there is no return value.
- Note that if a constructor exits by a throw, the destructor is _not_ called.
  - Destructors are only called for objects that were successfully constructed.
- To catch exceptions thrown by the initializer list, use a _function try block_ which catches exceptions from the function body and the initializer list.
  - The catch clause(s) of a function try block _must_ throw an exception. If you don't throw one, it will rethrow automatically.
  - You can also use function try blocks for regular functions, but they are really only useful for constructors. You can read more about it [here](https://en.cppreference.com/w/cpp/language/function-try-block)
- The code above doesn't really work that well. We know it's `q` that's throwing, and that allocating `p` succeeds, but what if we don't? We have to delete the one(s) that were allocated successfully. Which do we delete?

[`ctor2.cpp`](ctor2.cpp)

- We can use smart pointers to handle this. Only objects that were successfully constructed will be destructed.

## Containers

- A container is an object that holds a collection of other objects.
- Today we will only talk about _sequence_ containers, where the user specifies the order.

## `vector`

[`vector.cpp`](vector.cpp)

- `vector` provides an array-like contiguous sequence of elements.
- `push_back` adds an object to the end of the `vector`.
- All containers provide `.size()` and `.empty()`, among other members.
- Note that you should use a `vector` of `unique_ptr` or something similar if you want polymorphic behavior.

[`emplace.cpp`](emplace.cpp)

- `vector` is typically implemented by doubling its size once it is full.
- Lots of copies/moves are made!
  - `vector` prefers copies/moves in this order: `noexcept` move ctor, copy ctor, normal move ctor (since a move ctor that throws is more dangerous than a copy ctor that throws, see [this SO question](https://stackoverflow.com/questions/28627348/noexcept-and-copy-move-constructors) for details)
- `push_back` copies/moves an object into the `vector`.
- `emplace_back` takes the arguments of the object constructor and creates the object _in_ the `vector`, saving a copy/move.

[`range.cpp`](range.cpp)

- Accessing elements using `[]` just accesses the underlying memory, without range checking.
- Using `.at(...)` to access an element does range checking, and throws `out_of_range` if the argument is out of range.
  - There is some overhead to doing this check (~10%).

[`operations.cpp`](operations.cpp)

- All containers provide a few standard operations.
  - `operator==` just checks if all the members are equal and in the same order.
  - `operator<` checks the lexicographic order.
  - `swap`, copy/move constructors/assignments are all defined.

## `array`

[`array.cpp`](array.cpp)

- A container for a fixed-length array, an alternative to using C arrays.
  - Benefits are that it stores its size (using `.size()`), doesn't convert to a pointer implicitly, and has some convenience functions.
  - _No_ runtime overhead compared to C arrays.
- Defined in `<array>`.

## `list`

[`list.cpp`](list.cpp)

- `list` is a doubly-linked list.
- `forward_list` is a singly-linked list, if you really need the lower overhead.
  - It also does not provide `size()` to reduce overhead.

## `deque`

[`deque.cpp`](deque.cpp)

- A double ended queue (deque, pronounced "deck") has 2 usual implementations: as a doubly linked list and as an array that can be extended in either direction. Since C++ provides a linked list container already, `deque` is an implementation of the latter.
- Like `vector`, but also with fast insertion at front.
  - Not strictly better however, since this is implemented with multiple underlying arrays (we can't extend arrays in both directions indefinitely). Multiple pointer dereferences are needed to access elements, as opposed to one dereference for a `vector`. It also typically needs more memory than a `vector`.

## Container adapters

- C++ also provides container _adapters_, which are containers that use another container as its underlying container.
- `stack` and `queue` are fairly straightforward. Both use `deque` by default, but `list` also works and `vector` is also suitable for `stack`.
- `priority_queue` provides constant time for accessing the largest element, and logarithmic time for insertion and deleting the largest element.
  - Uses `vector` by default, though `deque` is also available.
  - Uses standard library functions to manage a heap in the underlying container.
  - The comparison function can be customized to reverse the ordering, for example.

| Container | Insertion | Access | Deletion |
| --- | --- | --- | --- |
| `vector` | O(1) at back<br>O(n) otherwise | O(1) | O(1) at back<br>O(n) otherwise |
| `deque` | O(1) at front and back<br>O(n) otherwise | O(1) | O(1) at front and back<br>O(n) otherwise |
| `list`/`forward_list` | O(1) after reaching the element | O(1) at front and back (only for `list`)<br>O(n) otherwise | O(1) after reaching the element |
| `priority_queue` | O(log n) | O(1) for the max | O(log n) for the max |
