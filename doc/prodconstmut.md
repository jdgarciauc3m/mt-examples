#prodconsmut# prodconssem

This example is a very basic producer-consumer program with two threads: a
producer thread and a consumer thread. The producer thread generates a sequence
of integers that are stored in a shared buffer, while the consumer thread takes
those integers from the buffer and prints them.

The synchronization between the producer and consumer threads is done using a
mutex (`mtx`) and two condition variables: `not_empty` and `not_full`. The mutex
is used to protect access to the shared buffer, while the condition variables
are used to signal when the buffer is not empty or not full.

The program runs for a specified number of iterations, producing and consuming
integers in a loop. The producer thread generates integers starting from 0,
while the consumer thread simply prints the integers it consumes.

For this example 2 solutions are provided:

- [C23 prodconssem](../c23/prodconssem/main.c): C solution using pthreads.
- [C++23 prodconssem](../cpp23/prodconssem/main.cpp): C++ solution using
  `std::jthread`.

## Notes on the C23 version

The buffer and the syncrhonization variables are defined as global variables.
The thread logic are implemented in separate functions, and the main function
creates the corresponding threads and waits for them to finish.

## Notes on the C++23 version

The buffer and the syncrhonization variables are defined as local variables to
`main()`. The thread logic are implemented as lambdas, and the main function
creates threads using `std::jthread`, which automatically joins the threads when
they go out of scope.