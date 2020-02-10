# Lecture 4: Feb 10 2020

## Destructors

[`eg0.cpp`](eg0.cpp)

- How does the dynamically allocated memory get freed?

[`eg1.cpp`](eg1.cpp)

- Called automatically when an object's lifetime ends
- Used to clean up resources
- If there is a possibility of subclasses, destructors should be `virtual` (why?)

### Order of construction and destruction

[`order.cpp`](order.cpp)

- The constructor initializes the base class (using a constructor if it was in the initializer list), then class members in _declaration_ order (order in initializer list doesn't matter), then the constructor body.
- The destructor calls the destructor body, then destructs class members in _reverse_ order of declaration, then destructors of base classes (why?).
- Note that we use declaration order, since the order of the initializer list can differ for different constructors, and the destructor needs to run in the reverse order as construction.
- Destruction order in general is the reverse of the construction order (e.g. local variables).

## Copy

[`eg2.cpp`](eg2.cpp)

- Copies are made when:
  - Initialization with another object: `integer i {j}`, `integer i(j)`, `integer i = j`.
  - Passing an object (by value) to a function.
  - Returning an object (by value) from a function.
  - Throwing an object as an exception (more on this in a later lecture).
  - Assigning an object to another object (more on this in the next example).
- The parameter to the copy ctor must be a reference to its own class, but doesn't have to be `const`. Would taking a non-reference make sense?
  - Logically `const` makes more sense
  - Also, must be `const` for copying from `const` objects/temporaries.

[`eg3.cpp`](eg3.cpp)

- Copy elision omits copies in some simple cases.

[`eg4.cpp`](eg4.cpp)

- Copy assignment operator
- Be careful of self assignment
  - e.g. if in `operator=` we have `delete p; p = new int {i.get()};` this would fail for self assignment!

## Move

[`eg5.cpp`](eg5.cpp)

- lvalues vs rvalues
- We can "steal" the resources of an rvalue.
- Note that `delete nullptr;` is a NOP.

[`eg6.cpp`](eg6.cpp)

- Assignment again
- Self assignment? (see below)

[`eg7.cpp`](eg7.cpp)

- `std::move` in `<utility>`
  - Forcefully moving
  - Use in move ctor and move assn, to move member variables with user-defined types, for example.
  - Note that you can assume that `i = move(i)` is not performed, so move assn doesn't have to worry about self assignment.

## Defaults for special member functions

- The default constructor is generated if no other constructor is user-defined.
- The destructor is always generated if you don't define it yourself.
- The copy constructor and copy assignment are generated if the move constructor and move assignment are not user defined.
- The move constructor and move assignment are generated if the user didn't define any other special member functions.

## Base classes

- Note that you need to call the base class copy/move constructor/`operator=` yourself if you are writing a custom copy/move constructor/`operator=` (and you want the base class's behavior). The implicit (`= default`) ones will do it for you.
  - All constructors (copy/move included) will call the base class default constructor if you don't call any base class constructor in the initializer list.
  - Destructors will also call the base class destructor (as noted above)

## Misc extra stuff

- Default arguments.
  - It is possible to declare the default in either the declaration or the definition of the member function (not both). You should do this in the declaration (header), otherwise a caller can't know it exists.

- `enum` and `enum class`es
  - `enum` just declare some names for ints 0, 1, 2, 3, etc
  - `enum class` is strongly typed and scoped enumerators
    - can actually define more operators, but won't go into this.
    - prefer enum class to enum, in most cases
