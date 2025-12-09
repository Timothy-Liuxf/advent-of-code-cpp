# advent-of-code-cpp

C++ solution to [Advent of Code](https://adventofcode.com/)

## Languages

[English (United States)](./README.md) | [简体中文（中国大陆）](./README.zh-CN.md)

## How to Build

### Prerequisite

+ Linux Operating System
+ C++ compiler supporting fully C++23 (GCC 14, Clang 19 or higher versions)

### Build

Run:

```bash
$ ./autogen.sh
$ CXX=<compiler> ./configure
$ make -j$(nproc)
```

where `<compiler>` is the compiler you want to use, such as `g++-14` or `clang++-19`. Take `g++-14` as an example: `CXX=g++-14 ./configure`.

## How to Run

```bash
$ ./build/bin/year<yyyy>/day<d> -f <path>
```

where `<yyyy>` is the year, `<d>` is the number of the day, and `<path>` is the path to the input file. For example: `./build/bin/year2025/day1 -f ./data/2025/day1/input.txt`
