# cour 04 : FIFOS 


## 1. Définition :

- Le  **FIFOs :** est utilisé pour désigner les tuyaux nommés (FIFOs) en langage C et dans les systèmes Unix. 

- Un FIFO est un mécanisme de communication interprocessus qui permet à plusieurs processus de partager des données dans l'ordre où elles ont été insérées, c'est-à-dire que les données sont lues dans l'ordre où elles ont été écrites.




## 2. les carctéristiques de FIFOS :

1. **Tuyaux nommés (FIFOs)** : Les FIFOs sont des fichiers spéciaux dans le système de fichiers qui sont utilisés pour la communication entre processus. Ils sont nommés parce qu'ils ont un nom de fichier associé dans le système de fichiers, ce qui permet à plusieurs processus d'y accéder en utilisant ce nom.

2. **Communication bidirectionnelle** : Contrairement aux tuyaux anonymes (pipe ) , les FIFOs permettent la communication bidirectionnelle entre les processus. Plusieurs processus peuvent ouvrir un même fichier FIFO en lecture et écriture, ce qui permet d'échanger des données dans les deux sens.

3. **Ordre FIFO** : Les données écrites dans un fichier FIFO sont lues dans l'ordre où elles ont été écrites, d'où le nom "First In, First Out." Cela garantit que les données sont traitées dans l'ordre où elles ont été insérées.

4. **Création et ouverture** : Les FIFOs sont créés à l'aide de la fonction `mkfifo()` et ouverts avec `open()`. Pour les utiliser, vous devez d'abord créer un fichier FIFO avec `mkfifo` et ensuite ouvrir le fichier FIFO pour la communication avec `open()`.

5. **open() pour les fifos:**
 
    - Lorsqu'un processus ouvre un fichier FIFO à l'aide de la fonction `open()` en mode lecture (`O_RDONLY`) ou écriture (`O_WRONLY`), le comportement est bloquant si l'autre extrémité du FIFO (soit en lecture, soit en écriture) n'est pas ouverte par un autre processus. 

    - Cela signifie que si un processus tente d'ouvrir un FIFO en lecture alors qu'aucun processus n'a encore ouvert l'autre extrémité en écriture, l'ouverture bloquera jusqu'à ce que l'extrémité en écriture soit ouverte par un autre processus, et vice versa.

    - Cela permet de garantir que la communication est bien synchronisée entre les processus. Un processus en attente de lecture ne pourra lire les données que lorsque l'extrémité en écriture sera disponible, et vice versa. 


6. **Utilisation courante** : Les FIFOs sont souvent utilisés dans des scénarios où plusieurs processus doivent communiquer et échanger des données, par exemple, pour coordonner des tâches entre plusieurs processus ou pour la communication entre des programmes indépendants.



## 3. Création d'un FIFO : `mkfifo`

- La fonction `mkfifo` en langage C est utilisée pour créer un tuyau nommé (FIFO, "First In, First Out") dans le système de fichiers. Contrairement aux tuyaux anonymes créés avec `pipe()`, 

- les tuyaux nommés sont des fichiers spéciaux dans le système de fichiers qui peuvent être partagés entre plusieurs processus.

- la signature de la fonction `mkfifo` :

```c
#include <sys/types.h>
#include <sys/stat.h>

int mkfifo(const char *pathname, mode_t mode);
```

- `pathname` est le chemin du fichier FIFO à créer dans le système de fichiers.

- `mode` :

    - Le paramètre `mode` dans la fonction `mkfifo` est utilisé pour spécifier les autorisations ou les permissions du fichier FIFO (tuyau nommé) que vous êtes en train de créer. 
    
    - Les autorisations définies par le `mode` déterminent qui peut lire, écrire ou exécuter le fichier FIFO. En particulier, le `mode` est un masque de bits qui contrôle les autorisations d'accès au fichier.
    
    - Le `mode` dans la fonction `mkfifo` est généralement défini sous forme de constante octale (en base 8) pour indiquer les autorisations pour différents types d'utilisateurs : **propriétaire**, **groupe** et **autres**. 
    
    - Les chiffres octaux vont de 0 à 7, et chaque chiffre représente les autorisations de lecture, d'écriture et d'exécution. Voici comment les chiffres dans le `mode` sont interprétés :

        - Le premier chiffre représente les autorisations du propriétaire du fichier.
        - Le deuxième chiffre représente les autorisations pour le groupe.
        - Le troisième chiffre représente les autorisations pour les autres utilisateurs (ceux qui ne sont pas le propriétaire ni dans le groupe).

        - Chaque chiffre peut avoir une valeur de 0 à 7, où 0 signifie aucune autorisation et 7 signifie toutes les autorisations (lecture, écriture et exécution).



 
- La fonction `mkfifo` crée un fichier FIFO (un tuyau nommé) avec les autorisations spécifiées. Ce fichier FIFO peut être ouvert et utilisé par différents processus pour effectuer une communication bidirectionnelle. 


- un exemple d'utilisation de la fonction `mkfifo` pour créer un fichier FIFO et l'ouvrir pour la communication :

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifo_path = "/tmp/myfifo"; // Chemin du fichier FIFO

    if (mkfifo(fifo_path, S_IRUSR | S_IWUSR) == -1) {
        perror("Erreur lors de la création du fichier FIFO");
        exit(1);
    }

    int fd = open(fifo_path, O_RDWR); // Ouvrir le fichier FIFO en lecture et écriture

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier FIFO");
        exit(1);
    }

    // Effectuer la communication avec le fichier FIFO

    close(fd); // Fermer le fichier FIFO

    return 0;
}
```





## 4. la fonction `open()` :

- La fonction `open()` en langage C est utilisée pour ouvrir ou créer un fichier sur le système de fichiers. 

- Elle permet aux processus d'accéder à des fichiers existants ou de créer de nouveaux fichiers, selon les options spécifiées lors de l'ouverture. La signature de la fonction `open()` est la suivante :

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags, mode_t mode);
```

- `pathname` est le chemin du fichier à ouvrir ou à créer.

- `flags` sont les indicateurs qui contrôlent le comportement de l'ouverture du fichier, tels que les options de lecture, d'écriture, de création, etc. Ces indicateurs sont spécifiés en utilisant des constantes définies dans la bibliothèque `fcntl.h`:

    - **O_RDONLY** # Ouvrir le fichier en mode lecture seule (Read-Only).

    - **O_WRONLY** # Ouvrir le fichier en mode écriture seule (Write-Only).

    - **O_RDWR** # Ouvrir le fichier en mode lecture et écriture (Read-Write).

    - **O_CREAT**  #  Créer le fichier s'il n'existe pas


- `mode` est un masque de bits qui spécifie les autorisations du fichier à créer s'il n'existe pas déjà. Cela est généralement utilisé lors de la création d'un nouveau fichier.

- La fonction `open()` renvoie **un descripteur de fichier**, qui est un entier qui identifie le fichier ouvert. Ce descripteur de fichier est ensuite utilisé pour effectuer des opérations de lecture, d'écriture ou d'autres opérations sur le fichier.

- un exemple simple d'utilisation de la fonction `open()` pour ouvrir un fichier en lecture :

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    int fd = open("example.txt", O_RDONLY);

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // Effectuer des opérations de lecture sur le fichier

    close(fd); // Fermer le fichier

    return 0;
}
```

