# cour 06 : Rédrictions :

## 1. Introduction :

- La redirection en C pour un processus vous permet de rediriger les entrées/sorties standard (stdin, stdout, stderr) d'un processus vers des fichiers plutôt que vers les canaux par défaut (clavier et écran). 

- Cela peut être utile pour enregistrer la sortie d'un programme dans un fichier, ou pour lire l'entrée depuis un fichier au lieu du clavier.

- Pour réaliser une redirection en C, vous pouvez utiliser la fonction `dup2()`, qui permet de dupliquer un descripteur de fichier sur un autre descripteur de fichier. 



## 2. la fonction `dup2()` :

- La fonction `dup2` en langage C est utilisée pour dupliquer (ou rediriger) un descripteur de fichier vers un autre descripteur de fichier. Elle permet de rediriger une sortie (par exemple, `stdout` ou `stderr`) vers un fichier ou un tube (pipe), ou de dupliquer un descripteur de fichier ouvert vers un autre numéro de descripteur de fichier.

- La signature de la fonction `dup2` est la suivante :

```c
#include <unistd.h>

int dup2(int oldfd, int newfd);
```

- `oldfd` est le descripteur de fichier existant que vous souhaitez dupliquer.
- `newfd` est le numéro de descripteur de fichier vers lequel vous souhaitez dupliquer `oldfd`.

La fonction `dup2` fonctionne en dupliquant `oldfd` dans `newfd`. Si `newfd` est déjà ouvert, `dup2` ferme d'abord `newfd` avant de le dupliquer. Cela garantit que `newfd` soit associé à `oldfd`.


- un exemple d'utilisation de `dup2` pour rediriger la sortie standard (`stdout`) vers un fichier :

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Ouvrir (ou créer) un fichier pour la sortie
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // Rediriger stdout (descripteur 1) vers le descripteur de fichier fd
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Erreur lors de la redirection de stdout");
        exit(1);
    }

    // À partir de maintenant, toute sortie écrite sur stdout sera dirigée vers "output.txt"
    printf("Ce message est écrit dans le fichier.\n");

    close(fd);  // Fermez le fichier après utilisation

    return 0;
}
```


## 3.  Redirection de la sortie standard  , de l'entrée standard  :


1. Redirection de la sortie standard (stdout) vers un fichier :

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Ouvre un fichier en écriture (crée s'il n'existe pas)
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    
    // Redirige stdout vers le descripteur de fichier fd
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Erreur lors de la redirection de stdout");
        exit(1);
    }
    
    // À partir de maintenant, toute sortie écrite sur stdout sera dirigée vers "output.txt"
    printf("Ce message est écrit dans le fichier.\n");

    close(fd);  // Fermez le fichier après utilisation
    return 0;
}
```

2. Redirection de l'entrée standard (stdin) depuis un fichier :

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Ouvre un fichier en lecture
    int fd = open("input.txt", O_RDONLY);
    
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    
    // Redirige stdin depuis le descripteur de fichier fd
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("Erreur lors de la redirection de stdin");
        exit(1);
    }
    
    // À partir de maintenant, toute lecture depuis stdin viendra du fichier "input.txt"
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("Donnée lue depuis le fichier : %s", buffer);
    }

    close(fd);  // Fermez le fichier après utilisation
    return 0;
}
```
