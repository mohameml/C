# cour 05 : Barrier 


## 1. Introduction :

- **Une barrière :** en programmation concurrente est un mécanisme de synchronisation qui permet à un groupe de threads d'attendre mutuellement les uns les autres à un point spécifique de leur exécution avant de pouvoir continuer. 

- Les barrières sont principalement utilisées dans des scénarios où vous avez un groupe de threads qui doivent tous atteindre un certain point avant de pouvoir progresser ensemble.

- Le concept de barrière est souvent utilisé pour coordonner les threads dans des étapes distinctes d'un algorithme parallèle ou pour s'assurer que tous les threads ont terminé une phase particulière avant de passer à la suivante. 


## 2. Barrier en C : `pthread_barrier_t`:

- La structure `pthread_barrier_t` est un type de données utilisé dans la bibliothèque POSIX Threads (pthread) en C pour créer et gérer des barrières de threads.  

- **déclaration  et utilisation en C :**

    - **Déclaration d'une barrière :**
        ```c
        pthread_barrier_t my_barrier;
        ```

    - **Initialisation de la barrière :**
        ```c
        int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned int count);
        ```
        - `barrier` : Un pointeur vers la structure `pthread_barrier_t` à initialiser.
        - `attr` : Un pointeur vers des attributs de barrière (habituellement `NULL` pour les valeurs par défaut).
        - `count` : Le nombre de threads que la barrière attendra avant de se débloquer.

    - **Attente à la barrière :**
        ```c
        int pthread_barrier_wait(pthread_barrier_t *barrier);
        ```
        - Cette fonction est appelée par chaque thread pour attendre à la barrière.
        - Elle renvoie `PTHREAD_BARRIER_SERIAL_THREAD` pour un thread arbitraire qui atteint la barrière pour la première fois.
        - Elle renvoie `0` pour tous les autres threads qui atteignent la barrière.

    - **Destruction de la barrière :**
        ```c
        int pthread_barrier_destroy(pthread_barrier_t *barrier);
        ```
        - Utilisée pour détruire la barrière et libérer les ressources associées.


- **un exemple simple d'utilisation de `pthread_barrier_t` :**

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>



pthread_barrier_t barrier ;


void* routine()
{
    sleep(1);
    printf("waitting in the barrier \n");

    pthread_barrier_wait(&barrier);
    sleep(1);
    printf("we are passed the barrier \n");

    return NULL;
}


int main(void)
{

    pthread_t th[10];


    pthread_barrier_init(&barrier,NULL ,10);


    for(int i=0 ; i<10 ; i++)
    {
        if(pthread_create(&th[i],NULL,&routine , NULL)!=0)
        {
            perror("Faild to create  thread \n");
        }
    }


    for(int i =0 ; i < 10 ; i++)
    {
        if(pthread_join(th[i],NULL)!=0)
        {
            perror("faild to join  thread \n");
        }
    }


    pthread_barrier_destroy(&barrier);


    return 0 ;
}


```



