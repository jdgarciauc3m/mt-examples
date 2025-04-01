#include <chrono>
#include <print>
#include <iostream>

// POSIX headers
#include <sched.h>
#include <wait.h>
#include <unistd.h>

// Server library
#include "request.hpp"

class process_manager {
public:
  void wait_finished_children() {
    std::println(std::cerr, "Waiting for finished children");
    pid_t pid = waitpid(-1, nullptr, WNOHANG);
    while (pid>0) {
      nchildren--;
      std::println(std::cerr, "Child {} terminated", pid);
      pid = waitpid(-1, nullptr, WNOHANG);
    }
  }

  void wait_all_children() {
    std::println(std::cerr, "Waiting for all children");
    while (nchildren > 0) {
      pid_t pid = waitpid(-1, nullptr, 0);
      if (pid > 0) {
        nchildren--;
        std::println(std::cerr, "Child {} terminated", pid);
      }
    }
  }

  void process_request(server::request& req) {
    pid_t pid = fork();
    if (pid == 0) {
      // Child process
      req.process();
      req.reply();
      exit(0);
    } else if (pid > 0) {
      // Parent process
      nchildren++;
      std::println(std::cerr, "Child {} created\n", pid);
    } else {
      perror("Cannot create child");
    }
  }

private:
  int nchildren = 0;
};

int main() {
  using namespace std::chrono;
  using namespace server;
  
  constexpr int max_requests = 5;
  process_manager manager;

  const auto start = high_resolution_clock::now();
  for (int i = 0; i < max_requests; i++) {
    request req = receive_request();
    manager.wait_finished_children();
    manager.process_request(req);
  }

  // Wait for all children to finish
  manager.wait_all_children();

  const auto stop = high_resolution_clock::now();
  const auto diff = duration_cast<seconds>(stop - start);
  std::println("Time: {}", diff.count());
}
