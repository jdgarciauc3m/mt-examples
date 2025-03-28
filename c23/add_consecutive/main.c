#include <stdio.h>
#include <pthread.h>

struct add_param
{
  int start;
  int end;
  int result;
};

void * add(void * arg) {
  auto param = (struct add_param *)arg;
  for (int i = param->start; i <= param->end; ++i) {
    param->result += i;
  }
  return nullptr;
}

int main() {
  pthread_t th1;
  struct add_param param1 = {0, 50, 0};
  pthread_create(&th1, nullptr, add, &param1);
  pthread_t th2;
  struct add_param param2 = {51, 100, 0};
  pthread_create(&th2, nullptr, add, &param2);

  pthread_join(th1, nullptr);
  pthread_join(th2, nullptr);

  int result = param1.result + param2.result;
  printf("Partial result 1 = %d\n", param1.result);
  printf("Partial result 2 = %d\n", param2.result);
  printf("result = %d\n", result);
}
