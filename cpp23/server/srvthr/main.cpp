#include <thread>
#include <chrono>
#include <print>

// Server library
#include "request.hpp"


int main() {
  using namespace std::chrono;
  auto start = std::chrono::high_resolution_clock::now();

  auto service = [](server::request req) {
    std::println("Starting service for ID: {}", req.id());
    req.process();
    req.reply();
    std::println("Ending service for ID: {}", req.id());
  };

  auto receiver = [&] {
    constexpr int max_requests = 5;
    int num_in_service = 0;

    std::vector<std::jthread> service_threads;
    for (int i = 0; i < max_requests; i++) {
      auto req = server::receive_request();
      num_in_service++;
      service_threads.emplace_back(service, req);
    }

  };

  std::jthread receiver_th{receiver};
  receiver_th.join();

  const auto stop = high_resolution_clock::now();
  const auto diff = duration_cast<seconds>(stop - start);
  std::println("Time: {}", diff.count());
}


