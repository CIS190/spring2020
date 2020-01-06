# Lecture 1: Jan 15 2020

## Logistics

- See the [course webpage](https://www.seas.upenn.edu/~cis190/) for the syllabus and schedule.
- I won't be using Canvas this semester.

## What is C++?

- Originally created as "C with Classes" by Bjarne Stroustrup in 1979.
- Now a general purpose, multi-paradigm language (imperative, functional, object-oriented, generic all possible).

## Design principles

- Zero-overhead abstractions
  - If you don't use an abstraction (e.g. exceptions, dynamic dispatch), you should not have to pay for them.
  - Abstractions should not have any more overhead than implementing them manually.
- Direct map to hardware.
  - No language "below" C++ besides assembly.
  - C++ operations directly map to hardware operations. e.g. the standard library `vector` is just a contiguous block of memory, like an array. Arithmetic operations map directly to the assembly instructions. This can cause issues like `%` with negative numbers, which may differ in behavior based on platform.

## Hello world

[`hello.cpp`](hello.cpp)

- Compile with `g++ -std=c++17 -Wall -g -o hello hello.cpp`.
- To use C++17 features, you should use `g++` version 7 or newer.
- `-Wall` turns all compilers warnings.
- `-g` adds debugging information to be used by the `gdb` debugger.
- `-o NAME` lets you specify the name of the output executable. Without it, the default name is `a.out`.
- `main` returns `int`.

### `#include`
- `#include` basically copy and pastes the contents of a file into the current file.
- `iostream` (input/output stream) contains the declaration of `std::cout`.
- C++ standard library header files do not have the `.h` extension.
- "" vs <>.

### `cout`
- `std::` is the standard library _namespace_.
- `cout` (character output) is the standard output stream (we'll discuss in more detail later).
- `<<` is the "put to" operator (overloads the standard bit shift operator).
- `\n` is an _escape sequence_, which starts with `\`. It represents a newline character (0x0A in ASCII).
  - to print `\`, use `\\` in the string.

## Functions

[`functions.cpp`](functions.cpp)

- `void` means the function does not return any value.
- note that we can "chain" multiple `<<`s when using `cout`: we'll talk more about how this works later.
- pass by value by default.

We can overload functions (same function name) as long as they can be differentiated (e.g. adding `int triple(double n)` is ambiguous since only the return type differs).
If we add:
```c++
double triple(double n)
{
	return 3 * n;
}
```
to the code, everything will still work fine.

- Arithmetic operators: `+ - * / %`

C++ processes the source code linearly.
- That means this code will not compile: [`evenodd.cpp`](evenodd.cpp)
- We need to add a _declaration_ `bool odd(int);` to tell the compiler that this function exists, and has this type (return type + type and number of arguments).
- Declarations can happen multiple times, but _definitions_ can only happen once.

## If
- Comparison operators: `== != < > <= >=`
- Logical operators:
  - Bitwise: `& | ^ ~`
  - Logical: `&& || !`
- `if (int i = getVal(); i == 0) ...`
- `switch`
  -	Like `if` and `for`, can also do `switch (int i = ...; i) ...`.

## Variables
- e.g. `auto i {0};`
  - same as `int i = 0;`
  - `{}` can help detect unwanted type conversions: `int i = 1.1;` works but `int i {1.1};` doesn't.
- Initialize before use
  - Undefined behavior
- `const`
- Arrays
  - `int arr[4];`
  - `int arr[] {1, 2, 3, 4};`
  - `arr[0] = 1; ... arr[3] = 4;`
  - Does `arr[4] = 1;` work?
  	- Undefined behavior

## Loops

4 types of loops
```c++
for (auto i {0}; i < 10; ++i)
	...;
```

```c++
while (i > 0)
	...;
```

```c++
do
{
	...
} while (i > 0);
```

```c++
for (auto i : {1, 2, 3, 4})
	...;
```

- `i++` vs `++i` (or `--`)
- `+= -= *= /= %=`
- `,` operator.
- scope

## Pointers

[`remainder.cpp`](remainder.cpp)

- `*` denotes a pointer type.
- Holds the address to some memory, using the type for size information.
- `*` (contents of, also called dereferencing) and `&` (address of).

[`newdelete.cpp`](newdelete.cpp)
- `new` and `delete`
  - `new[]` and `delete[]`
