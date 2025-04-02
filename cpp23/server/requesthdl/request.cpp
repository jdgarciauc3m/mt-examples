
#include "request.hpp"

#include <iostream>
#include <mutex>
#include <print>
#include <thread>

namespace server {
  namespace {
    constexpr long max_processing_iterations = 100'000'000;
    constexpr std::array<unsigned,5> receive_times {3, 2, 3, 1, 4};
    constexpr std::array<unsigned,5> send_times { 6, 15, 15, 12, 1};
    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    int request_id = 0;
    unsigned next_receive = 0;
    unsigned next_send = 0;
    std::mutex generator_mutex;
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

  }// namespace

  request receive_request() {
    std::println(std::cerr, "Receiving request");

    request req {request_id++};

    // Simulate receiving a request
    std::unique_lock lock{generator_mutex};
    unsigned delay = receive_times.at(next_receive);
    next_receive = (next_receive + 1) % receive_times.size();
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(delay));// Simulate receive time

    std::println(std::cerr, "Request received with ID: {} after {} seconds", req.id(), delay);
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
    std::unique_lock lock{generator_mutex};
    unsigned delay = send_times.at(next_send);
    next_send = (next_send + 1) % send_times.size();
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(delay));// Simulate send time

    std::println(std::cerr, "Request with ID: {} replied after {} seconds", id(), delay);
  }

}// namespace server