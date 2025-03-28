# add_consecutive

In this example, we spawn two threads that add consecutive numbers in two
separate ranges, and then print the result. That is, the first thread add the
integer numbers from 0 to 50 and the second thread adds the integer numbers from
51 to 100.

For this example 3 solutions are provided:

- [C23 add_consecutive](../c23/add_consecutive/main.c): C solution using
  pthreads.
- [C++23 add_consecutive](../cpp23/add_consecutive/main.cpp): C++ solution using
  std::jthread.
- [C++23 add_consecutive_async](../cpp23/add_consecutive_async/main.cpp): C++
  solution using std::async.