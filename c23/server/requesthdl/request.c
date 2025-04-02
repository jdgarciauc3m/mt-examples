#include "request.h"
#include <stdio.h>

// POSIX headers
#include <unistd.h>

static long request_id = 0;
static constexpr unsigned receive_times[] = {3, 2, 3, 1, 4};
static unsigned next_receive = 0;
static constexpr long max_processing_iterations = 100'000'000;
static constexpr unsigned send_times[] = { 6, 15, 15, 12, 1};
static unsigned next_send = 0;

void receive_request(request_t *req) {
  fprintf(stderr, "Receiving request...\n");
  req->id = request_id++;

  // Simulate receiving a request
  unsigned delay = receive_times[next_receive++ % (sizeof(receive_times) / sizeof(receive_times[0]))];
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
  unsigned delay = send_times[next_send++ % (sizeof(send_times) / sizeof(send_times[0]))];
  sleep(delay); // Simulate processing time

  fprintf(stderr, "Request with ID: %ld replied after %d seconds\n", req->id, delay);
}