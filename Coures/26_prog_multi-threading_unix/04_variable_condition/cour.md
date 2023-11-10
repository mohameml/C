# cour 04 : Variable Condition :

## 1. Introduction :

- **Définition :**

    - Une variable de condition  est un mécanisme de synchronisation  pour coordonner l'exécution de threads en leur permettant de communiquer et de synchroniser leur activité jusqu'à que une condition spécifique est vérifier. 

    

- **Carctéristiques :**

    1. **Attente de conditions** : Les variables de condition sont principalement utilisées pour permettre à un thread d'attendre qu'une certaine condition se produise. Les threads peuvent attendre sur une variable de condition jusqu'à ce qu'un autre thread les réveille en modifiant cette condition.

    2. **Mécanisme de notification** : Les variables de condition fournissent un mécanisme de notification permettant à un thread d'informer d'autres threads qu'une condition souhaitée est maintenant remplie et qu'ils peuvent procéder. Cette notification permet d'économiser des ressources en évitant aux threads de vérifier constamment la condition.

    3. **Utilisation conjointe avec un mutex** : Les variables de condition sont généralement utilisées en conjonction avec un mutex (verrou). La combinaison d'un mutex et d'une variable de condition permet de créer des sections critiques protégées par le mutex, tout en permettant aux threads d'attendre que la condition soit satisfaite sans gaspiller des ressources du processeur.

    4. **Opérations clés** :

    - `pthread_cond_wait` : Un thread attend sur une variable de condition. Il libère le mutex associé et entre en état de sommeil jusqu'à ce qu'un autre thread le réveille en modifiant la condition.

    - `pthread_cond_signal` : Un thread signale à un thread en attente sur une variable de condition que la condition souhaitée est remplie. Il réveille au moins un des threads en attente.

    - `pthread_cond_broadcast` : Un thread signale à tous les threads en attente sur une variable de condition que la condition souhaitée est remplie. Il réveille tous les threads en attente.

    5. **Utilisations courantes** : Les variables de condition sont couramment utilisées pour implémenter des modèles de synchronisation complexes tels que la communication entre producteurs et consommateurs, le rendez-vous, la gestion de files d'attente, etc.





## 2. les variables de condition en C : `pthread_cond_t` :

- Les variables de condition en C, représentées par le type `pthread_cond_t`, sont un mécanisme de synchronisation fourni par la bibliothèque de threads POSIX (pthreads). 

- Elles sont utilisées pour coordonner l'exécution de threads en leur permettant d'attendre qu'une certaine condition soit remplie. 

- Les variables de condition sont souvent utilisées en conjonction avec des mutex (verrous) pour synchroniser l'accès à des ressources partagées entre threads. 

- Voici comment elles fonctionnent en général :

    1. **Création d'une variable de condition** : Pour créer une variable de condition, vous pouvez utiliser `pthread_cond_init` :

    ```c
    pthread_cond_t ma_variable_de_condition;
    pthread_cond_init(&ma_variable_de_condition, NULL); // NULL pour les attributs par défaut
    ```

    2. **Attendre sur une variable de condition** : Un thread peut attendre qu'une certaine condition soit remplie en utilisant `pthread_cond_wait`. Cette fonction libère le mutex associé au thread et le met en attente de la notification. Par exemple :

    ```c
    pthread_mutex_lock(&monMutex); // Verrouillez le mutex avant d'attendre
    while (!condition_souhaitee) {
        pthread_cond_wait(&ma_variable_de_condition, &monMutex);
    }
    // Une fois réveillé, le mutex est de nouveau verrouillé.
    ```

    3. **Signaler une condition remplie** : Un autre thread peut signaler que la condition souhaitée est remplie en utilisant `pthread_cond_signal` ou `pthread_cond_broadcast`. Cette notification réveille les threads en attente. Par exemple :

    ```c
    pthread_mutex_lock(&monMutex); // Verrouillez le mutex avant de signaler
    condition_souhaitee = 1; // Modification de la condition
    pthread_cond_signal(&ma_variable_de_condition); // Réveiller un thread en attente
    pthread_mutex_unlock(&monMutex); // Déverrouillez le mutex
    ```

    4. **Libération d'une variable de condition** : Une fois que vous avez terminé d'utiliser une variable de condition, vous devriez la libérer en utilisant `pthread_cond_destroy`. Par exemple :

    ```c
    pthread_cond_destroy(&ma_variable_de_condition);
    ```






## 3. les fonctions de varaibles de condition :



1. `pthread_cond_wait`:

- **fonctionnement :**

    - La fonction `pthread_cond_wait` en C est utilisée pour mettre un thread en attente sur une variable de condition jusqu'à ce qu'un autre thread le réveille en modifiant la condition associée. 

    - Elle est s utilisée en conjonction avec un mutex (verrou) pour synchroniser les threads.

    - **fonctionnement :**

        1. **Verrouillage du mutex** : Avant d'appeler `pthread_cond_wait`, le thread doit verrouiller un mutex en utilisant `pthread_mutex_lock`. Le mutex est nécessaire pour éviter les conflits de données et pour coordonner l'accès aux ressources partagées ou aux données sur lesquelles la condition est basée.

        2. **Attente sur la variable de condition** : Lorsque le thread atteint un point où il souhaite attendre une certaine condition, il appelle `pthread_cond_wait` en passant la variable de condition correspondante et le mutex verrouillé. À ce stade, le mutex est automatiquement déverrouillé par `pthread_cond_wait`, permettant ainsi à d'autres threads d'accéder au mutex si nécessaire.

        3. **Mise en attente et déverrouillage du mutex** : Le thread est mis en attente sur la variable de condition, ce qui signifie qu'il passe dans un état de sommeil jusqu'à ce qu'un autre thread le réveille en modifiant la condition et en appelant `pthread_cond_signal` ou `pthread_cond_broadcast`. Pendant cette attente, le mutex est déverrouillé, ce qui permet à d'autres threads d'accéder à des ressources protégées par le mutex.

        4. **Réveil par un autre thread** : Lorsqu'un autre thread modifie la condition souhaitée et appelle `pthread_cond_signal` (pour réveiller un seul thread en attente) ou `pthread_cond_broadcast` (pour réveiller tous les threads en attente), le thread en attente est réveillé.

        5. **Verrouillage du mutex à nouveau** : Après avoir été réveillé, le thread réacquiert le mutex pour continuer son exécution. À ce stade, le mutex est à nouveau verrouillé, et le thread est prêt à continuer son travail en sachant que la condition souhaitée a été remplie.




