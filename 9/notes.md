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
