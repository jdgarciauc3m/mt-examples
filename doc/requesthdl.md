# requesthdl

This component is a small library to simulate request handling. It is 
designed to provide a very simple implementation with three operatrions:

1. Receive a request.
2. Process a request.
3. Send a response.

There are two versions of the library:

- A C23 version.
- A C++23 version.

## Library requesthdl (C23 version)

The header file `requesthdl.h` contains the definition of the request type 
with a number of fields.

Three functions are provided:
- `receive_request`: This function simulates the reception of a request. It 
  takes a pointer to a request and simulates some I/O time.
- `process_request`: This function simulates the processing of a request. It 
  takes a pointer to a request and performs some computation using the CPU.
- `reply_request`: This function simulates the sending of a response. It 
  takes a pointer to a request and simulates some I/O time.

### Notes

- When receiving a request IDs are assigned consecutively.
- I/O time si simulated using POSIX `sleep()` system call which  will block the
  calling thread for a given number of seconds.
- The duration of time spent in I/O is generated using `rand()` function. 
  Note that this function is not thread-safe. Additionally, the function has 
  a slight bias towards smaller numbers.
- The processing time is simulated using a busy loop that will consume CPU time
  for a given number of iterations.

## Library requesthdl (C++23 version)

The header file `requesthdl.hpp` contains the definition of the request type.

The following operations are provided:

- `receive_request()`: This function simulates the reception of a request. It 
  simulates some I/O time and returns a request object.
- `req.process_request()`: This function simulates the processing of a request. It 
  performs some computation using the CPU and updates the request object `req`.
- `req.reply_request()`: This function simulates the sending of a response. It 
  simulates some I/O time.

### Notes
- When receiving a request IDs are assigned consecutively.
- I/O time si simulated using C++20 `std::this_thread::sleep_for()` which will 
  block the calling thread for a given number of milliseconds.
- The duration of time spent in I/O is generated using `std::minstd_rand` type. 
- The processing time is simulated using a busy loop that will consume CPU time
  for a given number of iterations.