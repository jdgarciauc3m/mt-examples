#include <array>
#include <condition_variable>
#include <mutex>
#include <print>
#include <thread>

constexpr int buffer_size = 1024;
constexpr int num_elements = 100'000;

int main() {
  std::array<int, buffer_size> buffer {};
  int n_elements = 0;

  std::mutex mtx;
  std::condition_variable not_full;
  std::condition_variable not_empty;

  auto producer = [&]() {
    std::size_t pos = 0;
    for (int i = 0; i < num_elements; i++) {
      int data = i;                      // Produce a data item
      std::println("producing {}", data);// Use std::println for output
      std::unique_lock<std::mutex> lock(mtx);
      not_full.wait(lock, [&] { return n_elements < buffer_size; });
      buffer.at(pos) = data;
      pos = (pos + 1) % buffer_size;
      n_elements++;
      not_empty.notify_one();
    }
  };

  auto consumer = [&]() {
    std::size_t pos = 0;
    for (int i = 0; i < num_elements; i++) {
      std::unique_lock<std::mutex> lock(mtx);
      not_empty.wait(lock, [&] { return n_elements > 0; });
      int data = buffer.at(pos);
      pos = (pos + 1) % buffer_size;
      n_elements--;
      not_full.notify_one();
      std::println("consuming {}", data);// Use std::println for output
    }
  };

  std::jthread const th_producer(producer);
  std::jthread const th_consumer(consumer);
}
