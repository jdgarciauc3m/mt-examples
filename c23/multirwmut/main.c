#include <pthread.h>
#include <stdio.h>

int data = 42;
constexpr int max_readers = 5;
constexpr int max_writers = 4;
int num_readers = 0;
pthread_mutex_t readers_mutex;
pthread_mutex_t data_mutex;

void * reader(void * arg);
void * writer(void * arg);

int main(void) {
  pthread_mutex_init(&readers_mutex, nullptr);
  pthread_mutex_init(&data_mutex, nullptr);

  pthread_t readers[max_readers];
  for (int i = 0; i < max_readers; i++) { pthread_create(&readers[i], nullptr, reader, nullptr); }
  pthread_t writers[max_writers];
  for (int i = 0; i < max_writers; i++) { pthread_create(&writers[i], nullptr, writer, nullptr); }

  for (int i = 0; i < max_readers; i++) { pthread_join(readers[i], nullptr); }
  for (int i = 0; i < max_writers; i++) { pthread_join(writers[i], nullptr); }

  pthread_mutex_destroy(&readers_mutex);
  pthread_mutex_destroy(&data_mutex);
}

void * reader(void *) {
  pthread_mutex_lock(&readers_mutex);
  num_readers++;
  if (num_readers == 1) { pthread_mutex_lock(&data_mutex); }
  pthread_mutex_unlock(&readers_mutex);

  printf("Reading data = %d\n", data);

  pthread_mutex_lock(&readers_mutex);
  num_readers--;
  if (num_readers == 0) { pthread_mutex_unlock(&data_mutex); }
  pthread_mutex_unlock(&readers_mutex);
  pthread_exit(nullptr);
}

void * writer(void *) {
  pthread_mutex_lock(&data_mutex);
  data += 2;
  printf("Writer is writing data = %d\n", data);
  pthread_mutex_unlock(&data_mutex);
  pthread_exit(nullptr);
}
