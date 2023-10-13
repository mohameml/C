# cour 03 : pipe 


## 1.  Les tuyaux :

- Les **tuyaux** (pipes en anglais) sont un mécanisme de communication interprocessus (IPC) qui permet à deux processus de partager des données de manière unidirectionnelle. 


- Il existe deux types principaux de tuyaux :

1. **Tuyaux anonymes (pipes anonymes)** :
   - Les tuyaux anonymes sont créés à l'aide de la fonction système `pipe()`.
   - Ils sont unidirectionnels, ce qui signifie que les données ne peuvent être transférées que dans une seule direction, du processus père vers le processus fils, ou vice versa.
   - Les données sont lues à partir d'une extrémité du tuyau (lecteur) et écrites dans l'autre extrémité (écrivain).
   - Ils sont principalement utilisés pour la communication entre un processus père et un processus fils lorsqu'un processus crée un nouveau processus à l'aide de `fork()`.

2. **Tuyaux nommés (FIFO)** :
   - Les tuyaux nommés, également appelés FIFO (pour "first in, first out"), sont créés en tant que fichiers spéciaux dans le système de fichiers.
   - Ils sont bidirectionnels, ce qui signifie que les données peuvent être transférées dans les deux sens, à la fois de l'écrivain vers le lecteur et vice versa.
   - Ils sont identifiés par un nom de fichier dans le système de fichiers et peuvent être partagés entre n'importe quel processus tant qu'ils ont les autorisations appropriées.
   - Ils sont utilisés pour la communication entre des processus indépendants qui peuvent être exécutés séparément et qui se connectent via le tuyau nommé.



## 2. la fonction ``pipe()`` en C :

- La fonction `pipe` en langage C est utilisée pour créer un tuyau (pipe) anonyme, qui permet la communication unidirectionnelle entre deux processus. 

- Un tuyau est un canal de communication qui peut être utilisé pour transmettre des données d'un processus à un autre, généralement du processus père à un processus fils ou vice versa.


- la signature de la fonction `pipe` :

```c
#include <unistd.h>

int pipe(int pipefd[2]);
```

- `pipefd` est un tableau d'entiers de deux éléments qui sera utilisé pour stocker **les descripteurs de fichiers du tuyau**: `pipefd[0]` est le descripteur de lecture (lecteur), et `pipefd[1]` est le descripteur d'écriture (écrivain).

- La fonction `pipe` crée un tuyau et associe automatiquement les descripteurs de fichiers au tuyau. Le processus père peut utiliser `pipefd[1]` pour écrire des données dans le tuyau, tandis que le processus fils peut utiliser `pipefd[0]` pour lire ces données.


- un exemple simple d'utilisation de `pipe` pour créer un tuyau et effectuer une communication basique entre un processus père et un processus fils :

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>




int main(void)
{
    int fd[2];

    int status = pipe(fd);

    if(status==-1)
    {
        perror("Error fro the opening the pipe \n");
    }


    int id = fork();

    if(id==0)
    {
        // the child processus 
        // chlid will write in the pipe
        close(fd[0]); // closing the file descritption of raeding in the pipe 
        int x ;
        printf("Please write your number : ");
        scanf("%d",&x);
        write(fd[1], &x , sizeof(int));
        close(fd[1]); // in the end , you must closing the file descritpion of writhing in the pipe 
    }
    else 
    {
        // the case of the parent processus 
        close(fd[1]);
        int y ;
        read(fd[0], &y , sizeof(int));
        close(fd[0]);
        printf("Got from the processus child in the pipe %d \n", y);
    }

    return 0 ;
}
```



### RQ :

- **Un descripteur de fichier  :** est un identifiant numérique utilisé par un système d'exploitation pour représenter un fichier ouvert ou une ressource de fichier.

- **les descripteur standard :**


    - ``STDIN_FILENO`` : Ce descripteur de fichier standard représente l'entrée standard, généralement liée au clavier.


    - ``STDOUT_FILENO`` : Ce descripteur de fichier standard représente la sortie standard, généralement liée à l'écran ou à la console.


    - ``STDERR_FILENO`` : Ce descripteur de fichier standard représente la sortie d'erreur standard, également généralement liée à l'écran ou à la console.


- **les fonctions :**
    
    - **write() :**
    
     - La signature de la fonction `write()` en langage C est la suivante :

        ```c
        #include <unistd.h>

        ssize_t write(int fd, const void *buf, size_t count);
        ```

        - `fd` est le descripteur de fichier sur lequel écrire les données. Cela peut être un descripteur de fichier pour un fichier, un tuyau (pipe), un socket ou un autre type de flux de données.

        - `buf` est un pointeur vers les données à écrire.

        - `count` est le nombre d'octets à écrire.

    - La fonction `write()` renvoie le nombre d'octets écrits avec succès dans le cas d'une écriture réussie. En cas d'erreur, elle renvoie -1 et place le code d'erreur dans la variable globale `errno`.



    - **read() :**

        - La signature de la fonction `read()` en langage C est la suivante :

            ```c
            #include <unistd.h>

            ssize_t read(int fd, void *buf, size_t count);
            ```

            - `fd` est le descripteur de fichier depuis lequel lire les données. Cela peut être un descripteur de fichier pour un fichier, un tuyau (pipe), un socket ou un autre type de flux de données.

            - `buf` est un pointeur vers la mémoire où les données lues seront stockées.

            - `count` est le nombre d'octets à lire.

        - La fonction `read()` renvoie le nombre d'octets lus avec succès dans le cas d'une lecture réussie. En cas d'erreur, elle renvoie -1 et place le code d'erreur dans la variable globale `errno`.



    - **close() :***

        - La signature de la fonction `close()` en langage C est la suivante :

            ```c
            #include <unistd.h>

            int close(int fd);
            ```

            - `fd` est le descripteur de fichier que vous souhaitez fermer. Un descripteur de fichier est un identifiant associé à un fichier ouvert, un tuyau (pipe), un socket ou un autre type de flux de données.

        - La fonction `close()` est utilisée pour fermer un descripteur de fichier ouvert. Après avoir fermé un descripteur de fichier, il n'est plus possible de l'utiliser pour lire ou écrire des données. Il est recommandé de fermer les descripteurs de fichier après leur utilisation pour éviter des fuites de ressources.
        - return - 1 en cas d'errure .




