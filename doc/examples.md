# Examples

A number of examples are provided in this repository.

Each example is as simple as possible, and is designed to illustrate a specific
concept in multithreading.

For each example, there is a C version and a C++ version.

The C version is designed to be as simple as possible, but using modern C as
much as possible.

The C++ version tries to show the same concept in a way that is more type safe,
using C++23 features where possible.

List of examples:

- [add_consecutive](add_consecutive.md): Spawns two threads that add consecutive
  numbers in two separate variables, and then prints the result.
- Producer consumer.
    - [prodconssem](prodconssem.md): A producer-consumer example using
      semaphores.
    - [prodconsmut](prodconsmut.md): A producer-consumer example using mutexes
      and condition variables.
- Readers-writers.
    - [multirwsem](multirwsem.md): A readers-writers example
      using semaphores.
    - [multirwmut](multirwmut.md): A readers-writers example
      using mutexes and condition variables.