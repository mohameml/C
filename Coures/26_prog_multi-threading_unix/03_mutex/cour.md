# cour 03 : Mutex 


## 1. Définitions :

- ``l'éxclusion mutuelle`` : est un concept fondamental en programmation concurrente ,  elle se réfère à une condition où un seul processus (ou thread) peut accéder à une ressource partagée ou exécuter une section critique à la fois. L'idée derrière l'exclusion mutuelle est d'éviter les conflits et les incohérences lorsque plusieurs processus tentent d'accéder simultanément à la même ressource.


- ``section critique :``  une portion de code dans un programme informatique où une ressource partagée est accédée ou modifiée par plusieurs threads (ou processus) concurrents. 


- ``Un mutex`` :  est un mécanisme de synchronisation utilisé en programmation concurrente pour éviter les conflits de données lorsque plusieurs threads (ou processus) tentent d'accéder simultanément à une ressource partagée. 

## 2. la structure de mutex en C :  `pthread_mutex_t` 

- La structure `pthread_mutex_t` en C est un type de données utilisé pour représenter un ``mutex`` géré par la bibliothèque de threads POSIX (pthreads). 

- Cette structure est utilisée pour **créer**, **initialiser**, **verrouiller** et **déverrouiller** un mutex, ce qui permet de gérer l'accès concurrent aux ressources partagées. 

```c
typedef struct {
    // Champ interne, généralement non accessible directement
    // Utilisé pour implémenter le mutex.
} pthread_mutex_t;
```

- La structure `pthread_mutex_t`  est  généralement pas être accédée directement. Au lieu de cela, vous utiliserez les fonctions pthread appropriées pour travailler avec les mutex. 


## 3. les fonctions de manipulation de `mutex`  en C : 


1. **`pthread_mutex_init` :** 


- La fonction `pthread_mutex_init` en C est utilisée pour initialiser un ``mutex`` géré par la bibliothèque de threads POSIX (pthreads). 

- Cette fonction crée un nouvel objet mutex et l'initialise avec les attributs spécifiés. 

- **sa signature :**

```c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
```

- `mutex` : C'est un pointeur vers un objet de type `pthread_mutex_t` que vous avez déjà déclaré, `pthread_mutex_init` initialisera cet objet pour représenter un mutex valide.

- `attr` : C'est un pointeur vers un objet de type `pthread_mutexattr_t` qui peut être utilisé pour spécifier des attributs personnalisés pour le mutex. Si vous ne souhaitez pas personnaliser les attributs, vous pouvez passer `NULL` pour utiliser les attributs par défaut.

- **Exemple :**


```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


int sum = 0 ;

pthread_mutex_t mutex ;

void* routine()
{   
    pthread_mutex_lock(&mutex);  
    for(int i=0 ; i<1000000;i++)
    {
        
        sum++; 
        // 	movl sum(%rip), %eax
        // addl	$1, %eax
        // movl	%eax, sum(%rip)

    }
    
    pthread_mutex_unlock(&mutex);


    return NULL ;
}



int main(void)
{
    pthread_t t1 , t2 ;
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&t1 , NULL , &routine , NULL);
    
    pthread_create(&t2 , NULL , &routine , NULL);

    pthread_join(t1,NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    printf("%d \n", sum);
    return 0 ;
}
```

Il est important d'initialiser et de détruire les mutex correctement pour éviter les fuites de ressources. De plus, assurez-vous de gérer les erreurs qui peuvent survenir lors de l'initialisation du mutex en vérifiant la valeur renvoyée par `pthread_mutex_init`. 

2. **`pthread_mutex_destroy` :** 

- La fonction `pthread_mutex_destroy` en C est utilisée pour détruire un mutex (exclusion mutuelle) qui a été initialisé précédemment à l'aide de la fonction `pthread_mutex_init`. Cette fonction libère toutes les ressources associées au mutex et le rend inutilisable. 

- **sa signature :**

```c
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

- `mutex` : C'est un pointeur vers un objet de type `pthread_mutex_t` qui représente le mutex que vous souhaitez détruire.



- **exemple d'utilisation de `pthread_mutex_destroy` :**

```c
#include <pthread.h>

pthread_mutex_t monMutex; // Déclaration d'un mutex

