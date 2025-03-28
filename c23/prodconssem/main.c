#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

constexpr int buffer_size = 1024;
constexpr int num_elements = 100'000;

sem_t used_slots;
sem_t empty_slots;
int buffer[buffer_size];

void * producer(void *);
void * consumer(void *);

int main(void) {
  sem_init(&used_slots, 0, 0);           // Initially: no used slots
  sem_init(&empty_slots, 0, buffer_size);// Initially: All empty slots

  pthread_t th_producer;
  pthread_create(&th_producer, nullptr, producer, nullptr);
  pthread_t th_consumer;
  pthread_create(&th_consumer, nullptr, consumer, nullptr);

  pthread_join(th_producer, nullptr);
  pthread_join(th_consumer, nullptr);

  sem_destroy(&used_slots);
  sem_destroy(&empty_slots);
}

void * producer(void *) {
  int pos = 0;
  for (int i = 0; i < num_elements; ++i) {
    int data = i;// Generate data somehow
    sem_wait(&empty_slots);
    buffer[pos] = data;
    pos = (pos + 1) % buffer_size;
    sem_post(&used_slots);
  }
  pthread_exit(nullptr);
}

void * consumer(void *) {
  int pos = 0;
  for (int i = 0; i < num_elements; ++i) {
    sem_wait(&used_slots);
    int data = buffer[pos];
    pos = (pos + 1) % buffer_size;
    sem_post(&empty_slots);
    printf("%d\n", data);
  }
  pthread_exit(nullptr);
}
