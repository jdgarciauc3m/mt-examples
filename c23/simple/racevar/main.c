#include <stdio.h>
#include <pthread.h>

double balance = 0;

void deposit(double amount) {
  balance += amount;
}

void withdraw(double amount) {
  balance -= amount;
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
  pthread_create(&deposit_th, nullptr, deposit_thread, nullptr);
  pthread_create(&withdraw_th, nullptr, withdraw_thread, nullptr);
  pthread_join(deposit_th, nullptr);

  printf("final balance: %lf\n", balance);
}