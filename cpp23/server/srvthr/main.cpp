#include <chrono>
#include <print>
#include <thread>

// Server library
#include "request.hpp"


int main() {
  using namespace std::chrono;
  auto start = std::chrono::high_resolution_clock::now();

  std::counting_semaphore sem_nchildren {0};
  auto service = [&](server::request req) {
    std::println("Starting service for ID: {}", req.id());
    req.process();
    req.reply();
    sem_nchildren.release();
    std::println("Ending service for ID: {}", req.id());
  };


  constexpr int max_requests = 5;
  int num_in_service = 0;

  for (int i = 0; i < max_requests; i++) {
    auto req = server::receive_request();
    num_in_service++;
    std::jthread service_th {service, req};
    service_th.detach();
  }
  while (num_in_service > 0) {
    std::println("Waiting for children");
    sem_nchildren.acquire();
    num_in_service--;
    std::println("Child terminated");
  }

  const auto stop = high_resolution_clock::now();
  const auto diff = duration_cast<seconds>(stop - start);
  std::println("Time: {}", diff.count());
}
