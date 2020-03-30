# Lecture 9: Mar 30 2020

## Abstracting over functions continued

[`hash.cpp`](hash.cpp)

- `unordered_map` uses `std::hash` by default, or you can provide your own functor.
- `std::hash` is a template class defining a functor.
- The standard library provides specializations of `hash` for the basic C++ types.
- We can write our own specialization as well, and add it to the global namespace.

### Lambda expressions

[`lambda.cpp`](lambda.cpp)

- A lambda expression is shorthand for declaring a function object.
- If you need the type of the function object (e.g. if you want to use a lambda as the comparison object for `map` or a hash object), you can use `decltype`.

[`capture.cpp`](capture.cpp)

- `[]` is the _capture list_ of the lambda expression.
  - It allows the body of the lambda to access variables outside it.
  - `[limit]` captures `limit` by value.
  - `[&limit]` captures `limit` by reference.
  - `[=]` and `[&]` capture _everything_ by value and reference respectively.
  - A comma delimited list can customize which variables are captures by value or by reference.

[`generic_lambda.cpp`](generic_lambda.cpp)

- You can write generic lambdas using `auto` for its arguments.
  - This isn't allowed for regular functions.
- If necessary, you can use the syntax `-> T` after the `)` to specify that the lambda has return type T. When dealing with generic lambdas, often `decltype` is useful here.

## `<algorithm>`

- The standard library provides a long list of algorithms in `<algorithm>`. Most are function templates that take iterator arguments.
- Most of these functions use templates. The standard library is heavily based on the standard _template_ library (STL), a library written in 1993. Many people still call the standard library the STL.

[`for_each.cpp`](for_each.cpp)

- `for_each(first, last, f)` calls a function `f` on each element of the range defined by `first` and `last`.
- A range-based for loop is often simpler, but `for_each` allows the range to be specified.

[`find.cpp`](find.cpp)

- `find` returns an iterator to the first place where a value is found, or the end iterator if no match is found.
- There are also `find_if` and `find_if_not` variants that take a predicate instead.

[`algorithms.cpp`](algorithms.cpp)

- `iota` fills a range with an incrementing sequence. (Named after the ι function that did the same thing in APL, a programming language)
- The standard library also provide classes (in `<random>`) that generate _random_ and pseudorandom numbers in much more sophisticated ways than C `rand` and `srand`. See the [documentation](https://en.cppreference.com/w/cpp/numeric/random) for more details.
- `shuffle` reorders the range such that any permutation has equal probability to be chosen. It requires a source of random numbers.
- `replace` and `replace_if` replace some elements of a range.
- `sort` sorts a range defined by _random access_ iterators.
  - Other containers like `list` have a member `sort` function, since the implementation has to differ.

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
- `function` is a function object that holds any callable function.
- Needed (actually, there are some workarounds without using `function`) for recursive lambdas since `auto` needs to know its own type, but its own type (from `auto`) depends on itself.
  - We need to capture by reference since capturing by value gets an uninitialized `function`.
  - Note that you can't return this lambda since it depends on a local variable (itself).

[`functions.cpp`](functions.cpp)

- Also useful if you have a heterogeneous collection of functions to call with the same signature, but not necessarily the same type.
- You should prefer templates to `function` if possible though, since `function` can have some runtime overhead. Conceptually, templates are also a "safer" option since they involve static (compile-time) checks.
