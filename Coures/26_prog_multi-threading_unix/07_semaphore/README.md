# cour 07 : **``Les sémaphores``**


## 1. **Introduction:**

### a.définition :


- Les sémaphores sont un mécanisme de synchronisation utilisé  pour gérer l'accès à des ressources partagées ou pour coordonner l'exécution de plusieurs processus ou threads. 

- Un sémaphore s est l’ensemble d’un compteur entier noté s.c et d’une file d’attente s.f

- Deux opérations qui sont exécutées en exclusion  mutuelle :
    * P(s) s.c--; si s.c<0 alors le processus qui exécute P est bloqué dans s.f
    
    * V(s) s.c++ ; si s.c<=0 alors activer un processus de s.f



### b. Propriétés des sémaphores :


- Les propriétés des sémaphores :

1. **Valeur initiale d'un sémaphore** (c0 >= 0) : 

    - Lorsqu'un sémaphore est créé ou initialisé, il reçoit une valeur initiale, généralement indiquée comme c0. 
    
    - Un sémaphore ne peut pas avoir une valeur initiale négative.

2. **Valeur positive du sémaphore (s.c > 0)** : 
    
    - Si la valeur du sémaphore (s.c) est strictement positive, cela signifie qu'il y a des ressources disponibles pour être utilisées. 
    
    - Plus précisément, s.c représente le nombre de processus ou de threads qui peuvent exécuter avec succès une opération P (attente) sans se bloquer. 
    
    - Chaque exécution de P décrémente la valeur du sémaphore. Si s.c est supérieur à zéro, cela signifie que les ressources sont disponibles, et les processus peuvent les acquérir sans être mis en attente.

3. **Valeur négative du sémaphore (s.c < 0)** : 
    
    - Si la valeur du sémaphore (s.c) est négative, cela indique qu'il y a des processus en attente pour acquérir des ressources. Plus précisément, s.c représente le nombre de processus actuellement en attente (bloqués) pour effectuer une opération P. 
    
    - Chaque fois qu'un processus exécute P et ne peut pas acquérir de ressource (car s.c <= 0), il est mis en attente jusqu'à ce qu'une ressource devienne disponible.

Ces propriétés permettent de contrôler l'accès concurrent à une ressource partagée. Lorsqu'un processus souhaite acquérir une ressource, il utilise une opération P. Si s.c est positif, le processus obtient la ressource et décrémente s.c. Sinon, s.c devient négatif, indiquant que le processus est en attente. Lorsqu'un processus libère une ressource à l'aide de l'opération V, s.c est incrémenté, ce qui peut débloquer un processus en attente.




## 2. **Les sémaphores en C :``<semaphore.h>``**


La bibliothèque `<semaphore.h>` en C fournit des fonctionnalités pour utiliser les sémaphores, qui sont des mécanismes de synchronisation permettant la coordination entre plusieurs threads dans un programme multithread. Les sémaphores peuvent être utilisés pour gérer l'accès concurrentiel à des ressources partagées ou pour synchroniser l'exécution de plusieurs threads.


### a. Déclaration d'un semaphore :

- Pour déclarer un sémaphore en C à l'aide de la bibliothèque `<semaphore.h>`, vous devez utiliser le type de données `sem_t`. 

- Voici comment vous pouvez déclarer un sémaphore :

```c
#include <semaphore.h>

sem_t monSemaphore; // Déclaration du sémaphore
```


### b. Initialisation d'un Sémaphore :**`sem_init`**

- La fonction `sem_init` est utilisée pour initialiser un sémaphore. 

- Elle prend en charge trois arguments : 
    
    - l'adresse du sémaphore, 
    
    - le partage (0 pour un sémaphore local, non nul pour un sémaphore partagé entre les processus), 
    
    - et la valeur initiale du sémaphore.

```c
int sem_init(sem_t *sem, int pshared, unsigned int value);
```

### c. Opérations sur les Sémaphores

La bibliothèque `<semaphore.h>` propose trois opérations principales sur les sémaphores :

- `sem_wait`: Attend que le sémaphore soit décrémenté à une valeur positive, puis le décrémente.
- `sem_post`: Incrémente le sémaphore, le libérant potentiellement pour d'autres threads.
- `sem_trywait`: Tente de décrémenter le sémaphore sans attendre, renvoie une erreur si le sémaphore est déjà à zéro.

