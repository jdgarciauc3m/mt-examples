#include <stdio.h>
#include <pthread.h>

double balance = 0;
pthread_mutex_t mutex_balance = PTHREAD_MUTEX_INITIALIZER;

void deposit(double amount) {
  pthread_mutex_lock(&mutex_balance);
  balance += amount;
  pthread_mutex_unlock(&mutex_balance);
}

void withdraw(double amount) {
  pthread_mutex_lock(&mutex_balance);
  balance -= amount;
  pthread_mutex_unlock(&mutex_balance);
}

void * deposit_thread(void *) {
  double amount = 100;;
  for (int i = 0; i < 100; ++i) {
    deposit(amount);
  }
  return nullptr;
}

void * withdraw_thread(void * ) {
  double amount = 50;
  for (int i = 0; i < 100; ++i) {
    withdraw(amount);
  }
  return nullptr;
}

int main() {
  pthread_t deposit_th;
  pthread_t withdraw_th;
  pthread_mutex_init(&mutex_balance, nullptr);
  pthread_create(&deposit_th, nullptr, deposit_thread, nullptr);
  pthread_create(&withdraw_th, nullptr, withdraw_thread, nullptr);
  pthread_join(deposit_th, nullptr);
  pthread_join(withdraw_th, nullptr);
  pthread_mutex_destroy(&mutex_balance);

  printf("final balance: %lf\n", balance);
}
