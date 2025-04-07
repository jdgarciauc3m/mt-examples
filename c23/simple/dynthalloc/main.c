#include <bits/pthreadtypes.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t parse_args(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr,"Usage: dynth number\n");
    exit(EXIT_FAILURE);
  }
  char * end;
  size_t n = strtoul(argv[1], &end, 10);
  if (errno != 0 || *end != '\0') {
    fprintf(stderr, "Invalid number: %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  return n;
}

void * task(void * ) {
  pthread_t id = pthread_self();
  printf("Start thread %ld\n", id);
  sleep(1);
  printf("Stop thread %ld\n", id);
  return nullptr;
}

int main(int argc, char *argv[]) {
  size_t n = parse_args(argc, argv);
  printf("num threads = %ld\n", n);

  pthread_t * threads = calloc(n, sizeof(pthread_t));
  for (size_t i = 0; i < n; i++) {
    pthread_create(&threads[i], nullptr, task, nullptr);
  }

  for (size_t i = 0; i < n; i++) {
    pthread_join(threads[i], nullptr);
  }
  free(threads);
  printf("All threads finished\n");
}
