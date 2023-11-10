# cour 02 : condition de concurrence 


- **Définition :**

    - **Une condition de concurrence:** est un problème en programmation concurrente. Elle se produit lorsqu'au moins deux threads ou processus accèdent simultanément à des données partagées ou des ressources sans synchronisation appropriée, ce qui peut entraîner des résultats inattendus et incorrects. 

    - Les conditions de concurrence se produisent en raison de l'ordre non déterministe d'exécution des threads et peuvent causer des problèmes tels que des lectures ou des écritures incorrectes de données partagées.



- **exemple simple pour illustrer une ``race condition`` :**

voici le code en C d'un programme qui contient deux threads qui accédent simultant à la variable ``sum``:

```c

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


int sum = 0 ;

void* routine()
{   
    for(int i=0 ; i<1000000;i++)
    {
        
        sum++; 
        // 	movl sum(%rip), %eax
        // addl	$1, %eax
        // movl	%eax, sum(%rip)

    }


    return NULL ;
}



int main(void)
{
    pthread_t t1 , t2 ;

    pthread_create(&t1 , NULL , &routine , NULL);
    
    pthread_create(&t2 , NULL , &routine , NULL);

    pthread_join(t1,NULL);
    pthread_join(t2, NULL);

    printf("%d \n", sum);
    return 0 ;
}

```

- l'éxecution de code en dessus  donne une résulat incohréante , et à chaque exécution il donne une résulatt différent de la résulatt précedent :
il s'agit de `race condition`.

![image](race.png)


- **expliquation:**

    - La situation  observez dans le code  est effectivement due à une condition de concurrence (race condition). 

    - Une race condition se produit lorsque plusieurs threads tentent d'accéder et de modifier une variable partagée en même temps, sans aucune synchronisation appropriée. 

    - L'ordre d'exécution des threads peut varier à chaque exécution, ce qui peut entraîner des résultats incohérents.

    - Dans le  code, deux threads (`t1` et `t2`) exécutent la fonction `routine` simultanément. 

    - Cette fonction incrémente la variable partagée `sum` en utilisant l'opérateur `sum++`. 

    - Cet opérateur n'est pas une opération atomique, ce qui signifie que plusieurs instructions sont nécessaires pour effectuer l'incrémentation, et ces instructions peuvent être interrompues par d'autres threads entre-temps:

    en faite l'opérateur `sum++` est équivalent en assembleur à 3 instructions :
    ```c
        movl sum(%rip), %eax // récupération de sum à partir de la mémoire 
        addl	$1, %eax   // on effecute sum + 1;
        movl	%eax, sum(%rip) // puis on écrit la nouvelle valeur dans le mémoire .

    ```

- voici un scénario de `race condition` entre `Thread A` et `Thread B `: 

    1. ``Thread A`` lit la valeur actuelle de `sum` (disons 100) dans son registre.
    2. ``Thread B`` fait de même et obtient la même valeur (100) dans son registre.
    3. ``Thread A`` incrémente la valeur dans son registre à 101.
    4. Cependant, avant que ``Thread A`` puisse mettre à jour la variable `sum`, il est **interrompu** par le commutateur de contexte du système d'exploitation.
    5. ``Thread B`` est maintenant en cours d'exécution et incrémente également la valeur dans son registre à 101.
    6. ``Thread B`` met à jour la variable `sum` à 101.
    7. Aprés plusieurs opérations effecutent par ``Thread B`` ex : sum mnt égale 200.
    7. Enfin, ``Thread A`` est repris et met à jour la variable `sum` à 101 , écrasant le travail effectué par ``Thread B``.


### RQ :

- Pour corriger cette **race condition**, on doit  utiliser un mécanisme de synchronisation tel qu'un **mutex (verrou)** pour assurer un accès exclusif à la variable `sum` pendant l'incrémentation. 














