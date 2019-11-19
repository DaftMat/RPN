# RPN School project
RPN (Reverse Polish Notation) is a calculation method to parse a mathematical expression from left to right.
Done in C++.

# Dependencies (as submodules)
 - [Acutest (Unit testing lib)](https://github.com/mity/acutest)
 
# Features
 - RPN calculation (parse any valid expression)
 - Do nothing when there is `;` at the end of the expression
 - Variables management (only letters)

# Compilation
Run the following commands :
```txt
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Running
## Application
Here's the location where you'll find the executable application :
```txt
Bundle-*/bin
```
note : * is the name of the compiler you use (can be GNU, CLANG, ...)

The application takes zero or one argument :
 - If there is an argument, it will be used as a file name where a list of expression will be read.
 - Otherwise, it will ask you expressions through STDIN.

### Examples of execution
Basic Expression usage :
```txt
$ ./RPNapp
> Welcome to the RPN application. Type expressions (CTRL-D to end).
> 5 + 9
> 5 + 9 = 14
> 8 * (2 ^ 3);
> 8 * 4
> 8 * 4 = 32
$ ./RPNapp path/to/file.txt
> 5 + 9 = 14
> 8 * 4 = 32
```

Variables usage:
```txt
> Welcome to the RPN application. Type expressions (CTRL-D to end).
> twopi = 2 * 3.1415926536;
> radius = 3*8;
> circ = twopi * radius;
> circ
> circ = 150.79644738
```

File Usage :
```txt
5 + 9
8 * (2 ^ 3);
8 * 4
```

## Unit tests (could be used for CI)
Type the following command from the build directory to run unit tests :
```txt
$ make buildtests
$ make check
```
note : you must have generated the CMakeLists.
