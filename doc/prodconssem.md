# prodconssem

This example is a very basic producer-consumer program with two threads: a
producer thread and a consumer thread. The producer thread generates a sequence
of integers that are stored in a shared buffer, while the consumer thread takes
those integers from the buffer and prints them.

The synchronization between the producer and consumer threads is done using two
integer semaphores: `empty_slots` and `used_slots`. The `empty_slots` semaphore
is used to keep track of the number of empty slots in the buffer, while the
`used_slots` semaphore is used to keep track of the number of filled slots in
the buffer.

The producer thread waits on the `empty_slots` semaphore before adding an
integer to the buffer, and signals the `used_slots` semaphore after adding the
integer. The consumer thread waits on the `used_slots` semaphore before taking
an integer from the buffer, and signals the `empty_slots` semaphore after taking
the integer. This ensures that the producer does not add to a full buffer and
the consumer does not take from an empty buffer.

The program runs for a specified number of iterations, producing and consuming
integers in a loop. The producer thread generates integers starting from 0,
while the consumer thread simply prints the integers it consumes.

For this example 2 solutions are provided:

- [C23 prodconssem](../c23/prodconssem/main.c): C solution using pthreads.
- [C++23 prodconssem](../cpp23/prodconssem/main.cpp): C++ solution using
  `std::jthread`.