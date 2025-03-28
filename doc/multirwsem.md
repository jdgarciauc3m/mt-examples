# multirwsem

This example is a basic readers-writers program with multiple threads. It 
uses multiple readers and multiple writers thread.
The synchronization between the reader and writer threads is done using two 
semaphores: `sem_readers` and `sem_mutex`. The `sem_readers` semaphore is 
used to keep mutual exclusion when updating the number of readers. The 
`sem_mutex` semaphore is used to keep mutual exclusion when accessing the 
shared data.

When the first reader arrives, it waits on the `sem_mutex` semaphore to 
ensure that no writers are currently writing. 

When the last reader leaves, it signals the `sem_mutex` semaphore to allow a 
writer to proceed.

When a writer arrives, it waits on the `sem_mutex` semaphore to ensure that 
no readers or writers are currently accessing the shared data. 

When the writer is done, it signals the `sem_mutex` semaphore to allow 
another reader or writer to proceed.

For this example 2 solutions are provided:
- [C23 multirewsem](../c23/multirwsem/main.c): C solution using pthreads.
- [C++23 multirewsem](../cpp23/multirwsem/main.cpp): C++ solution using
  `std::jthread`.