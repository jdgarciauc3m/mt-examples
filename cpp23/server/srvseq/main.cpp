#include "request.hpp"

#include <chrono>
#include <print>


int main() {
  using namespace std::chrono;
  using namespace server;
  constexpr int max_requests = 5;

  const auto start = high_resolution_clock::now();
  for (int i = 0; i < max_requests; i++) {
    auto req = receive_request();
    req.process();
    req.reply();
  }
  const auto stop = high_resolution_clock::now();
  const auto diff = duration_cast<seconds>(stop - start);
  std::println("Time: {}", diff.count());
}
