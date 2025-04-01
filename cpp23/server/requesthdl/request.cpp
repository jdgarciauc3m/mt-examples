
#include "request.hpp"

#include <iostream>
#include <print>
#include <random>
#include <thread>

namespace server {
  namespace {
    constexpr int max_receive_time = 5;
    constexpr long max_processing_iterations = 100'000'000;
    constexpr int max_send_time = 20;

    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    int request_id = 0;
    std::minstd_rand generator;
    std::uniform_int_distribution<unsigned int> receive_time {0, max_receive_time};
    std::uniform_int_distribution<unsigned int> send_time {0, max_send_time};
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
  }// namespace

  request receive_request() {
    std::print(std::cerr, "Receiving request");

    request req {request_id++};

    // Simulate receiving a request
    unsigned delay = receive_time(generator);                // Simulate a random delay
    std::this_thread::sleep_for(std::chrono::seconds(delay));// Simulate receive time

    std::print(stderr, "Request received with ID: {} after {} seconds\n", req.id(), delay);
    return req;
  }

  void request::process() {
    std::println(std::cerr, "Processing request with ID: {}", id());

    // Simulate processing time;
    for (int i = 0; i < max_processing_iterations; i++) { update_data(i); }

    std::println(std::cerr, "Request with ID: {} processed", id());
  }

  void request::reply() const {
    std::println(std::cerr, "Replying to request with ID: {}", id());

    // Simulate replying to a request
    auto delay = send_time(generator);                       // Simulate a random delay
    std::this_thread::sleep_for(std::chrono::seconds(delay));// Simulate send time

    std::println(std::cerr, "Request with ID: {} replied after {} seconds", id(), delay);
  }

}// namespace server