#include "request.h"

#include <stdio.h>
#include <time.h>

int main() {
  constexpr int max_requests = 5;

  time_t t1 = time(nullptr);
  request_generator_init();
  for (int i = 0; i < max_requests; i++) {
    request_t req;
    receive_request(&req);
    process_request(&req);
    reply_request(&req);
  }
  request_generator_cleanup();
  time_t t2 = time(nullptr);
  double diff = difftime(t2, t1);
  printf("Time: %lf", diff);
}
