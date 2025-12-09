# advent-of-code-cpp

[Advent of Code](https://adventofcode.com/) C++ 解答.

## 语言

[English (United States)](./README.md) | [简体中文（中国大陆）](./README.zh-CN.md)

## 源代码

源代码均位于 `src/` 文件夹内.

具体来说，`<yyyy>` 年 Day `<d>` 的解答是 `src/year<yyyy>/day<d>/main.cc` 文件中的 `Solve` 函数。例如，`2025` 年 Day `1` 的解答在文件 [`src/year2025/day1/main.cc`](src/year2025/day1/main.cc) 中.

## 构建方式

### 准备

+ Linux 操作系统
+ 完整支持 C++23 的 C++ 编译器 (GCC 14、Clang 19 或更高版本)

### 构建

运行：

```bash
$ ./autogen.sh
$ CXX=<compiler> ./configure
$ make -j$(nproc)
```

`<compiler>` 是你使用的编译器，例如 `g++-14` 或 `clang++-19`。以 `g++-14` 为例：`CXX=g++-14 ./configure`.

## 运行方法

```bash
$ ./build/bin/year<yyyy>/day<d> -p <part> -f <path>
```

`<yyyy>` 是年份，`<d>` 是天数，`<p>` 是 Part 序号（默认为 1），`<path>` 是输入文件的路径. 例如：`./build/bin/year2025/day1 -p 1 -f ./data/2025/day1/input.txt`.
