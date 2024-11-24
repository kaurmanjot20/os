#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function executed by threads
void *print_message_function(void *ptr) {
    char *message;
    message = (char *)ptr; // Cast the void pointer to a character pointer
    printf("%s\n", message);
    pthread_exit(message); // Exit the thread and return the message
}

int main() {
    pthread_t thread1, thread2; // Thread identifiers
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;          // Return values for pthread_create
    void *ret;                 // Pointer to capture thread return value

    // Create independent threads, each executing the print_message_function
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void *)message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void *)message2);

    // Wait for both threads to complete
    pthread_join(thread1, &ret);
    printf("Thread 1 returns: %d\n", iret1);
    printf("Returned value from thread 1: %p\n", ret);

    pthread_join(thread2, &ret);
    printf("Thread 2 returns: %d\n", iret2);
    printf("Returned value from thread 2: %p\n", ret);

    exit(0);
}
