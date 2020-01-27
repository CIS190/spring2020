# Lecture 2: Jan 27 2020

## Pointers continued

- Pointer arithmetic
  - Same mechanism as array access

[`const.cpp`](const.cpp)

- `const` pointers, "spiral rule".
- `nullptr`

## Debugging

### `gdb`
[`debug.cpp`](debug.cpp)

- `gdb prog` to run gdb on the program `prog`
- or just run `gdb`, and load the program `prog` with `file prog`
- `run` to start debugging
- `backtrace` to view a stack trace
- `break filename:number` to set a breakpoint at some line number
  - or `break functionname` to set a breakpoint when the function is called
- `continue` to continue running after a breakpoint
- `step` to execute one line and break again
- `print varname` to print the value of a variable
- `watch varname` to break each time the value of a variable changes
- Many other features and editor integrations

### `valgrind`
```c++
int main()
{
	auto * p {new int};
}
```

## References

- Why do we use pointers?
  - pass by reference
  - dynamic allocation
- _References_ will solve the first problem.

[`remainder.cpp`](remainder.cpp)

- same e.g. as last class.
- Basically a `const` pointer that is automatically dereferenced.
- Must be initialized! No "null" reference.
- `const` references can be used for cheap argument passing.
- note on spacing: `*` and `&` are part of the type, so usually written as `int*` or `int *`.

## Standard streams

- stdout, stdin, stderr
  - abstraction of terminal I/O
  -	https://en.wikipedia.org/wiki/Standard_streams

## Output

- objects of type `ostream`.
- `cout`

[`buffered.cpp`](buffered.cpp)
- buffering
- `cout` (buffered, stdout)
- `cerr` (not buffered, stderr)
- `clog` (buffered, stderr)

- `<<` chaining is OK because `<<` is left-associative and `<<` returns the same stream.
  - `cout << 1 << "2";` is the same as `(cout << 1) << "2";`
  - The operator returns the stream by reference.
    - when doing this, as with pointers, be careful with scope.
    - Here we are returning a reference that was also an argument, so there are no lifetime issues.

- You can also do some formatting, e.g. `cout << scientific << 1.1;`
  - many other operations available, some in the `<iomanip>` header.

### Input

[`cin.cpp`](cin.cpp)

- object of type `istream`.
- `cin`
- `>>` ("get from")
  - skips whitespace
- `getline` to read until a newline.
- Handles memory management for you, no buffers to allocate.

[`readall.cpp`](readall.cpp)

- streams have a conversion to `bool` which tell you whether there is an error (e.g. EOF).
  - alternatively, check `cin.fail()`.
  - Ctrl-D to insert an EOF when reading from stdin.
- There are other flags and state operations for streams that I won't go into.
- `iostream` inherits from both `istream` and `ostream`.

## File and string streams

### `<fstream>`

- streams to and from a file.

[`fstream.cpp`](fstream.cpp)

- `ifstream`
- `ofstream`
- _Core_ stream operations are the same.
- There is also `fstream` that does both input and output, inherits from `iostream`

### `<sstream>`

- streams to and from a string.

[`sstream.cpp`](sstream.cpp)

- `istringstream`
- `ostreamstream`
- `stringstream`
- Typically used if you want to read/write a string from something that's not a file or stdin/stdout (e.g. network, GUI, function call, etc).

### Polymorphism

[`polymorphism.cpp`](polymorphism.cpp)

- Polymorphism in C++ requires passing by reference or pointer.
  - What would happen otherwise, using the normal pass by value?
