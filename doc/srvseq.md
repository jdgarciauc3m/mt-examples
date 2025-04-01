# srvseq

This example uses the `requesthdl` library to simulate a sequential server.

The application consecutively generates a number of requests. For each 
request the following steps are performed:

1. Receive a request.
2. Process a request.
3. Send a response.

Note that the steps are performed sequentially, which is problematic:

- The server is blocked while waiting for a request.
- The server is blocked while processing a request.
- The server is blocked while sending a response.

The application is implemented in C23 and C++23.

### Notes

- The C23 and C++23 versions are similar but slightly differ in results 
  because they use different random number generators.