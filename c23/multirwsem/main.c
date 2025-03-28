#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

int data = 42;
constexpr int max_readers = 5;
constexpr int max_writers = 4;
int num_readers = 0;
sem_t sem_readers;
sem_t sem_mutex;

void * reader(void * arg);
void * writer(void * arg);

int main() {
  sem_init(&sem_readers, 0, 1);
  sem_init(&sem_mutex, 0, 1);

  pthread_t readers[max_readers];
  for (int i = 0; i < max_readers; i++) { pthread_create(&readers[i], nullptr, reader, nullptr); }
  pthread_t writers[max_writers];
  for (int i = 0; i < max_writers; i++) { pthread_create(&writers[i], nullptr, writer, nullptr); }

  for (int i = 0; i < max_readers; i++) { pthread_join(readers[i], nullptr); }
  for (int i = 0; i < max_writers; i++) { pthread_join(writers[i], nullptr); }

  sem_destroy(&sem_readers);
  sem_destroy(&sem_mutex);
}

void * reader(void *) {
  sem_wait(&sem_readers);
  num_readers++;
  if (num_readers == 1) { sem_wait(&sem_mutex); }
  sem_post(&sem_readers);

  printf("Reading data = %d\n", data);

  sem_wait(&sem_readers);
  num_readers--;
  if (num_readers == 0) { sem_post(&sem_mutex); }
  sem_post(&sem_readers);
  pthread_exit(nullptr);
}

void * writer(void *) {
  sem_wait(&sem_mutex);
  data += 2;
  printf("Writer is writing data = %d\n", data);
  sem_post(&sem_mutex);
  pthread_exit(nullptr);
}
