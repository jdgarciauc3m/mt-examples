#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

constexpr int buffer_size = 1024;
constexpr int num_elements = 100'000;

pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;
int buffer[buffer_size];
int n_elements = 0;

void * producer(void *);
void * consumer(void *);

int main(void) {
  pthread_mutex_init(&mutex, nullptr);
  pthread_cond_init(&not_full, nullptr);
  pthread_cond_init(&not_empty, nullptr);

  pthread_t th_producer;
  pthread_create(&th_producer, nullptr, producer, nullptr);
  pthread_t th_consumer;
  pthread_create(&th_consumer, nullptr, consumer, nullptr);

  pthread_join(th_producer, nullptr);
  pthread_join(th_consumer, nullptr);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&not_full);
  pthread_cond_destroy(&not_empty);
}

void * producer(void *) {
  int pos = 0;
  for (int i = 0; i < num_elements; i++) {
    int data = i; // Produce a data item
    printf("producing %d\n", data);
    pthread_mutex_lock(&mutex);
    while (n_elements == buffer_size) {
      pthread_cond_wait(&not_full, &mutex);
    }
    buffer[pos] = data;
    pos = (pos + 1) % buffer_size;
    n_elements++;
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(nullptr);
}

void * consumer(void *) {
  int pos = 0;
  for (int i = 0; i < num_elements; i++) {
    pthread_mutex_lock(&mutex);
    while (n_elements == 0) {
      pthread_cond_wait(&not_empty, &mutex);
    }
    int data = buffer[pos];
    pos = (pos + 1) % buffer_size;
    n_elements--;
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);
    printf("consuming %d\n", data);
  }
  pthread_exit(nullptr);
}
