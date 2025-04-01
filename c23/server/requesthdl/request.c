#include "request.h"
#include <stdio.h>

// POSIX headers
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static long request_id = 0;
static constexpr int max_receive_time = 5;
static constexpr long max_processing_iterations = 100'000'000;
static constexpr int max_send_time = 20;

void receive_request(request_t *req) {
  fprintf(stderr, "Receiving request...\n");
  req->id = request_id++;

    // Simulate receiving a request
  unsigned delay = (unsigned)(rand() % max_receive_time) ; // Simulate a random delay
  sleep(delay); // Simulate processing time

  fprintf(stderr, "Request received with ID: %ld after %d seconds\n", req->id, delay);
}

void process_request(request_t *req) {
  fprintf(stderr, "Processing request with ID: %ld\n", req->id);

  // Simulate processing time;
  for (int i=0; i<max_processing_iterations; i++) {
    req->data += i;
  }

  fprintf(stderr, "Request with ID: %ld processed\n", req->id);
}

void reply_request(request_t *req) {
  fprintf(stderr, "Replying to request with ID: %ld\n", req->id);

  // Simulate replying to a request
  unsigned delay = (unsigned)(rand() % max_send_time); // Simulate a random delay
  sleep(delay); // Simulate processing time

  fprintf(stderr, "Request with ID: %ld replied after %d seconds\n", req->id, delay);
}