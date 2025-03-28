#include <print>    // Include the print header
#include <semaphore>// Include the semaphore header
#include <thread>

constexpr int buffer_size = 1024;
constexpr int num_elements = 100'000;


int main() {
  std::counting_semaphore<buffer_size> used_slots(0);           // Initially: no used slots
  std::counting_semaphore<buffer_size> empty_slots(buffer_size);// Initially: all slots empty
  std::array<int, buffer_size> buffer {};

  // Lambda expression with code for producer
  auto producer = [&]() {
    int pos = 0;
    for (int i = 0; i < num_elements; ++i) {
      int const data = i;// Generate data in some way
      empty_slots.acquire();
      buffer.at(pos) = data;
      pos = (++pos) % buffer_size;
      used_slots.release();
    }
  };

  // Lambda expression with code for consumer
  auto consumer = [&]() {
    int pos = 0;
    for (int i = 0; i < num_elements; ++i) {
      used_slots.acquire();
      int const data = buffer.at(pos);
      pos = (++pos) % buffer_size;
      empty_slots.release();
      std::println("{}", data);// Use std::print for output
    }
  };

  std::jthread const th_producer(producer);
  std::jthread const th_consumer(consumer);
}
