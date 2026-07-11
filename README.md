# cpp06

42 C++ Module 06 focuses on casting, serialization, and runtime type identification in C++98.

## Overview

This repository contains three independent exercises:

- `ex00`: scalar conversion from string literals to `char`, `int`, `float`, and `double`
- `ex01`: serialization and deserialization of a `Data` pointer using `uintptr_t`
- `ex02`: runtime type identification with `dynamic_cast`

Each exercise has its own `Makefile` and builds its own executable.

## Requirements

- C++98
- `make`
- a compiler compatible with the project flags `-Wall -Wextra -Werror`

## Build And Run

### ex00 - Scalar Converter

Build:

```bash
cd ex00
make
```

Run:

```bash
./scalar_converter <literal>
```

Example:

```bash
./scalar_converter 42
```

### ex01 - Serializer

Build:

```bash
cd ex01
make
```

Run:

```bash
./serializer
```

This exercise demonstrates how a pointer can be converted to an integer and back without losing the original address.

### ex02 - Dynamic Cast

Build:

```bash
cd ex02
make
```

Run:

```bash
./dynamic_cast
```

This exercise generates derived objects at runtime and identifies them through both pointers and references.

## Clean Up

Each exercise supports the usual make targets:

```bash
make clean
make fclean
make re
```

## Project Structure

```text
cpp06/
├── ex00/
├── ex01/
└── ex02/
```
