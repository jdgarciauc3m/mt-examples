#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

constexpr int buffer_size = 1024;
constexpr int num_elements = 100'000;

sem_t elements;
sem_t holes;
int buffer[buffer_size];

void * producer(void *);
void * consumer(void *);

int main(void) {
  sem_init(&elements, 0, 0);
  sem_init(&holes, 0, buffer_size);

  pthread_t th_producer;
  pthread_create(&th_producer, nullptr, producer, nullptr);
  pthread_t th_consumer;
  pthread_create(&th_consumer, nullptr, consumer, nullptr);

  pthread_join(th_producer, nullptr);
  pthread_join(th_consumer, nullptr);

  sem_destroy(&elements);
  sem_destroy(&holes);
}

void * producer(void *) {
  int pos = 0;
  for (int i = 0; i < num_elements; i++) {
    int data = i;  // Generate data somehow
    sem_wait(&holes);
    buffer[pos] = data;
    pos = (pos + 1) % buffer_size;
    sem_post(&elements);
  }
  pthread_exit(nullptr);
}

void * consumer(void *) {
  int pos = 0;
  for (int i = 0; i < num_elements; i++) {
    sem_wait(&elements);
    int data = buffer[pos];
    pos = (pos + 1) % buffer_size;
    sem_post(&holes);
    printf("%d\n", data);
  }
  pthread_exit(nullptr);
}
