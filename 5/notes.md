# Lecture 5: Feb 17 2020

## Exceptions
- In C...
  - Return codes
    - easy to ignore
  - `errno.h`
    - easy to ignore
  - `setjmp.h`
    - Like `goto`, can simulate exception handling in C, but won't support objects in C++.

[`exceptions.cpp`](exceptions.cpp)

- `throw` _unwinds_ the stack to find an exception handler (an enclosing `try`-`catch` block).
- We're allowed to `throw` any type.
  - `<stdexcept>` holds a base `exception` class and some common types of exceptions.
- Can `catch` by value or reference (but you should almost always catch by (const) reference, for polymorphism)
- `catch` clauses are processed in order from top to bottom. `catch(...)` catches any exception, so it has to be the last `catch` clause.
- No `finally` clause as in Java.
- `throw;` to rethrow the caught exception (useful for the `catch(...)` case, where it's unnamed).

[`noexcept.cpp`](noexcept.cpp)

- Can declare functions that should never throw as `noexcept`
  - The program terminates if the function does ever throw, even if a handler is available.

## Exception safety

- See the [wikipedia article](https://en.wikipedia.org/wiki/Exception_safety) for more details.
  1. No-throw guarantee
  2. Strong guarantee: failed operations are guaranteed to have no side effects. They are "rolled back".
  3. Basic guarantee: failed operations can result in side effects, but there are no leaks or broken invariants.
  4. No guarantee.

## Copy/move and swap

- If our `integer` example from last class had multiple members to copy/move, its `operator=` would only have a basic guarantee, since it may fail in the middle of the operation.

[`swap1.cpp`](swap1.cpp)

- `std::swap` in `<utility>` is `noexcept`.
- Only the call to the copy/move ctor can throw now.
- If the constructor fails, we don't perform the swap and the object is unchanged.
- This also removes the repeated code in the copy ctor/copy assignment, and in the move ctor/move assignment.

[`swap2.cpp`](swap2.cpp)

- Take the argument by value to skip the copy/move step, since it will be copied/moved in.

[`swap3.cpp`](swap3.cpp)

- `std::swap` is implemented as 3 move assignments. If we try to do `swap(*this, i);` in `operator=`, this will result in an infinite loop.
- But `swap` is a useful operation. The standard library `sort` uses it, for example.
- You can provide your own `swap` instead of `std::swap` for your class, and implement your move assignment in terms of that.
  - For some classes you may be able to write a faster version of `swap` than the 3 move assignments of `std::swap`
  - Your swap logic (here this is just swapping `p`) will have to go in either a custom `swap` or `operator=`.
- How does C++ choose which `swap` to use? If you specify using `std::swap`, it will pick that, but often we don't know if there's another `swap` that we want to use.
  - So typically `std::swap` is made accessible as `swap` with `using std::swap;`, and `swap` is called. A mechanism called [argument-dependent lookup](https://en.cppreference.com/w/cpp/language/adl) looks for a `swap` related to the types of the arguments (`integer`) before other namespaces, so `swap`, a `friend` of `integer`, is called. If this `swap` didn't exist, `std::swap` would be called. Code in the standard library that calls `swap` does this, to use user-defined instances of `swap` before falling back to `std::swap`.
- `friend` declares the function as a friend and defines it at the same time. This is equivalent to declaring it as a friend in the class and defining it outside the class (which we did before with `operator<<` and `operator>>`).

- Note that there is overhead (use of temporary object, extra moves) to using copy/move and swap!

## Resource acquisition is initialization (RAII)

- Idiom where resources are attached to the lifetime of the object. Acquiring resources (memory, files, locks, etc) is done in the constructor, and released in the destructor. If acquiring the resource fails, the constructor fails, and the object is invalid. Otherwise, the language guarantees that the destructor is called, releasing the resource and preventing leaks.
- _Crucial_ in C++. Takes the place of `finally` in other languages, since destructors are called during stack unwinding as well.
  - Because of this, destructors should _never_ throw. If one of the called destructors throws during stack unwinding, we can't stack unwind in parallel, so the program will terminate if this happens.

## Smart pointers

- A _smart pointer_ is a class that wraps a regular pointer, and uses its destructor to `delete` it.

### `unique_ptr`

[`unique.cpp`](unique.cpp)

- `unique_ptr` (in `<memory>`) represents unique ownership of a pointer.
- The type held is enclosed in `<>`.
- Can be initialized directly with `unique_ptr<int> i {new int {1}};`, or using `auto` and `make_unique`: `auto i {make_unique<int>(1)};`. `make_unique` allows us to use `auto` and avoid repeating the type twice. It also calls the constructor of the type based on the arguments passed to it, so we don't need to call `new` ourselves.
  - `make_unique` also makes sure that the thing being put into the `unique_ptr` is a newly allocated piece of memory, and not any random pointer, for example.
- If the `unique_ptr` holds an array, its type can be specified as `<int []>`.
- All the operations (`*`, `->`, `[]` in the case of `<T[]>` pointers) on pointers work the same way.
- `get`, `reset`, and `release` deal with the underlying pointer.
- It's possible to specify a custom deleter, to call `fclose` on a `FILE *`, for example.
- `unique_ptr`s cannot be copied, only moved.

### `shared_ptr`

[`shared.cpp`](shared.cpp)

- `shared_ptr` represented shared ownership of a pointer.
- `shared_ptr`s can be copied, and keep track of the number of references each held object.
  - Use the `shared_ptr`'s copy constructor or assignment operator. Making a new `shared_ptr` using the underlying pointer is undefined behaviour.
- An object is only destroyed once no `shared_ptr`s hold that object.

### `weak_ptr`

[`weak.cpp`](weak.cpp)

- `weak_ptr` represents temporary ownership of a pointer ordinarily owned by a `shared_ptr`.
- Without `weak_ptr` objects with cyclic references would never be destroyed.
- Must be converted to a `shared_ptr` temporarily to access the underlying pointer using `lock`.
- Since `lock` returns a `shared_ptr`, it increases the reference count by one and the pointer will not be invalidated while it is being used.
