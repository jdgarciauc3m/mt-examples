
#include "request.hpp"

#include <iostream>
#include <print>
#include <random>

// POSIX headers
#include <unistd.h>

namespace server {
  namespace {
    constexpr unsigned max_send_time = 5;
    constexpr unsigned max_recv_time = 20;
    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    int request_id = 0;
    std::minstd_rand0 generator;
    std::uniform_int_distribution<unsigned int> receive_time{0, max_recv_time};
    std::uniform_int_distribution<unsigned int> send_time{0, max_send_time};
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
  }// namespace

  request receive_request() {
    std::print(std::cerr, "Receiving request");

    request req {request_id++};

    // Simulate receiving a request
    unsigned delay = receive_time(generator);// Simulate a random delay
    sleep(delay);                            // Simulate processing time

    std::print(stderr, "Request received with ID: {} after {} seconds\n", req.id(), delay);
    return req;
  }

  void reply_request(request & req) {
    std::println(std::cerr, "Replying to request with ID: {}", req.id());

    // Simulate processing time;
    constexpr int num_iterations = 100'000'000;
    for (int i=0; i<num_iterations; i++) {
      req.update_data(i);
    }

    // Simulate replying to a request
    auto delay = send_time(generator); // Simulate a random delay
    sleep(delay); // Simulate processing time

    std::println(std::cerr, "Request with ID: {} replied after {} seconds", req.id(), delay);

  }

}// namespace server