# cour 08 :**Le problème du producteur-consommateur:**

## 1. **Introduction:**

- Le problème du producteur-consommateur est un problème classique de synchronisation en informatique, souvent utilisé pour illustrer les défis de la programmation multithread. 

- Il implique deux types de threads, les **producteurs** et les **consommateurs**, qui partagent une zone de mémoire appelée **tampon**.

- **Objectif :**
L'objectif principal est de garantir que les producteurs et les consommateurs peuvent fonctionner de manière coordonnée et sécurisée, en évitant les conditions de concurrence, en protégeant l'accès au tampon et en assurant une utilisation rationnelle des ressources.


## 2.Acteurs :

1. **Producteur :**
   - Génère des données (ou des éléments) à un certain rythme.
   - Ajoute les données au tampon.

2. **Consommateur :**
   - Consomme les données du tampon à un certain rythme.

3. **Tampon :**
   - Zone de mémoire partagée entre les producteurs et les consommateurs.
   - Peut avoir une taille limitée (nombre fixe d'emplacements).

## 3.Problème :

- **Synchronisation :** 
    
    - Les producteurs ne doivent pas ajouter de données au tampon si celui-ci est plein. 
    
    - Les consommateurs ne doivent pas essayer de consommer s'il est vide.
  
- **Protection des Données :** 
    
    - Les accès concurrents au tampon par les producteurs et les consommateurs doivent être protégés pour éviter des conditions de concurrence.

- **Utilisation Rationnelle du Tampon :** 
    
    - Les producteurs et les consommateurs doivent travailler de manière coordonnée pour éviter la surproduction ou la sous-consommation.

## 4. Mécanismes de Synchronisation Utilisés :

1. **Sémaphores :**
   - Deux sémaphores peuvent être utilisés : un pour suivre le nombre d'emplacements vides dans le tampon (`sem_empty`) et un pour suivre le nombre d'emplacements occupés (`sem_full`).

2. **Mutex (Serrure de Section Critique) :**
   - Un mutex peut être utilisé pour assurer une section critique lors de l'ajout ou de la suppression d'éléments du tampon.

## 5.Processus :

1. **Initialisation :**
   - Initialiser les sémaphores (`sem_empty` et `sem_full`) et le mutex.
   - Créer des threads producteurs et consommateurs.

2. **Boucle de Production :**
   - Le producteur génère des données.
   - Le producteur attend que l'espace soit disponible dans le tampon (`sem_empty`).
   - Le producteur acquiert le mutex pour ajouter les données au tampon.
   - Le producteur libère le mutex.
   - Le producteur signale qu'un emplacement est occupé dans le tampon (`sem_full`).

3. **Boucle de Consommation :**
   - Le consommateur attend que des données soient disponibles dans le tampon (`sem_full`).
   - Le consommateur acquiert le mutex pour consommer les données du tampon.
   - Le consommateur libère le mutex.
   - Le consommateur signale qu'un emplacement est vide dans le tampon (`sem_empty`).

4. **Libération des Ressources :**
   - Lorsque les threads ont terminé, libérer les ressources (sémaphores, mutex).

## 6.Solution :


```c
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define N 2

sem_t semFull ;
sem_t semEmpty ;

pthread_mutex_t m ;

/*------- tampon :------*/
int tampon[10];
int count = 0 ;

void* productuer(void* args)
{
    /*---------- production :----------------- */
    while(1)
    {
   
        int x = rand() % 100 ; /*------ génere un nombre aléatoie entre 0 , 100 -------*/
        sleep(1);
        
        sem_wait(&semEmpty);
        
        pthread_mutex_lock(&m);
        
        /*--------- Zone critique ------*/
        tampon[count] = x ;
        count++;
        
        printf("Production du %d \n" , x);


        pthread_mutex_unlock(&m);
        sem_post(&semFull);
    }


}



void* consommateur(void* args)
{
    /*------------- consommation:----------- */
    while(1)
    {
        int y ;

        sem_wait(&semFull);
        pthread_mutex_lock(&m);

        /*--------- zone critique : -----------*/ 
        y = tampon[count -1];
        count--;    

        pthread_mutex_unlock(&m);
        
        sem_post(&semEmpty);

        printf("Consomation du : %d \n", y);
        // sleep(1);
    }


}

int main(void)
{

    /*
    SemFull : controle le nombre cases déja utilisés par le productuer 
    SemFull : bloque le consommateur si le valeur égale à 0 
    semFull : la valeur initiale égale à 0 .    
    */
    sem_init(&semFull , 0 , 0); 
    
    /*
    semEmpty : controle le nombre des ressources disponibles (ie les cases Empty )
    semEmpty : bloque le productuer si le nombre des ressources Empty éfale à 0 
    semEmpty :  la valeur initiale est égale à la valeur initiale des ressources (ici 10);
    */
    sem_init(&semEmpty , 0 ,  10); 

    pthread_mutex_init(&m , NULL);

    /*-------- pour génerer des nombres aléatoires :------------*/
    srand(time(NULL));

    pthread_t th[N];


    for(int i =0 ; i< N ; i++)
    {
        if(i > 0)
        {
            if(pthread_create(&th[i] , NULL ,&productuer, NULL )!=0)
            {
                printf("Faild to create Thread %d " , i);
                return 1 ;
            }
        }
        else
        {
            if(pthread_create(&th[i] , NULL ,&consommateur, NULL )!=0)
            {
                printf("Faild to create Thread %d " , i);
                return 1 ;
            }         
        }
    }


    for(int i =0 ; i<N ; i++)
    {
        if(pthread_join(th[i] , NULL)!=0)
        {
            printf("Faild to join Thread %d \n", i);
        }
    }


    pthread_mutex_destroy(&m);

    return 0 ;

}

```

- **Illustration avec des Sémaphores :**

L'utilisation de deux sémaphores (`sem_empty` et `sem_full`) permet de contrôler l'accès au tampon de manière à éviter la surproduction et la sous-consommation. Les sémaphores agissent comme des compteurs pour suivre le nombre d'emplacements vides et occupés dans le tampon, facilitant ainsi la synchronisation entre producteurs et consommateurs.

```c
sem_t sem_empty, sem_full; // Initialisés en fonction de la taille du tampon
pthread_mutex_t mutex; // Mutex pour protéger l'accès au tampon
```

Le producteur effectue `sem_wait(&sem_empty)` avant d'ajouter une donnée au tampon et `sem_post(&sem_full)` après avoir ajouté une donnée. Le consommateur effectue `sem_wait(&sem_full)` avant de consommer une donnée et `sem_post(&sem_empty)` après avoir consommé une donnée.
