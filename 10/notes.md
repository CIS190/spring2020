# Lecture 10: April 6 2020

### Modifying containers

- None of the algorithms add or remove elements of a container, they only operate on _ranges_ defined by iterators, so they are unable to affect the size of the actual container.

[`remove1.cpp`](remove1.cpp)

- e.g. `remove` shifts the elements in the range to remove some elements, and returns a new end of range iterator. The underlying container's size is unchanged.

[`copy1.cpp`](copy1.cpp)

- e.g. `copy` assumes there is enough space in the destination container to copy the source range.

[`remove2.cpp`](remove2.cpp)

- One option to modify a container is by directly referring to it.
- e.g. after calling `remove` call `erase` on the container with the iterator returned by `remove`.

[`copy2.cpp`](copy2.cpp)

- e.g. Resize the container to the appropriate size before calling copy.

[`copy3.cpp`](copy3.cpp)

- You can also use something that knows about the container to modify it.
  - e.g. `back_inserter`, `inserter`, and `front_inserter` (in `<iterator>`) create special iterators that call `push_back`, `insert`, and `push_front` respectively, so the container will grow when things are written to the iterator.

### Parallel algorithms

[`execution.cpp`](execution.cpp)

- Most functions also accept an _execution policy_ (as the first argument), which allows for parallelization.
- If an execution policy is not specified, `execution::seq` (sequential) is the default.
- `execution::par`
  - Permits the algorithm to be parallelized.
- `execution::par_unseq`
  - Permits the algorithm to be parallelized _and_ vectorized (unsequenced execution on a single thread, using [SIMD](https://en.wikipedia.org/wiki/SIMD) instructions.
  - Can break some synchronization methods (more on this next lecture).
- These execution policies are _guidelines_ to the compiler. It is not guaranteed that using them will actually generate parallel code.
- Execution policies are badly supported by `g++`. It was implemented in `g++ 9.1` (in 2019) using the Intel TBB library (`-ltbb` flag at the end of the command to link the library).
  - This code is unlikely to run on your machine without installing anything new.
  - Use the instructions at [this link](https://solarianprogrammer.com/2019/05/09/cpp-17-stl-parallel-algorithms-gcc-intel-tbb-linux-macos/) to install the dependencies.

## Functional programming in C++

- C++ is a multi-paradigm language.
- We've seen OOP, generic programming, procedural programming so far. Functional programming is also possible.

[`oop.cpp`](oop.cpp)

- But calling member functions and regular functions are different.
  - One solution is to use a lambda to perform the call.
  - You can also use `mem_fn` (in `<functional>`), which converts a member function to a regular function object.

[`bind.cpp`](bind.cpp)

- `bind` (in `<functional>`) partially applies a function.
  - In order to leave arguments unbound, use `placeholders::_1`, `placeholders::_2`, etc.

[`higher.cpp`](higher.cpp)

- `<functional>` provides many functor versions of common operations, like `plus` which just wraps `+`.
- Other common higher-order functions are available as well
  - e.g. `accumulate` (in `<numeric>`) is a fold, `transform` is a map

### Function types

[`recursion.cpp`](recursion.cpp)

- So far we have used templates to take functors/lambdas/function pointers parameters.
- In fact, in the case of lambdas, they have some _unspecified_ unique type, so you cannot write its type without `auto`.
- `function` is a function class that holds any callable function.
- Needed (actually, there are some more complex workarounds without using `function`) for recursive lambdas since `auto` needs to know its own type, but its own type (from `auto`) depends on itself.
  - We need to capture by reference since capturing by value gets an uninitialized `function`.
  - Note that you can't return this lambda since it depends on a local variable (itself).

[`functions.cpp`](functions.cpp)

- Also useful if you have a heterogeneous collection of functions to call with the same signature, but not necessarily the same type.
- You should prefer templates to `function` if possible though, since `function` can have some runtime overhead (due to indirection and having to copy the thing it is wrapping).
