# Le problème classique du producteur et du consommateur :


- Le problème classique du producteur et du consommateur est un exemple fréquent utilisé pour illustrer la synchronisation de threads dans les systèmes multithreading. Dans cet exemple, nous allons utiliser le langage C avec la bibliothèque POSIX Threads (pthread), les variables de condition (`pthread_cond_t`) et les mutex (`pthread_mutex_t`) pour synchroniser les threads producteurs et consommateurs.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;  // Nombre d'éléments dans le tampon
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex pour la section critique
pthread_cond_t full = PTHREAD_COND_INITIALIZER;     // Condition "plein"
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;    // Condition "vide"

// Fonction du producteur
void *producer(void *arg) {
    int item;

    for (int i = 0; i < 10; ++i) {
        item = rand();  // Produire un élément (dans cet exemple, un nombre aléatoire)

        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            // Le tampon est plein, le producteur attend qu'il y ait de la place
            pthread_cond_wait(&empty, &mutex);
        }

        // Ajouter l'élément au tampon
        buffer[count++] = item;
        printf("Produit : %d\n", item);

        // Signaler aux consommateurs qu'il y a des éléments disponibles
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

// Fonction du consommateur
void *consumer(void *arg) {
    int item;

    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            // Le tampon est vide, le consommateur attend qu'il y ait des éléments
            pthread_cond_wait(&full, &mutex);
        }

        // Retirer un élément du tampon
        item = buffer[--count];
        printf("Consommé : %d\n", item);

        // Signaler aux producteurs qu'il y a de l'espace disponible
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Créer les threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Attendre la fin des threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Détruire les ressources utilisées par le mutex et les variables de condition
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}
```

Ce programme crée deux threads, un producteur et un consommateur, qui partagent un tampon (`buffer`) de taille fixe. Les variables de condition (`full` et `empty`) sont utilisées pour synchroniser les deux threads et éviter les conditions de concurrence.

Le producteur produit 10 éléments (nombres aléatoires dans cet exemple) et les ajoute au tampon, tandis que le consommateur retire ces éléments du tampon. Les opérations de verrouillage et déverrouillage du mutex garantissent un accès exclusif au tampon. Les appels à `pthread_cond_wait` permettent aux threads de s'endormir lorsqu'ils ne peuvent pas produire ou consommer, et les appels à `pthread_cond_signal` les réveillent lorsque les conditions sont remplies.

N'oubliez pas de compiler ce programme avec l'option `-pthread` pour inclure le support de pthread. Par exemple :

```bash
gcc -o prog program.c -pthread
```   
