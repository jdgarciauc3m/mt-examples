# srvthr

This example shows how to use the `requesthdl` library to create a simple server
using threads on demand. The server listens for requests and spawns a new thread
to handle each request.

The application consecutively generates a number of requests. For each request
the following steps are performed:

1. Receive a request.
2. Spawn a new thread for processing and serving the request.

The application is implemented in C23 and C++23.

### Notes to the C23 version

- The main program just spawns a `receiver()` thread that will receive requests.
  The main thread will then wait for the receiver thread to finish.
- After receiving a request, the receiver thread will increment the number of
  active threads (`num_in_service`) and spawn a new thread to handle the
  request. The receiver thread will then wait for the spawned thread has made a
  local copy of the request to avoid data races. This is synchronized by using
  the `sem_request` semaphore.
- The `service()` thread copies the passed request and signals that the copy has
  been made to allow the receiver thread to continue (by using
  `sem_request`). The thread will then process the request and send a reply. The
  thread will then decrement and signal the receiver that the request has been
  processed by using
  `sem_nchildren`
- The receiver thread will wait for the spawned thread to finish by using
  `sem_nchildren`. This is done in a loop until there are no more child threads.

### Notes to the C++23 version

- The main program defines a lambda epxression that will be used to spawn a new thread
  for each request. The lambda expression will be passed to the `std::jthread`
  constructor. Note that the lambda expression takes a request object by 
  value. Consequently, the request object will be copied when the thread is spawned.
  The main program will then spawn and detach a receiver thread for each 
  request that it receives.
- Each time a thread is spawned the counter for number of threads is 
  incremented. On cleaning up while there are still threads running, the 
  main thread will wait for all threads to finish by using the semaphore `sem_nchildren`.