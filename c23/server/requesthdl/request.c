#include "request.h"
#include <stdio.h>

// POSIX headers
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static long request_id = 0;

void receive_request(request_t *req) {
  fprintf(stderr, "Receiving request...\n");
  req->id = request_id++;

    // Simulate receiving a request
  unsigned delay = (unsigned)(rand() % 5) ; // Simulate a random delay
  sleep(delay); // Simulate processing time

  fprintf(stderr, "Request received with ID: %ld after %d seconds\n", req->id, delay);
}

void reply_request(request_t *req) {
  fprintf(stderr, "Replying to request with ID: %ld\n", req->id);

  // Simulate processing time;
  for (int i=0; i<100000000; i++) {
    req->data += i;
  }

  // Simulate replying to a request
  unsigned delay = (unsigned)(rand() % 20); // Simulate a random delay
  sleep(delay); // Simulate processing time

  fprintf(stderr, "Request with ID: %ld replied after %d seconds\n", req->id, delay);
}