```c
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_trywait(sem_t *sem);
```

### d. Destruction d'un Sémaphore

La fonction `sem_destroy` est utilisée pour libérer les ressources associées à un sémaphore après son utilisation.

```c
int sem_destroy(sem_t *sem);
```

### e.Exemple Simple d'Utilisation:

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

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
```

Dans cet exemple, deux threads accèdent à une section critique protégée par un sémaphore. Le sémaphore initialisé avec une valeur de 1 garantit l'accès exclusif à la section critique.


## 3. **sémaphore binaire :**



### a. **Définition :**

- Un sémaphore binaire est un type particulier de sémaphore  qu'il ne peut avoir que deux états distincts : 0 ou 1 .

- **Valeurs Possibles :**
    
    - 0 : La ressource est actuellement occupée (verrouillée).
    - 1 : La ressource est actuellement libre (déverrouillée).

- **Opérations Principales :**
  
    - **P (Proberen) :** Attente (Wait) - Si la ressource est occupée, le thread est bloqué jusqu'à ce qu'elle devienne libre.
        
    - **V (Verhogen) :** Libération (Signal) - Libère la ressource, la mettant à disposition d'autres threads.

### b. Utilisation Courante :

- **Exclusion Mutuelle :** 

Les sémaphores binaires sont souvent utilisés pour gérer l'exclusion mutuelle, où un seul thread à la fois peut accéder à une ressource partagée. Par exemple, dans le cas d'une section critique.


Exemple  :

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t binarySemaphore;

void *threadFunction(void *arg) {
    // Attente (Wait) sur le sémaphore
    sem_wait(&binarySemaphore);

    // Section critique (code protégé par le sémaphore)
    printf("Thread en section critique.\n");

    // Libération (Signal) du sémaphore
    sem_post(&binarySemaphore);

    return NULL;
}

int main() {
    // Initialisation du sémaphore binaire
    sem_init(&binarySemaphore, 0, 1); // La valeur initiale est 1 (libre)

    // Création d'un thread
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, NULL);

    // Attente de la fin du thread
    pthread_join(thread, NULL);

    // Destruction du sémaphore
    sem_destroy(&binarySemaphore);

    return 0;
}
```

Dans cet exemple, le sémaphore binaire est initialement à 1, ce qui signifie qu'il est libre. Le thread entre en section critique après avoir réussi à acquérir le sémaphore avec `sem_wait`, puis libère le sémaphore avec `sem_post` lorsqu'il a terminé. Cette utilisation garantit qu'un seul thread à la fois peut être en section critique.




- **Synchronisation entre le main thread avec un autre thread :** 

Vous pouvez utiliser un sémaphore pour synchroniser le main thread avec un autre thread afin de s'assurer qu'une tâche spécifique est terminée avant que le main thread ne continue son exécution.

Voici comment cela pourrait être mis en œuvre :

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void *threadFunction(void *arg) {
    // Effectuer la tâche spécifique

    // Signaliser que la tâche est terminée
    sem_post(&semaphore);

    return NULL;
}

int main() {
    // Initialiser le sémaphore à 0
    sem_init(&semaphore, 0, 0);

    // Créer un thread
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, NULL);

    // Attendre que la tâche soit terminée
    sem_wait(&semaphore);

    // Continuer l'exécution dans le main thread après que la tâche est terminée
    printf("La tâche est terminée. Le main thread peut continuer.\n");

    // Libérer les ressources du sémaphore
    sem_destroy(&semaphore);

    return 0;
}
```

Dans cet exemple, le main thread utilise `sem_wait` pour attendre que le sémaphore devienne non nul, ce qui se produit lorsque le thread a terminé sa tâche et a appelé `sem_post`. Cela garantit que le main thread attend effectivement la fin de la tâche avant de continuer son exécution.

C'est une approche courante pour synchroniser les threads lorsque vous avez besoin de garantir qu'une tâche spécifique est terminée avant de passer à une autre partie du programme.




### c.  **la différence entre les sémaphores binaires et les mutex :**

- **Mutex :**

- Un mutex doit être verrouillé (lock) et déverrouillé (unlock) par le même thread. Cela signifie qu'un thread qui a verrouillé un mutex est également responsable de le déverrouiller.

- Cette propriété d'exclusivité assure qu'un seul thread à la fois peut accéder à la ressource protégée par le mutex. Cela garantit l'exclusion mutuelle.

- **Sémaphore Binaire :**

- Un sémaphore binaire peut être "baissé" (P) par un thread et "levé" (V) par un autre thread. Différents threads peuvent interagir avec un sémaphore binaire, et la responsabilité de l'abaisser et de le relever n'est pas limitée au même thread.

- Cette caractéristique rend les sémaphores binaires plus flexibles dans certaines situations où différents threads peuvent être impliqués dans des opérations de verrouillage et de déverrouillage.



En résumé, la principale différence réside dans la propriété d'exclusivité des mutex, où un thread doit prendre en charge le verrouillage et le déverrouillage, tandis que les sémaphores binaires permettent une plus grande flexibilité en permettant à différents threads de baisser et de lever le sémaphore.



## 4. **La fonction `sem_getvalue`:**

La fonction `sem_getvalue` est une fonction de la bibliothèque `<semaphore.h>` en C qui permet de récupérer la valeur actuelle d'un sémaphore. Cette fonction est utile pour connaître l'état actuel du sémaphore, notamment le nombre d'opérations "V" (libération) moins le nombre d'opérations "P" (attente) qui ont été effectuées sur le sémaphore.

Voici la signature de la fonction `sem_getvalue` :

```c
#include <semaphore.h>