- **signature :**


    ```c
    int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
    ```

    - `cond` : C'est un pointeur vers une variable de condition de type `pthread_cond_t` sur laquelle le thread actuel attend.

    - `mutex` : C'est un pointeur vers le mutex de type `pthread_mutex_t` qui doit être verrouillé avant d'appeler `pthread_cond_wait`. 




2. `pthread_cond_signal` :

- **fonctionnement :**

    - La fonction `pthread_cond_signal` en C est utilisée pour réveiller un thread en attente sur une variable de condition. 

    - Elle permet à un thread de signaler qu'une certaine condition souhaitée est remplie, ce qui réveille un thread en attente sur la même variable de condition.

- **signature :**

    ```c
    int pthread_cond_signal(pthread_cond_t *cond);
    ```

    - `cond` : C'est un pointeur vers une variable de condition de type `pthread_cond_t` que vous souhaitez utiliser pour signaler.







3. `pthread_cond_brodcast` :

- **fonctionnement :**

    - La fonction `pthread_cond_broadcast` en C est utilisée pour réveiller tous les threads en attente sur une variable de condition donnée. 

    - Elle permet à un thread de signaler que la condition souhaitée est remplie, réveillant ainsi tous les threads en attente sur la même variable de condition. 

    - Contrairement à `pthread_cond_signal`, qui réveille un seul thread en attente (généralement le premier thread qui est entré en attente), `pthread_cond_broadcast` réveille tous les threads en attente sur la variable de condition. 
    
    - Cela peut être utile dans des situations où plusieurs threads attendent la même condition et doivent tous être réveillés lorsque cette condition est remplie.


- **signature :**


    ```c
    int pthread_cond_broadcast(pthread_cond_t *cond);
    ```

    - `cond` : C'est un pointeur vers une variable de condition de type `pthread_cond_t` que vous souhaitez utiliser pour signaler.






## 4. Exemple Complet : 

- un exemple simplifié de l'utilisation de variables de condition pour gérer un compte bancaire dans une situation multi-thread.

    - Supposons que vous ayez un compte bancaire avec un solde initial et que vous aimeriez permettre à plusieurs threads de déposer de l'argent sur le compte ou de retirer de l'argent tout en maintenant la cohérence du solde. 

    - Vous utiliserez une variable de condition pour gérer ces opérations et empêcher les retraits lorsque le solde est insuffisant.

```c
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t compte_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t solde_suffisant = PTHREAD_COND_INITIALIZER;
int solde = 0;

void *deposer(void *arg) {
    int montant = *((int *)arg);
    pthread_mutex_lock(&compte_mutex);
    solde += montant;
    printf("Dépôt de %d euros. Nouveau solde : %d euros.\n", montant, solde);
    pthread_cond_signal(&solde_suffisant); // Signale qu'un dépôt a eu lieu
    pthread_mutex_unlock(&compte_mutex);
    return NULL;
}

void *retirer(void *arg) {
    int montant = *((int *)arg);
    pthread_mutex_lock(&compte_mutex);
    while (solde < montant) {
        printf("Solde insuffisant. Attente...\n");
        pthread_cond_wait(&solde_suffisant, &compte_mutex); // Attend que le solde soit suffisant
    }
    solde -= montant;
    printf("Retrait de %d euros. Nouveau solde : %d euros.\n", montant, solde);
    pthread_mutex_unlock(&compte_mutex);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int montants[] = {100, 50, 200};

    // Créez trois threads pour effectuer des opérations sur le compte
    for (int i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            pthread_create(&threads[i], NULL, deposer, &montants[i]);
        } else {
            pthread_create(&threads[i], NULL, retirer, &montants[i]);
        }
    }

    // Attendez que tous les threads aient terminé
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
```

Dans cet exemple :

1. Nous utilisons un mutex (`compte_mutex`) pour protéger l'accès concurrentiel au solde du compte.

2. Lorsque des dépôts sont effectués, nous signalons que le solde a été modifié à l'aide de `pthread_cond_signal`.

3. Lors des retraits, nous utilisons `pthread_cond_wait` pour attendre que le solde soit suffisant. Si le solde est insuffisant, le thread est mis en attente jusqu'à ce qu'un dépôt ait lieu et signale que le solde est suffisant.

4. Le programme crée trois threads pour simuler des opérations de dépôt et de retrait. Chaque thread effectue une opération sur le compte et imprime le solde résultant.



### RQ : 


- Les variables de condition sont utiles pour éviter une utilisation intensive du processeur dans les boucles d'attente actives (polling). Au lieu de vérifier constamment une condition dans une boucle, un thread peut attendre passivement jusqu'à ce qu'il soit réveillé par un autre thread lorsque la condition est remplie. Cela réduit la consommation de ressources CPU et améliore l'efficacité de la synchronisation entre threads.