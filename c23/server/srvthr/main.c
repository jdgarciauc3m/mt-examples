#include <stdio.h>
#include <string.h>

// POSIX headers
#include <semaphore.h>
#include <pthread.h>

// Server library
#include "request.h"


sem_t sem_nchilren;
sem_t sem_request;

void copy_request(request_t * dest, const request_t *src) {
  dest->id = src->id;
  dest->kind = src->kind;
  strcpy(dest->url,src->url);
  dest->data = src->data;
}

void * service(void * arg) {
  request_t req;
  copy_request(&req, (request_t*)arg);
  sem_post(&sem_request);
  fprintf(stderr, "Starting service for ID: %ld\n", req.id);
  process_request(&req);
  reply_request(&req);
  sem_post(&sem_nchilren);
  fprintf(stderr, "Ending service for ID: %ld\n", req.id);
  pthread_exit(nullptr);
  return nullptr;
}

void * receiver(void *) {
  constexpr int max_requests = 5;
  int num_in_service = 0;
  request_t req;
  pthread_t service_th;

  for (int i = 0; i < max_requests; i++) {
    receive_request(&req);
    num_in_service++;
    pthread_create(&service_th, nullptr, service, &req);
    sem_wait(&sem_request);
    pthread_detach(service_th);
  }

  while (num_in_service>0) {
    fprintf(stderr, "Waiting for children\n");
    sem_wait(&sem_nchilren);
    num_in_service--;
    fprintf(stderr, "Child terminated\n");
  }

  pthread_exit(nullptr);
  return nullptr;
}


int main() {
  time_t t1 = time(nullptr);

  sem_init(&sem_nchilren, 0, 0);
  sem_init(&sem_request, 0, 0);
  pthread_t receiver_th;
  pthread_create(&receiver_th, nullptr, receiver, nullptr);
  pthread_join(receiver_th, nullptr);
  sem_destroy(&sem_nchilren);
  sem_destroy(&sem_request);

  time_t t2 = time(nullptr);

  double diff = difftime(t2, t1);
  printf("Time: %lf", diff);
}

