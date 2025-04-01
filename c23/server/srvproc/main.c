#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// POSIX headers
#include <sched.h>
#include <wait.h>
#include <unistd.h>

#include "request.h"


int main() {
  constexpr int max_requests = 5;
  int nchildren = 0;

  time_t t1 = time(nullptr);
  for (int i = 0; i < max_requests; i++) {
    request_t req;
    receive_request(&req);

    pid_t pid;
    do {
      fprintf(stderr, "Waiting for children\n");
      pid = waitpid(-1, nullptr, WNOHANG);
      if (pid>0) {
        nchildren--;
        fprintf(stderr, "Child %d terminated\n", pid);
      }
    } while (pid>0);

    pid = fork();
    if (pid == 0) {
      // Child process
      process_request(&req);
      reply_request(&req);
      exit(0);
    } else if (pid > 0) {
      // Parent process
      nchildren++;
      fprintf(stderr, "Child %d created\n", pid);
    } else {
      perror("Cannot create child");
    }
  }

  // Wait for all children to finish
  while (nchildren > 0) {
    fprintf(stderr, "Waiting for children\n");
    pid_t pid = waitpid(-1, nullptr, WNOHANG);
    if (pid > 0) {
      nchildren--;
      fprintf(stderr, "Child %d terminated\n", pid);
    }
  }

  time_t t2 = time(nullptr);
  double diff = difftime(t2, t1);
  printf("Time: %lf", diff);
}