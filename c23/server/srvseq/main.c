#include "request.h"

#include <stdio.h>
#include <time.h>

int main() {
  constexpr int max_requests = 5;
  request_t req;

  time_t t1 = time(nullptr);
  for (int i = 0; i < max_requests; i++) {
    receive_request(&req);
    process_request(&req);
    reply_request(&req);
  }
  time_t t2 = time(nullptr);
  double diff = difftime(t2, t1);
  printf("Time: %lf", diff);
}