int sem_getvalue(sem_t *sem, int *sval);
```

- `sem` : Pointeur vers le sémaphore dont vous souhaitez obtenir la valeur.
- `sval` : Pointeur vers un int où la valeur du sémaphore sera stockée.

### Exemple d'utilisation :

```c
#include <stdio.h>
#include <semaphore.h>

int main() {
    sem_t mySemaphore;

    // Initialiser le sémaphore avec une valeur initiale de 2
    sem_init(&mySemaphore, 0, 2);

    // Obtenir la valeur du sémaphore
    int value;
    sem_getvalue(&mySemaphore, &value);

    // Afficher la valeur du sémaphore
    printf("La valeur du sémaphore est : %d\n", value);

    // Libérer les ressources du sémaphore
    sem_destroy(&mySemaphore);

    return 0;
}
```

Dans cet exemple, le sémaphore est initialisé avec une valeur initiale de 2, puis la fonction `sem_getvalue` est utilisée pour obtenir cette valeur. La valeur est ensuite affichée à l'écran.

Notez que `sem_getvalue` n'est pas une fonction standardisée par le C11, et sa disponibilité dépend du système d'exploitation. Elle est plus couramment disponible sur les systèmes de type POSIX.


Si vous avez un seul sémaphore partagé entre plusieurs threads et que ces threads peuvent effectuer des opérations concurrentes sur ce sémaphore, il est recommandé d'utiliser un mutex pour garantir l'exclusion mutuelle lors des opérations sur le sémaphore. Cela évite les conditions de concurrence et assure une manipulation sûre du sémaphore partagé.

Voici un exemple simplifié pour illustrer cela :

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mySemaphore;
pthread_mutex_t mutex;

void *threadFunction(void *arg) {
    // Effectuer des opérations non protégées sur le sémaphore
    sem_post(&mySemaphore);

    // Opérations protégées par un mutex
    pthread_mutex_lock(&mutex);
    // Effectuer des opérations protégées sur le sémaphore
    sem_wait(&mySemaphore);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    // Initialisation du sémaphore
    sem_init(&mySemaphore, 0, 0);

    // Initialisation du mutex
    pthread_mutex_init(&mutex, NULL);

    // Création de plusieurs threads
    pthread_t threads[5];
    for (int i = 0; i < 5; ++i) {
        pthread_create(&threads[i], NULL, threadFunction, NULL);
    }

    // Attente de la fin de tous les threads
    for (int i = 0; i < 5; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Libération des ressources
    sem_destroy(&mySemaphore);
    pthread_mutex_destroy(&mutex);

    return 0;
}
```

Dans cet exemple, chaque thread effectue des opérations non protégées sur le sémaphore en utilisant `sem_post`. Cependant, pour des opérations telles que `sem_wait`, qui modifient l'état du sémaphore, un mutex est utilisé pour garantir que ces opérations sont effectuées de manière atomique.

Assurez-vous d'ajuster cette structure générale à vos besoins spécifiques en fonction des opérations que vous effectuez sur le sémaphore dans vos threads.