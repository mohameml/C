# cour 02 : ``wait``



## 1. **Définition :**

- La fonction `wait()` en langage C est utilisée pour suspendre l'exécution d'un processus parent jusqu'à ce qu'un de ses processus fils se termine. 


- Elle permet au processus parent d'attendre la fin de l'exécution de l'un de ses fils avant de continuer son propre travail. 

- La fonction `wait()` est souvent utilisée en conjonction avec `fork()` pour gérer des processus fils.




- **la signature de la fonction `wait()` :**

 ```c
    #include <sys/types.h>
    #include <sys/wait.h>

    pid_t wait(int *status);
```

- `status` est un pointeur vers une variable où le statut de sortie du processus fils sera stocké. Si vous n'avez pas besoin de récupérer ce statut, vous pouvez passer `NULL`.

- La fonction `wait()` renvoie le PID (identifiant de processus) du processus fils qui s'est terminé. Si le processus parent a plusieurs processus fils, `wait()` attendra la terminaison de n'importe lequel d'entre eux.

- La fonction `wait()` est bloquante, ce qui signifie que si aucun de ses fils n'est encore terminé, le processus parent sera mis en attente jusqu'à ce que l'un de ses fils se termine.

Voici un exemple d'utilisation de `fork()` et `wait()` pour créer et attendre un processus fils :

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Erreur lors de la création du processus fils");
        exit(1);
    }

    if (pid == 0) {
        // Code exécuté par le processus fils
        printf("Je suis le processus fils (PID : %d).\n", getpid());
        exit(0); // Terminer le processus fils
    } else {
        // Code exécuté par le processus parent
        printf("Je suis le processus parent (PID : %d).\n", getpid());

        int status;
        pid_t child_pid = wait(&status);

        if (child_pid == -1) {
            perror("Erreur lors de l'attente du processus fils");
            exit(1);
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Le processus fils (PID : %d) s'est terminé avec le statut : %d.\n", child_pid, exit_status);
        }
    }

    return 0;
}
```

Dans cet exemple, le processus parent crée un processus fils avec `fork()`. Le processus parent attend ensuite la terminaison du processus fils en utilisant `wait()`. Le statut de sortie du processus fils est stocké dans la variable `status`, que nous pouvons vérifier à l'aide de `WIFEXITED` pour déterminer si le processus fils s'est terminé normalement, et obtenir le code de sortie à l'aide de `WEXITSTATUS`.



## 2.  **récupere l'état du child :**


Les fonctions `WIFEXITED` et `WEXITSTATUS` font partie des fonctions de la bibliothèque standard C (notamment `waitpid()`) et sont utilisées pour examiner le statut de terminaison d'un processus fils (child process) après son exécution dans un processus parent. 

1. **`WIFEXITED` :**

   - Prototype : `int WIFEXITED(int status);`
   - Description : 
        - Cette fonction est utilisée pour vérifier si un processus fils s'est terminé normalement. 
        
        - Elle prend en argument le statut d'un processus (généralement renvoyé par `wait()`) 
        
        - et renvoie :
            * une valeur différente de zéro si le processus fils s'est terminé normalement.
   - Retour : Si `WIFEXITED(status)` renvoie une valeur différente de zéro, cela signifie que le processus fils s'est terminé normalement.

2. **`WEXITSTATUS` :**

   - Prototype : `int WEXITSTATUS(int status);`
   - Description : Cette fonction est utilisée pour récupérer le code de sortie (exit code) d'un processus fils qui s'est terminé normalement. Elle prend en argument le statut d'un processus (généralement renvoyé par `wait`) et renvoie le code de sortie du processus fils.
   - Retour : 
        - Le code de sortie du processus fils (0 si tout passe bien ). 
        
        - Vous pouvez utiliser cette valeur pour déterminer comment s'est terminé le processus et récupérer des informations sur son exécution.

Voici un exemple d'utilisation de `WIFEXITED` et `WEXITSTATUS` en conjonction avec `waitpid()` pour attendre la fin d'un processus fils et récupérer son code de sortie :

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Code du processus fils
        printf("Je suis le processus fils.\n");
        exit(42);
    } else if (child_pid > 0) {
        // Code du processus parent
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Le processus fils s'est terminé avec le code de sortie : %d\n", exit_status);
        } else {
            printf("Le processus fils ne s'est pas terminé normalement.\n");
        }
    } else {
        perror("Erreur lors de la création du processus fils");
        exit(1);
    }

    return 0;
}
```

Dans cet exemple, le processus parent attend la fin du processus fils et utilise `WIFEXITED` pour vérifier si le processus fils s'est terminé normalement. Si c'est le cas, il utilise `WEXITSTATUS` pour récupérer le code de sortie du processus fils (dans cet exemple, 42).

### 3. la fonction `waitpid` :


- La fonction `waitpid` est une fonction en C utilisée pour attendre qu'un processus fils se termine dans un programme qui crée des processus en utilisant la fonction `fork`. 

- `waitpid` permet au processus parent de bloquer son exécution jusqu'à ce que le processus fils spécifié se termine. 

- Cette fonction est couramment utilisée pour la gestion des processus dans les programmes multi-processus.

- **La syntaxe de la fonction `waitpid` est la suivante :**

```c
#include <sys/types.h>
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options);
```

- `pid` : C'est l'ID du processus que vous souhaitez attendre. Il peut prendre différentes valeurs :
  - Si `pid` est positif, il attend le processus fils dont l'ID de processus correspond à `pid`.
  - Si `pid` est égal à -1, il attend n'importe quel processus fils.
  - Si `pid` est égal à 0, il attend n'importe quel processus fils dans le même groupe de processus que le processus appelant.
  - Si `pid` est négatif, il attend n'importe quel processus fils du groupe de processus dont le groupe est l'opposé de `pid`.

- `status` : C'est un pointeur vers une variable entière où les informations sur la terminaison du processus fils seront stockées. Il peut être utilisé pour récupérer le code de sortie du processus fils ou d'autres informations sur sa terminaison.

- `options` : Il s'agit d'un ensemble de drapeaux qui contrôlent le comportement de la fonction. Les options courantes incluent `WNOHANG` (pour un appel non bloquant) et `WUNTRACED` (pour inclure les processus arrêtés).

- La fonction `waitpid` bloque le processus parent jusqu'à ce que le processus fils se termine. Une fois le processus fils terminé, `waitpid` renvoie l'ID du processus fils qui s'est terminé, ou -1 en cas d'erreur. Le statut de terminaison du processus fils est stocké dans la variable pointée par `status`.

- **Exemple d'utilisation de `waitpid` :**

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // Code du processus fils
        printf("Je suis le processus fils.\n");
        // Faire des tâches...
        return 42; // Code de sortie du processus fils
    } else {
        // Code du processus parent
        int status;
        pid_t terminated_pid = waitpid(child_pid, &status, 0);

        if (terminated_pid == -1) {
            perror("waitpid");
            return 1;
        }

        if (WIFEXITED(status)) {
            printf("Le processus fils avec PID %d s'est terminé avec le code de sortie : %d\n", terminated_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
```

Dans cet exemple, le processus parent crée un processus fils à l'aide de `fork` et utilise ensuite `waitpid` pour attendre que le processus fils se termine. Une fois le processus fils terminé, il récupère le code de sortie du processus fils à partir de `status`.