# ParaCL language interpreter

## Description
This repository implements the C like language interpreter. The language consists of basic operations that make it Turing complete. Only `int` type variables are supported. Example of code:

```cpp
n = ?;         //console input

if (n <= 0){

    print 0;
}

while (n > 0){

    print n;
    n = n - 1;
}
```

Implemented check of syntax and variables definitions:

```cpp
error_var = 3
var = 1;
error = 1 + - 2;

if (undef_var > 0){

    print 3;
}
```

Result:

```Bash
syntax error, unexpected variable, expecting ; [2, 1]
var = 1;
^
syntax error, unexpected -, expecting ( or ? or number or variable [3, 13]
error = 1 + - 2;
~~~~~~~~~~~~^
identifier "undef_var" is undefined [5]
```

## Implementation
For lexical analysis, Bison and Flex code generators are used. Files to generate are in `./bin`.

To work with the abstract syntax tree, a request system is used. Description of this system located in `./src/frontend/headers`.

## Build
Before building the program:

```Bash
mkdir build 
cd ./build
cmake .
```
There are two build targets in the project:

```Bash 
make ParaCL
make Tests
```

1. ParaCL - build a program to work with ParaCL code 
2. Tests - buuld tests for interpreter

The command line arguments contain a file with the source text of the ParaCL language program.



