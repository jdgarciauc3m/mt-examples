# srvproc

This example uses the `requesthdl` library to simulate a multi-process server.
Every time a new request is received, a new process is created to handle the
request, while the main process continues to listen for new requests. The server
is implemented using the `fork()` system call, which is a POSIX system call that
creates a new process by duplicating the calling process. The new process is a
child of the calling process, and it has its own memory space. The child process
can then handle the request and send a response back to the main process.

The application consecutively generates a number of requests. For each request
the following steps are performed:

1. Receive a request.
2. Spawn a new process for processing and serving the request.

The application is implemented in C23 and C++23.

### Notes to the C23 version

- After recieving a request, the process first checks if there are any finished
  child processes. To do so, it waits (`waitpid()`) in a non-blocking way
  (`WNOHANG`) for any child (`-1` as pid parameter).
- The process then forks a new child process to handle the request. The child
  process will call `process_request()` and `reply_request()`, while the parent
  process will continue to listen for new requests.
- When no more request are exptcted, the parent process will call `waitpid()`
  with `0` as third parameter (blocking wait) to clean up any remaining child
  processes. This is done in a loop until there are no more child processes.

### Notes to the C++23 version

- Process mangement is encapsulated in a process manager class. The class
  provides a method to spawn a new process for a request. It also provides 
  member functions for non-blocking and blocking waits for child processes.
