#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include <unistd.h>

void* print_message(void* ) {
    for (int i=0; i<3; ++i) {
      printf("Hello!\n");
      sleep(1);
    }
    return nullptr;
}

int main() {
    pthread_t thread;

    // Create a new thread that will execute the print_message function
    int result = pthread_create(&thread, nullptr, print_message, nullptr);
    if (result != 0) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        return EXIT_FAILURE;
    }

    result = pthread_join(thread, nullptr);
    if (result != 0) {
        fprintf(stderr, "Error joining thread: %d\n", result);
        return EXIT_FAILURE;
    }

    printf("Thread joined\n");
    return EXIT_SUCCESS;
}
