# requesthdl

This component is a small library to simulate request handling. It is designed
to provide a very simple implementation with three operatrions:

1. Receive a request.
2. Process a request.
3. Send a response.

There are two versions of the library:

- A C23 version.
- A C++23 version.

The library is thread-safe.

## Library requesthdl (C23 version)

The header file [requesthdl.h](../c23/server/requesthdl/request.h) contains the
definition of the request type with a number of fields.

Five functions are provided:

- `request_generator_init()`: This function initializes the request generator.
  The function must be invoked before any other function in the library.
- `request_generator_cleanup()`: This function cleans up the request generator.
  The function must be invoked after all other functions in the library have
  been invoked.
- `receive_request()`: This function simulates the reception of a request. It
  takes a pointer to a request and simulates some I/O time.
- `process_request`: This function simulates the processing of a request. It
  takes a pointer to a request and performs some computation using the CPU.
- `reply_request`: This function simulates the sending of a response. It takes a
  pointer to a request and simulates some I/O time.

### Usage notes

- Programs should invoke `request_generator_init()` before any other function in
  the library. This function initializes the request generator and must be
  invoked only once.
- Programs should invoke `request_generator_cleanup()` after all other functions
  in the library have been invoked. This function cleans up the request
  generator and must be invoked only once.

### Implementation notes

Implementation is provided in the
file [requesthdl.c](../c23/server/requesthdl/request.c).

- When receiving a request IDs are assigned consecutively.
- I/O time si simulated using POSIX `sleep()` system call which will block the
  calling thread for a given number of seconds.
- The duration of time spent in I/O is generated using a fixed sequence of
  values in a round-robin fashion. There is one fixed sequence of delay values
  for receiving requests and one for sending responses.
- The processing time is simulated using a busy loop that will consume CPU time
  for a given number of iterations.

## Library requesthdl (C++23 version)

The header file [requesthdl.hpp](../cpp23/server/requesthdl/request.hpp)
contains the definition of the `request` type.

The following operations are provided:

- `receive_request()`: This function simulates the reception of a request. It
  simulates some I/O time and returns a request object.
- `req.process_request()`: This function simulates the processing of a request.
  It performs some computation using the CPU and updates the request object
  `req`.
- `req.reply_request()`: This function simulates the sending of a response. It
  simulates some I/O time.

### Implementation notes

Implementation is provided in the
file [requesthdl.cpp](../cpp23/server/requesthdl/request.cpp).

- When receiving a request IDs are assigned consecutively.
- I/O time si simulated using C++20 `std::this_thread::sleep_for()` which will
  block the calling thread for a given number of seconds.
- The duration of time spent in I/O is generated using a fixed sequence of
  values in a round-robin fashion. There is one fixed sequence of delay values
  for receiving requests and one for sending responses.
- The processing time is simulated using a busy loop that will consume CPU time
  for a given number of iterations.