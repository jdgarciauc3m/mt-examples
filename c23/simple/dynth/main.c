#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int parse_args(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr,"Usage: dynth number\n");
    exit(EXIT_FAILURE);
  }
  return atoi(argv[1]);
}

void * task(void * ) {
  pthread_t id = pthread_self();
  printf("Start thread %ld\n", id);
  sleep(1);
  printf("Stop thread %ld\n", id);
  return nullptr;
}

int main(int argc, char *argv[]) {
  int n = parse_args(argc, argv);
  printf("num threads = %d\n", n);

  pthread_t threads[n];
  for (int i = 0; i < n; i++) {
    pthread_create(&threads[i], nullptr, task, nullptr);
  }

  for (int i = 0; i < n; i++) {
    pthread_join(threads[i], nullptr);
  }
  printf("All threads finished\n");
}
