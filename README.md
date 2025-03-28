# mt-examples: Multithreading examples

This repo contains a number of very simple examples on multi-threading. It 
is a support material for the Operating Systems course at UC3M.

## Goals

This repo has multiple goals:

- Modern C: The examples use modern C as much as possible (to the best of my
  knowledge).
- C versus C++ comparison: Each example in C has a C++ counter example.

## Explanations for examples

Please see [documentation](doc/examples.md) for explanations of the examples.

## Building

The simplest way of building the examples is using cmake.

### Building with cmake on Docker

This repo contains a Dockerfile that can be used to build the examples. Note 
that in this case you will need to have Docker installed in your machine. 
The docker image contains everything that is needed to build the examples (GCC 14, 
cmake, ...).

From a command line where you have the Dockerfile, you can build the image 
and compile with:

```bash
docker build -t mt-builder .
docker run --rm -v $(pwd):/app -w /app mt-builder cmake --workflow --preset=all
docker run --rm -v $(pwd):/app -w /app mt-builder cmake --install out/build/default --prefix=out --config=Release
```

If you want to execute an example inside the docker container, you can do so.
For example, to run the `add_consecutive` example, you can do:

```bash
docker run --rm -v $(pwd):/app -w /app mt-builder out/bin/add_consecutive
```

### Building with cmake on Linux

In this case you will need a recent Linux distribution (e.g. Ubuntu 22.04) 
and the following packages installed:
- `cmake`.
- `gcc` version 14 or later.

From a command line, in the root of the repo, you can build the examples with:

```bash
cmake --workflow --preset=all
cmake --install out/build/default --prefix=out --config=Release
```

All the executable files shall be found on `out/bin` directory.

## How to contribute

There are multiple ways to contribute to this repo:

- **Open an issue**: If you find an example that is unclear, please open an issue.
- **Fix an example**: If you find a bug in an example, please fix it and open a pull
  request.
- **Fix an explanation**: If you find a bug in an explanation, please fix it and
  open a pull request.
- **Request an example**: If you want to see an example of a specific concept, please
  open an issue and request it.