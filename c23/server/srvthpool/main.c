#include <stdio.h>

// POSIX headers
#include <pthread.h>

// Server library
#include "request.h"

constexpr int max_buffer = 128;
request_t buffer[max_buffer];
int num_elements = 0;
int pos_service = 0;
pthread_mutex_t mutex_buffer;
pthread_cond_t not_full;
pthread_cond_t not_empty;

pthread_mutex_t mutex_mend;
int end = 0;

void * receiver(void *) {
  constexpr int max_requests = 5;
  for (int i = 0; i < max_requests; ++i) {
    request_t req;
    receive_request(&req);
    pthread_mutex_lock(&mutex_buffer);
    while (num_elements == max_buffer) {
      pthread_cond_wait(&not_full, &mutex_buffer);
    }
    buffer[pos_service] = req;
    pos_service = (pos_service + 1) % max_buffer;
    num_elements++;
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex_buffer);
  }
  fprintf(stderr, "Finishing receiver\n");

  pthread_mutex_lock(&mutex_mend);
  end = 1;
  pthread_mutex_unlock(&mutex_mend);

  pthread_mutex_lock(&mutex_buffer);
  pthread_cond_broadcast(&not_empty);
  pthread_mutex_unlock(&mutex_buffer);

  fprintf(stderr, "Finished receiver\n");
  return nullptr;
}

void * service(void*) {
  for (;;) {
    pthread_mutex_lock(&mutex_buffer);
    while (num_elements == 0) {
      pthread_mutex_lock(&mutex_mend);
      if (end) {
        pthread_mutex_unlock(&mutex_mend);
        pthread_mutex_unlock(&mutex_buffer);
        fprintf(stderr, "Finishing service\n");
        pthread_exit(nullptr);
      }
      pthread_mutex_unlock(&mutex_mend);
      pthread_cond_wait(&not_empty, &mutex_buffer);
    }
    fprintf(stderr, "Serving position %d\n", pos_service);
    request_t req = buffer[pos_service];
    pos_service = (pos_service + 1) % max_buffer;
    num_elements--;
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex_buffer);
    reply_request(&req);
  }
  return nullptr;
}

int main() {
  time_t t1 = time(nullptr);

  request_generator_init();

  pthread_mutex_init(&mutex_buffer, nullptr);
  pthread_cond_init(&not_full, nullptr);
  pthread_cond_init(&not_empty, nullptr);
  pthread_mutex_init(&mutex_mend, nullptr);

  pthread_t receiver_th;
  pthread_create(&receiver_th, nullptr, receiver, nullptr);

  constexpr int pool_size = 5;
  pthread_t pool[pool_size];
  for (int i = 0; i < pool_size; i++) {
    pthread_create(&pool[i], nullptr, service, nullptr);
  }

  pthread_join(receiver_th, nullptr);
  for (int i = 0; i < pool_size; i++) {
    pthread_join(pool[i], nullptr);
  }
  pthread_mutex_destroy(&mutex_buffer);
  pthread_cond_destroy(&not_full);
  pthread_cond_destroy(&not_empty);
  pthread_mutex_destroy(&mutex_mend);
  request_generator_cleanup();

  time_t t2 = time(nullptr);
  double diff = difftime(t2, t1);
  printf("Time: %lf", diff);

  return 0;
}
