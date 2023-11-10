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


### 2.4 Récupérer la valeur de retour de la fonction  de ``Thread`` :


- **Récupération de la valeur de retour :** Une fois que le thread est terminé, vous pouvez utiliser `pthread_join` pour attendre sa fin et récupérer la valeur de retour.


- un exemple pour illustrer ces étapes :

```c
#include <stdio.h>
#include <pthread.h>

void *ma_fonction_thread(void *arg) {
    int *valeur_retour = malloc(sizeof(int));
    *valeur_retour = 42; // Définir une valeur de retour (dans cet exemple, 42)

   return (void*)valeur_retour ;
}

int main() {
    pthread_t thread;
    int *resultat;

    if (pthread_create(&thread, NULL, &ma_fonction_thread, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_join(thread, (void **)&resultat) != 0) {
        perror("pthread_join");
        return 1;
    }

    printf("La valeur de retour du thread est : %d\n", *resultat);

    free(resultat); // N'oubliez pas de libérer la mémoire allouée pour la valeur de retour

    return 0;
}
```

Dans cet exemple :

- La fonction `ma_fonction_thread` est exécutée dans un thread. Elle alloue dynamiquement de la mémoire pour stocker la valeur de retour .

- Dans la fonction `main`, nous créons un thread en appelant `pthread_create` et spécifions la fonction du thread (`ma_fonction_thread`) comme la fonction à exécuter dans le thread.

- En utilisant `pthread_join`, nous attendons que le thread se termine et récupérons la valeur de retour renvoyée par le thread. La valeur de retour est stockée dans la variable `resultat`.

- Assurez-vous de libérer la mémoire allouée pour la valeur de retour (dans cet exemple, nous utilisons `free`) une fois que vous avez récupéré la valeur.




### 2.5 la fonction ``pthread_exit`` :

- **Déscription :**

    - La fonction `pthread_exit`  est utilisée pour terminer l'exécution d'un thread. 

    - Cette fonction prend un argument qui peut être renvoyé au thread parent, s'il souhaite récupérer une valeur de retour du thread enfant.

    - La fonction `pthread_exit` est couramment utilisée pour permettre à un thread de se terminer proprement et, éventuellement, de renvoyer une valeur à son parent


- **la signature de la fonction `pthread_exit` :**

    ```c
    void pthread_exit(void *retval);
    ```

    - `retval` : C'est un pointeur vers la valeur que le thread souhaite renvoyer à son parent. Cette valeur peut être de n'importe quel type, car elle est de type `void *`. Si le thread n'a pas besoin de renvoyer de valeur, vous pouvez passer `NULL` comme argument.


- **un exemple d'utilisation :**

```c
#include <stdio.h>
#include <pthread.h>

void *fonction_thread(void *arg) {
    int *valeur = (int *)arg;
    printf("Thread : J'ai reçu la valeur %d.\n", *valeur);
    int resultat = 42;
    pthread_exit(&resultat);
}

int main() {
    pthread_t thread;
    int valeur = 123;

    if (pthread_create(&thread, NULL, fonction_thread, &valeur) != 0) {
        perror("Erreur lors de la création du thread.");
        return 1;
    }

    int *resultat;
    pthread_join(thread, (void **)&resultat);

    printf("Thread principal : Le thread fils a renvoyé %d.\n", *resultat);

    pthread_exit(0);
}
```






### RQ : la différance entre `Thread` et `Processus` :

Les processus et les threads sont deux concepts fondamentaux dans le domaine de la programmation concurrente et parallèle, et ils sont utilisés pour accomplir des tâches simultanées. Voici les principales différences entre les processus et les threads :

1. Définition :
   - Processus : Un processus est un programme en cours d'exécution avec sa propre mémoire, son propre espace d'adressage et sa propre table de gestion des fichiers. Chaque processus est indépendant, ce qui signifie qu'ils ne partagent pas de mémoire sauf si cela est spécifiquement configuré (comme la mémoire partagée).
   - Thread : Un thread (ou fil d'exécution) est une unité d'exécution plus légère qui fait partie d'un processus. Les threads d'un même processus partagent la même mémoire et les mêmes ressources du processus parent. Ils sont plus légers à créer et à gérer que les processus.

2. Création et Terminaison :
   - Processus : La création et la terminaison d'un processus sont plus lourdes en termes de ressources, car elles impliquent généralement la duplication de l'espace d'adressage du processus parent. Les processus sont indépendants les uns des autres.
   - Thread : La création et la terminaison des threads sont plus légères, car ils partagent la même mémoire que le processus parent. Ils sont plus rapides à créer et à détruire que les processus.

3. Communication et Synchronisation :
   - Processus : La communication entre les processus est généralement plus complexe et nécessite l'utilisation de mécanismes tels que les tubes (pipes) ou les sockets pour partager des données. La synchronisation entre les processus peut également être complexe.
   - Thread : Les threads d'un même processus peuvent communiquer et partager des données plus facilement car ils partagent la même mémoire. La synchronisation entre les threads est généralement plus simple, mais il est essentiel d'éviter les problèmes de concurrence et d'accès concurrent à la mémoire partagée.

4. Fiabilité :
   - Processus : Les processus sont plus fiables en cas de plantage, car un processus en échec ne devrait pas affecter les autres processus.
   - Thread : Si un thread d'un processus plante, il peut potentiellement affecter tous les autres threads du même processus, car ils partagent la même mémoire.

5. Parallélisme :
   - Processus : Les processus peuvent être exécutés en parallèle sur des processeurs multiples, car ils sont indépendants les uns des autres.
   - Thread : Les threads d'un processus peuvent être exécutés en parallèle, ce qui permet d'exploiter efficacement les processeurs multiples, mais cela nécessite une gestion appropriée de la concurrence.