int main() {
    // Initialisation du mutex avec les attributs par défaut
    if (pthread_mutex_init(&monMutex, NULL) != 0) {
        perror("pthread_mutex_init");
        return 1;
    }

    // Utilisation du mutex ici...

    // Destruction du mutex une fois qu'il n'est plus nécessaire
    if (pthread_mutex_destroy(&monMutex) != 0) {
        perror("pthread_mutex_destroy");
        return 1;
    }

    return 0;
}
```

Dans l'exemple ci-dessus, le mutex est initialement créé avec `pthread_mutex_init` et utilisé dans la section critique. Une fois que le mutex n'est plus nécessaire, `pthread_mutex_destroy` est appelé pour libérer les ressources associées au mutex. Vous devez toujours vérifier la valeur renvoyée par `pthread_mutex_destroy` pour détecter d'éventuelles erreurs.



3. **`pthread_mutex_lock` :** 

- **Déscription :**

    - La fonction `pthread_mutex_lock` en C est utilisée pour verrouiller (ou bloquer) un mutex  avant d'entrer dans une section critique de code. 

    - Elle assure l'exclusion mutuelle, ce qui signifie que si un autre thread a déjà verrouillé le mutex, l'appel à `pthread_mutex_lock` par un thread en attente bloquera ce thread jusqu'à ce que le mutex soit déverrouillé par le thread qui le détient actuellement. 

- **sa signature :**

```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
```

- `mutex` : C'est un pointeur vers un objet de type `pthread_mutex_t` qui représente le mutex que vous souhaitez verrouiller.
 
 
- **un exemple d'utilisation de `pthread_mutex_lock` pour protéger une section critique :**

```c
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t monMutex; // Déclaration d'un mutex

int compteur = 0;

void *fonction_thread(void *arg) {
    for (int i = 0; i < 10000; i++) {
        pthread_mutex_lock(&monMutex); // Verrouille le mutex
        compteur++;
        pthread_mutex_unlock(&monMutex); // Déverrouille le mutex
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialisation du mutex avec les attributs par défaut
    pthread_mutex_init(&monMutex, NULL);

    // Création de deux threads
    pthread_create(&thread1, NULL, fonction_thread, NULL);
    pthread_create(&thread2, NULL, fonction_thread, NULL);

    // Attente de la fin des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destruction du mutex une fois qu'il n'est plus nécessaire
    pthread_mutex_destroy(&monMutex);

    printf("Valeur finale du compteur : %d\n", compteur);

    return 0;
}
```

Dans cet exemple, `pthread_mutex_lock` est utilisé pour verrouiller le mutex `monMutex` avant d'incrémenter la variable `compteur` dans chaque thread. Le verrouillage du mutex garantit que chaque thread entre dans la section critique de manière exclusive, évitant ainsi les conflits de données.




4. **`pthread_mutex_trylock` :**  

- **Description :**

    -  La fonction `pthread_mutex_trylock` en C est utilisée pour essayer de verrouiller un mutex  sans attendre. 
    
    - Si le mutex est déjà verrouillé par un autre thread, `pthread_mutex_trylock` renverra immédiatement une valeur indiquant si la tentative de verrouillage a réussi ou échoué. 
    
- **sa signature :**

```c
int pthread_mutex_trylock(pthread_mutex_t *mutex);
```

- `mutex` : C'est un pointeur vers un objet de type `pthread_mutex_t` qui représente le mutex que vous souhaitez essayer de verrouiller.

La valeur de retour de `pthread_mutex_trylock` peut être interprétée comme suit :

- Si la fonction renvoie 0, cela signifie que le mutex a été verrouillé avec succès par le thread appelant.
- Si la fonction renvoie un code d'erreur, cela signifie que le mutex est déjà verrouillé par un autre thread, et la tentative de verrouillage a échoué.


- **un exemple d'utilisation de `pthread_mutex_trylock` :**

```c
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t monMutex; // Déclaration d'un mutex

int compteur = 0;

void *fonction_thread(void *arg) {
    for (int i = 0; i < 10000; i++) {
        // Essayer de verrouiller le mutex sans attendre
        if (pthread_mutex_trylock(&monMutex) == 0) {
            compteur++;
            pthread_mutex_unlock(&monMutex); // Déverrouiller le mutex
        }
        // Si le mutex est déjà verrouillé, ne rien faire dans ce tour de boucle
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialisation du mutex avec les attributs par défaut
    pthread_mutex_init(&monMutex, NULL);

    // Création de deux threads
    pthread_create(&thread1, NULL, fonction_thread, NULL);
    pthread_create(&thread2, NULL, fonction_thread, NULL);

    // Attente de la fin des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destruction du mutex une fois qu'il n'est plus nécessaire
    pthread_mutex_destroy(&monMutex);

    printf("Valeur finale du compteur : %d\n", compteur);

    return 0;
}
```

Dans cet exemple, `pthread_mutex_trylock` est utilisé pour essayer de verrouiller le mutex `monMutex` sans attendre. Si le mutex est déjà verrouillé par un autre thread, le thread actuel passe simplement au tour de boucle suivant, sans attendre. Si le verrouillage réussit, le thread entre dans la section critique, incrémente la variable `compteur`, puis déverrouille le mutex.


5. **`pthread_mutex_unlock` :** 

- **Description :**

    - La fonction `pthread_mutex_unlock` en C est utilisée pour déverrouiller (ou débloquer) un mutex (exclusion mutuelle) qui a été verrouillé précédemment à l'aide de la fonction `pthread_mutex_lock` ou `pthread_mutex_trylock`. 
    
    - Elle permet à d'autres threads d'accéder à la section critique protégée par le mutex. 
    
- **sa signature :**

```c
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

- `mutex` : C'est un pointeur vers un objet de type `pthread_mutex_t` qui représente le mutex que vous souhaitez déverrouiller.









