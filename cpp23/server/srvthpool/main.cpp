#include <print>

// Server library
#include "request.hpp"

#include <condition_variable>
#include <mutex>
#include <thread>

class request_buffer {
public:
  request_buffer() = default;
  request_buffer(const request_buffer&) = delete;
  request_buffer& operator=(const request_buffer&) = delete;

  void add_request(server::request const & req) {
    std::println("Adding request");
    std::unique_lock lock{mtx};
    not_full.wait(lock, [this] { return num_elements < buffer_size; });
    buffer.at(next_put) = req;
    next_put = (next_put + 1) % buffer_size;
    num_elements++;
    not_empty.notify_one();
  }

  server::request get_request() {
    std::println("Removing request");
    std::unique_lock lock{mtx};
    not_empty.wait(lock, [this] { return num_elements > 0; });
    auto req = buffer.at(next_get);
    next_get = (next_get + 1) % buffer_size;
    num_elements--;
    not_full.notify_one();
    return req;
  }

private:
  static constexpr int buffer_size = 128;
  std::array<server::request, buffer_size> buffer{};
  std::size_t num_elements = 0;
  std::size_t next_put = 0;
  std::size_t next_get = 0;
  std::mutex mtx;
  std::condition_variable not_empty;
  std::condition_variable not_full;
};


int main() {
  using namespace std::chrono;
  auto start = std::chrono::high_resolution_clock::now();

  request_buffer buffer{};
  std::mutex mutex_end;
  bool end = false;

  auto service = [&]() {
    for (;;) {
      std::unique_lock lock{mutex_end};
      if (end) {
        std::println("Finishing service");
        return;
      }
      lock.unlock();
      auto req = buffer.get_request();
      std::println("Starting service for ID: {}", req.id());
      req.process();
      req.reply();
      std::println("Ending service for ID: {}", req.id());
    }
  };

  auto receiver = [&] {
    constexpr int max_requests = 5;
    for (int i = 0; i < max_requests; i++) {
      auto req = server::receive_request();
      std::println("Adding request");
      buffer.add_request(req);
    }
    std::lock_guard const lock{mutex_end};
    end = true;
  };

  {
  std::jthread const receiver_thread{receiver};
  std::vector<std::jthread> pool;
  constexpr int pool_size = 5;
  for (int i = 0; i < pool_size; ++i) {
    pool.emplace_back(service);
  }
}


  const auto stop = high_resolution_clock::now();
  const auto diff = duration_cast<seconds>(stop - start);
  std::println("Time: {}", diff.count());
}
