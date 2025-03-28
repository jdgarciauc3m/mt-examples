#include <future>
#include <print>

int add(int start, int end) {
  int result = 0;
  for (int i = start; i <= end; ++i) {
    result += i;
  }
  return result;
}

int main() {
  auto f1 = std::async(std::launch::async, add, 0, 50);
  auto f2 = std::async(std::launch::async, add, 51, 100);

  auto r1 = f1.get();
  auto r2 = f2.get();
  std::println("Partial result 1 = {}", r1);
  std::println("Partial result 2 = {}", r2);
  std::println("result = {}", r1+r2);
}

