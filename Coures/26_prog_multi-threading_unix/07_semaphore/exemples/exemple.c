#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void *fonction_thread(void *arg) {
    int id = *(int *)arg;

    for (int i = 0; i < 5; ++i) {
        sem_wait(&semaphore);
        printf("Thread %d : Section critique (%d)\n", id, i);
        sem_post(&semaphore);
        usleep(100000);
    }

    return NULL;
}

int main() {
    sem_init(&semaphore, 0, 1);

    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    pthread_create(&thread1, NULL, fonction_thread, &id1);
    pthread_create(&thread2, NULL, fonction_thread, &id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&semaphore);

    return 0;

}