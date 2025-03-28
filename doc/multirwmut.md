# multirwmut

This example is a basic readers-writers program with multiple threads. It
uses multiple readers and multiple writers thread.
The synchronization between the reader and writer threads is done using two
mutexes: `readers_mutex` and `data_mutex`. 

The `readers_mutex` mutex is used to keep mutual exclusion when updating the 
number of readers. The `data_mutex` mutex is used to keep mutual exclusion 
when accessing the shared data.

When the first reader arrives, it locks the `readers_mutex` mutex to ensure 
that now writers are currently writing. 

When the last reader leaves, it unlocks the `readers_mutex` mutex to allow a 
writer to proceed.

When a writer arrives, it locks the `data_mutex` mutex to ensure that no 
readers or writers are currently accessing the shared data.

When the writer is done, it unlocks the `data_mutex` mutex to allow
another reader or writer to proceed.

For this example 2 solutions are provided:
- [C23 multirwmut](../c23/multirwmut/main.c): C solution using pthreads.
- [C++23 multirwmut](../cpp23/multirwmut/main.cpp): C++ solution using
  `std::jthread`.