#include <print>
#include <thread>

void add(int start, int end, int &result) {
  for (int i = start; i <= end; ++i) {
    result += i;
  }
}

int main() {
  int result1 = 0;
  int result2 = 0;
  {
    std::jthread th1(add, 0, 50, std::ref(result1));
    std::jthread th2(add, 51, 100, std::ref(result2));
  } // Implicit join

  std::println("Partial result 1 = {}", result1);
  std::println("Partial result 2 = {}", result2);
  int result = result1 + result2;
  std::println("result = {}", result);
}

