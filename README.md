# RPN School project
RPN is a calculation method to parse a mathematical expression from left to right.
Done in C++.

# Compilation
Run the following commands :
```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Running application
Here's the location where you'll find the executable application :
```sh
Bundle-*/Debug/bin
```
note : * is the name of the compiler you use (can be GNU, CLANG, ...)

The application takes zero or one argument :
 - If there is an argument, it will be used as a file name where a list of expression will be read.
 - Otherwise, it will ask you expressions through STDIN.

## Examples of execution
```sh
$ ./RPNapp
> Welcome to the RPN application. Type expresions (CTRL-D to end).
> 5 + 9
> 5 + 9 = 14
> 8 * (2 ^ 3)
> 8 * (2 ^ 3) = 64
$ ./RPNapp path/to/file.txt
> 5 + 9 = 14
> 8 * (2 ^ 3) = 64
```


