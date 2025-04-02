# srvthpool

This example shows how to use the `requesthdl` library to create a simple server
using a thread pool. The server listens for requests and puts received 
requests in a buffer. All threads in the thread pool will then process the requests
as they become available.

The application consecutively generates a number of requests. For each request
the following steps are performed:

1. Receive a request.
2. Put the request in a buffer.

The application is implemented in C23 and C++23.

