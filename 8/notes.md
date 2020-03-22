# Lecture 8: Mar 23 2020

## Templates

- Templates are used for _parametric polymorphism_, for writing code that does not depend on the type of a value.

### Function templates

[`function_template.cpp`](function_template.cpp)

- We can write functions that are parametric on an input type.
- The compiler generates a separate function for each use of the template with a different type.
- `typename` and `class` are interchangeable in the template prefix. I prefer `typename`, since not all types are classes in C++. You may find `class` in older code.

### Class templates

[`class_template.cpp`](class_template.cpp)

- We can also write class templates.
- The container classes and smart pointers that we've seen are all examples of these.

[`templates/wrapper.hpp`](templates/wrapper.hpp)

[`templates/wrapper.tpp`](templates/wrapper.tpp)

- The compiler generates different code each time the template is _instantiated_, so the implementation and interface must be bundled together in the same file for this to occur (due to separate compilation).
  - Sometimes people still break up the interface and implementation for organization or design reasons, but `#include` the implementation file (usually using a different file extension) in the interface file so it still compiles.

- We can also write function templates.
- The things we've talked about in the past 2 weeks are _not_ object-oriented.
  - If it were, there would be overhead in the form of virtual function calls when trying to perform operations abstractly.
  - To abstract over them we can use templates instead, since they share a consistent common interface.
  - Note that we can't use templates in place of virtual calls, since virtual calls can perform dynamic dispatch (look up and call different functions at runtime), while templates cannot.

### Requirements on templates

- For most cases we want some restrictions on what type parameters are acceptable in templates.
- E.g. for `wrapper` above we want `T` to be copy constructible, since we copy it when `get` is called.
- [Requirements](https://en.cppreference.com/w/cpp/named_req) on types are very common, but there is currently no way to write them in C++.
- _Concepts_ are a way of writing these requirements down and enforcing them, to come in C++20.
  - Similar to traits in Rust or typeclasses in Haskell.

### Type aliases for templates

[`using.cpp`](using.cpp)

- All containers provide a few common member _types_, like `value_type`, so they can be used generically.
- `using` in this context is the same as `typedef`.
- We need `typename` to tell the compiler the following expression is a type.
  - This was not necessary for things like `vector<int>::iterator` since you can check that expression is a type.
  - Since `Container` here is a template parameter, the compiler cannot know what `Container::value_type` is until after template instantiation.

#### Unrelated note: templates can have default arguments. (e.g. `map`)

## Value template arguments

[`value.cpp`](value.cpp)

- We can also write class or function templates that are parameterized by values.
  - Why when we can pass values normally? Some things (e.g. arrays) require _compile-time_ constants (see below), and also, having the argument be a constant can be useful.
- e.g. `array` that takes the size of the array.

### `constexpr`

- What can we use as a value template argument?
  - Alternatively, what can we use as an array size?

[`constexpr1.cpp`](constexpr1.cpp)

- `constexpr` is a _stronger_ notion of immutability than `const`.
  - `const` is basically a _promise_ that you won't change this variable.
- A variable declared `constexpr` means it will be evaluated at compile time.
  - `constexpr` variables are also `const.
- Useful for declaring constants and placing values in read-only memory in the executable.
  - Similar to `#define`'s use cases in C.
- So far this seems kind of useless. Why do we need a whole new keyword for literals that the compiler knows at compile time anyways? Simple cases work just fine with `const`.
- What if we want to perform more complex operations at compile time?

[`constexpr2.cpp`](constexpr2.cpp)

- What if we want to perform more complex operations at compile time?
- `constexpr` can also be applied to functions.
- Functions can only be made `constexpr` if they are simple (pure in functional programming terminology): they can only use arguments passed to it and cannot have side effects.
- When a `constexpr` function is called with `constexpr` arguments, the output is also `constexpr`.
- A `constexpr` function can also be used as a regular function (which doesn't return a `constexpr`).

- `g++ -s -S constexpr2.cpp` to see the assembly output of the compiler.
  - `-s` removes debugging information, and `-S` generates assembly instead of an executable.

## Template metaprogramming

### Template specialization

[`specialization.cpp`](specialization.cpp)

- Templates can have custom code for specific instantiations.
- `template <>` is required, to tell the compiler the class/function is a template.
- The specializations must come after the general template declaration.
- e.g. `vector<bool>`

### Metaprogramming

- Metaprogramming is where programs can themselves deal with programs as data.
- Templates are already an instance of metaprogramming -- they generate code for you.

[`fib.cpp`](fib.cpp)

- A more general style that is actually Turing-complete (Veldhuizen 2003) was discovered, without the intent of the C++ designers.
- A "functional language" using templates, with specializations as "base cases".
- Moves computation from runtime to compile time.
- Uses `struct`s to hold values that we are computing.

[`collatz.cpp`](collatz.cpp)

- Similar in use to `constexpr`, though templates are more expressive.
  - E.g. templates can deal with any type, not just simple types.

## Abstracting over functions

- Higher order functions, as you've seen in CIS 120, are really useful.
- We can use function pointers from C, but these are fairly basic and cannot be parameterized (i.e. there are no function pointers to function templates).

### Function objects

[`functor.cpp`](functor.cpp)

- A function object (sometimes called a functor) is an object that can be called like a function.
- This is done by overloading `operator()`.
- The object can store other state inside, which can be useful.
- A functor is just a regular object, so its class can also be made a class template.
- Note that `struct`s and `class`es can be written within other structures, like functions and other `class`es.
