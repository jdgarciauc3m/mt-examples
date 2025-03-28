#include <print>
#include <semaphore>
#include <thread>
#include <vector>

constexpr int max_readers = 5;
constexpr int max_writers = 4;
constexpr int initial_value = 42;

int main() {
  int data = initial_value;
  int num_readers = 0;

  std::binary_semaphore sem_readers {1};
  std::binary_semaphore sem_mutex {1};

  auto reader = [&]() {
    sem_readers.acquire();
    num_readers++;
    if (num_readers == 1) { sem_mutex.acquire(); }
    sem_readers.release();

    std::println("Reading data = {}", data);

    sem_readers.acquire();
    num_readers--;
    if (num_readers == 0) { sem_mutex.release(); }
    sem_readers.release();
  };

  auto writer = [&]() {
    sem_mutex.acquire();
    data += 2;
    std::println("Writer is writing data = {}", data);
    sem_mutex.release();
  };

  std::vector<std::jthread> readers;
  for (int i = 0; i < max_readers; ++i) { readers.emplace_back(reader); }
  std::vector<std::jthread> writers;
  for (int i = 0; i < max_writers; ++i) { writers.emplace_back(writer); }

}
