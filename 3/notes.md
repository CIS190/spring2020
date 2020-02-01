# Lecture 3: Feb 3 2020

## Classes

[`class.cpp`](class.cpp)

- `class` vs `struct`.
  - don't need to declare a struct as `struct pair p`, just `pair p`.
  - `struct`s are more "first class" than in C.
  - "real" types.
- The `Point` function is the _constructor_ for the class.
- `: x {x}, y {y}` is an _initializer list_, which initializes these variables. You can't initialize them in the body of the constructor, only assign to them. Since you can't assign to references, they _must_ be initialized in the initializer list.
- `this`: pointer to current instance, implicit first argument to member functions.
- Note that the parts of a class are typically called _members_ in C++, e.g. member functions, member data, though terms from other languages like _methods_ are sometimes used too.

[`const.cpp`](const.cpp)

- `const` after a member function declaration means the function does not mutate the object.
- Only `const` member functions can be used on `const` objects.

## I/O for user-defined classes

- Depending on the type of the first argument to the overloaded operator, the operator can be defined as a member function of the first argument's class or a free function.

[`overload.cpp`](overload.cpp)

- overload `operator>>` and `operator<<` for your classes.
- idiomatic way of printing custom classes (vs `toString()` in Java).

## Separate compilation

- Code in multiple files (why?)
- Header files (`.h`, `.hpp` common) are the interface

[`separate/point.hpp`](separate/point.hpp)
[`separate/point.cpp`](separate/point.cpp)
[`separate/main.cpp`](separate/main.cpp)

- Declaration vs. definition of classes and class members.
  - One definition rule.
- Use `#include "..."` for user-defined headers.
- `class::member(...)` (scope resolution operator) to _define_ member functions.
  - note that `const` member functions have `const` as part of the type, so it must be included in the `.cpp` too.
- Use include guards to prevent multiple `#include`s of the same file.
    - `#ifndef`, `#define`, `#endif`
  - `-E -P` to see the result of the preprocessor
- Each `.cpp` file (called a _translation unit_) is compiled into an object file, and these are all linked together to form the executable.
- Typically each class is in its own translation unit.

- Note that all this isn't strictly part of the language, it's just convention. It works fine to put definitions in headers (though functions defined in a class definition are `inline` by default.), or to put everything in one file. Compile times and ease of programming may suffer though (and your grades if you do this in homeworks).
  - And this system isn't perfect: e.g. the _definition_ of a class is put into the header file, including its private members.
  	- Because the private members are required to compute the size of the class (needed if you want to declare an object of this class, but _not_ if you use a pointer or reference)
	  - If a forward declaration of a class is sufficient use that, not the whole `#include` to speed up compile times. This is typically done in header files.
	- "pImpl" idiom to circumvent this
- "Real" module system to come in C++20 (`import module` instead of `#include`)

### Inheritance

[`inheritance.cpp`](inheritance.cpp)

- `: public superclass`
- `virtual`
  - Not required in derived class, derived virtual members are still virtual
  - Why?
  - Overhead, pointer to vtable
- `override` after the member function declaration is not necessary
  - But it helps for documentation and can catch bugs (e.g. trying to override something but misspelled function name)
- Pure virtual function: `= 0;`
- Abstract classes are those that have a pure virtual function (either defined or inherited without being overriden with a non pure virtual function).
  - You cannot define objects of abstract classes.
- Classes you _can_ instantiate are called concrete classes.
- `final` can be used after the class name or after the function declaration to disallow inheritance and overriding, respectively.

### Constructors

- Default constructor: constructor with no arguments.
  - Required for some applications, like arrays.
  - When an object is constructed and a member isn't initialized, its default constructor is called.
  - If a class has _no_ constructors, an implicit one will be defined, which is equivalent to the empty constructor.
    - If you want the default-generated default constructor and it wasn't generated (because you have another constructor, for example), you can tell the compiler to do this explicitly: `classname() = default;`.
- You can also explicitly disallow use of the default constructor (and other implicitly generated things that we'll see later) with `classname() = delete;`.
  - Note the differing terminology from Java.

[`conversion.cpp`](conversion.cpp)

- Constructors define a conversion from its argument types
  - To disable this, use `explicit classname(...);`

### Misc things

[`default.cpp`](default.cpp)

- Default member initializers
