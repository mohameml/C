# cour 01 : introduction aux Threads en C 



## 1. Introduction à Threads :

- **Les threads:** :
    
    * Un thread (fil d'exécution) est une unité d'exécution légère qui partage la même mémoire que les autres threads d'un processus. Les threads permettent à un programme de gérer plusieurs tâches de manière concurrente, ce qui peut améliorer les performances.
 
    * sont utilisés pour créer des programmes parallèles qui peuvent effectuer plusieurs tâches en même temps.


- **Le parallélisme:** consiste à exécuter plusieurs threads en même temps pour améliorer les performances de votre programme. Cependant, vous devez faire attention aux problèmes de concurrence et utiliser des mécanismes de synchronisation tels que les mutex (verrous) pour éviter les conflits entre threads.



## 2. les bases de la programmation multi-thread en C avec ``pthread`` :



### 2.1 Création de Threads : **`pthread_create`**

- La fonction principale pour créer un thread est `pthread_create`. 


- Voici son prototype :

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg);
```

- `thread` est un pointeur vers la structure qui stockera l'identifiant du thread.
- `attr` est un pointeur vers un ensemble d'attributs du thread (généralement `NULL`).
- `start_routine` est la fonction que le thread exécutera.
- `arg` est un pointeur vers les arguments passés à la fonction `start_routine`.

- **Exemple** :

```c
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    // Code du thread
    printf("Bonjour depuis le thread !\n");
    return NULL;
}

int main() {
    pthread_t my_thread;
    if (pthread_create(&my_thread, NULL, thread_function, NULL) != 0) {
        perror("Erreur lors de la création du thread");
        return 1;
    }
    pthread_join(my_thread, NULL);
    return 0;
}
```

### 2.2 Attente de la Fin d'un Thread :  **`pthread_join`**


- La fonction `pthread_join` est utilisée pour attendre la fin de l'exécution d'un thread. Cela signifie que, lorsqu'un thread est créé à l'aide de `pthread_create`, le processus principal peut utiliser `pthread_join` pour attendre que ce thread se termine avant de continuer son propre travail. 

- Cela est souvent nécessaire pour garantir que les résultats produits par le thread créé sont disponibles ou pour coordonner les activités entre les différents threads d'un programme multi-thread.


- le prototype de la fonction `pthread_join` :

    ```c
    int pthread_join(pthread_t thread, void **retval);
    ```

    - `thread` : L'identifiant du thread que vous souhaitez attendre.

    - `retval` : Un pointeur vers un emplacement mémoire où la valeur de retour du thread sera stockée. Cette valeur de retour est renvoyée par la fonction que le thread exécute. Si vous n'avez pas besoin de récupérer la valeur de retour, vous pouvez simplement passer `NULL` à cet argument.

- La fonction `pthread_join` bloque le processus appelant (généralement le thread principal) jusqu'à ce que le thread spécifié par `thread` se termine. Une fois le thread terminé, le processus peut reprendre son exécution normale.

- un exemple d'utilisation de `pthread_join` :

```c
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Bonjour depuis le thread !\n");
    return (void *)42;
}

int main() {
    pthread_t my_thread;
    if (pthread_create(&my_thread, NULL, thread_function, NULL) != 0) {
        perror("Erreur lors de la création du thread");
        return 1;
    }

    void *thread_result;
    if (pthread_join(my_thread, &thread_result) != 0) {
        perror("Erreur lors de l'attente du thread");
        return 1;
    }

    printf("Le thread s'est terminé avec la valeur de retour : %ld\n", (long)thread_result);
    return 0;
}
```

Dans cet exemple, le thread créé avec `pthread_create` exécute la fonction `thread_function`, qui renvoie l'entier 42. La valeur de retour du thread est récupérée à l'aide de `pthread_join` et affichée par le thread principal.







### 2.3 Passage d'Arguments aux Threads

- Pour passer des arguments à un thread, vous pouvez créer une structure de données pour contenir les arguments, puis passer un pointeur vers cette structure lors de la création du thread.

**Exemple** :

```c
#include <stdio.h>
#include <pthread.h>

struct ThreadArgs {
    int data;
    char message[20];
};

void *thread_function(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    printf("Donnée : %d\nMessage : %s\n", args->data, args->message);
    return NULL;
}

int main() {
    pthread_t my_thread;
    struct ThreadArgs args = {42, "Hello"};
    if (pthread_create(&my_thread, NULL, thread_function, &args) != 0) {
        perror("Erreur lors de la création du thread");
        return 1;
    }
    pthread_join(my_thread, NULL);
    return 0;
}
```

