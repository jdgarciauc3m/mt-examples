#include <mutex>
#include <print>
#include <thread>
#include <vector>

constexpr int max_readers = 5;
constexpr int max_writers = 4;
constexpr int initial_value = 42;

int main() {
  int data = initial_value;
  int num_readers = 0;
  std::mutex readers_mutex;
  std::mutex data_mutex;

  auto reader = [&] {
    {
      std::lock_guard const lock {readers_mutex};
      num_readers++;
      if (num_readers == 1) { data_mutex.lock(); }
    }

    std::println("Reading data = {}", data);

    {
      std::lock_guard const lock {readers_mutex};
      num_readers--;
      if (num_readers == 0) { data_mutex.unlock(); }
    }
  };

  auto writer = [&] {
    std::lock_guard const lock {readers_mutex};
    data += 2;
    std::println("Writer is writing data = {}", data);
  };

  std::vector<std::jthread> readers;
  for (int i = 0; i < max_readers; i++) { readers.emplace_back(reader); }
  std::vector<std::jthread> writers;
  for (int i = 0; i < max_writers; i++) { writers.emplace_back(writer); }
}