# RPN School project
RPN (Reverse Polish Notation) is a calculation method to parse a mathematical expression from left to right.
Done in C++.

# Compilation
Run the following commands :
```txt
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Running application


Here's the location where you'll find the executable application :
```txt
Bundle-*/Debug/bin
```
note : * is the name of the compiler you use (can be GNU, CLANG, ...)

The application takes zero or one argument :
 - If there is an argument, it will be used as a file name where a list of expression will be read.
 - Otherwise, it will ask you expressions through STDIN.

## Examples of execution
```txt
$ ./RPNapp
> Welcome to the RPN application. Type expressions (CTRL-D to end).
> 5 + 9
> 5 + 9 = 14
> 8 * (2 ^ 3)
> 8 * (2 ^ 3) = 64
$ ./RPNapp path/to/file.txt
> 5 + 9 = 14
> 8 * (2 ^ 3) = 64
```

## Example of file to be parsed
```txt
5 + 9
8 * (2 ^ 3)
```