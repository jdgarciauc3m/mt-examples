#include <pthread.h>
#include <stdio.h>

void print_vec(double * vec, int size) {
  for (int i = 0; i < size; ++i) { printf("arg[%d] = %lf\n", i, vec[i]); }
  printf("\n");
}

void * print_args(void * args) {
  double * vec = (double *) args;
  printf("Thread %lu\n", pthread_self());
  print_vec(vec, 3);
  return nullptr;
}

int main() {
  pthread_t thread;
  double args[3] = {1, 2, 3};

  pthread_create(&thread, nullptr, print_args, (void *) args);
  pthread_join(thread, nullptr);

  return 0;
}
