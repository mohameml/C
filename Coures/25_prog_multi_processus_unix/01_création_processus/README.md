# cour 01 : Création de processus 

## 1. Définition d'un Processus :

- Un processus est une instance en cours d'exécution d'un programme informatique sur un système d'exploitation. En d'autres termes, un processus est un programme en cours d'exécution avec sa propre mémoire, son propre espace d'adressage, ses ressources allouées, et son propre contexte d'exécution. 

- Les processus sont la base de la gestion des tâches et de l'exécution de programmes sur un système informatique.


- quelques points clés à retenir à propos des processus :

1. **Isolation** : Chaque processus s'exécute dans son propre espace d'adressage mémoire, ce qui signifie qu'il ne peut pas accéder directement à la mémoire d'autres processus. Cela garantit l'isolation et la sécurité des données entre les processus.

2. **Indépendance** : Les processus sont indépendants les uns des autres, ce qui signifie que la panne ou l'arrêt d'un processus n'affecte généralement pas les autres processus en cours d'exécution.

3. **Gestion des ressources** : Les processus ont leurs propres ressources allouées, telles que des fichiers ouverts, des descripteurs de fichiers, des identifiants de processus, etc. Le système d'exploitation est responsable de la gestion de ces ressources pour chaque processus.

4. **Multitâche** : Les systèmes d'exploitation modernes permettent l'exécution simultanée de plusieurs processus, offrant ainsi la possibilité de multitâche. Le système d'exploitation alloue du temps CPU à chaque processus de manière équitable.

5. **Communication interprocessus** : Les processus peuvent communiquer entre eux en utilisant des mécanismes de communication interprocessus tels que les sockets, les tubes (pipes), les files de messages, etc.

6. **Création et gestion** : Les processus sont créés par le système d'exploitation lorsqu'un programme est lancé. Le système d'exploitation gère leur cycle de vie, y compris leur création, leur exécution, leur suspension et leur terminaison.

7. **Identifiants de processus** : Chaque processus est associé à un identifiant de processus (PID) unique qui le distingue des autres processus en cours d'exécution sur le système. Les PID sont utilisés pour la gestion et le suivi des processus.



## 2. la fonction `fork()` :


- La fonction `fork()` est une fonction du langage C qui est principalement utilisée sur les systèmes Unix et Unix-like, notamment Linux. 

- Elle permet de créer un nouveau processus en copiant le processus appelant (appelé processus parent) pour créer un processus fils. Le processus parent et le processus fils s'exécutent simultanément et partagent une partie de leur état, mais ils ont des espaces mémoire distincts.

- La signature de la fonction `fork()` est la suivante :

```c
#include <unistd.h>

pid_t fork(void);
```

- `fork()` renvoie le PID (identifiant de processus) du processus fils au processus parent.
- `fork()` renvoie 0 au processus fils pour indiquer qu'il est le fils.
- En cas d'erreur, `fork()` renvoie -1.

 
- **fonctionne la fonction `fork()` :**

1. Lorsque vous appelez `fork()`, le système d'exploitation crée une copie du processus appelant, y compris son code, ses données, son contexte d'exécution et ses ressources. Le processus créé est une copie quasi identique du processus parent.

2. Le processus parent et le processus fils se poursuivent à partir du point où `fork()` a été appelé. Cependant, le PID retourné diffère. Le PID du processus parent est le PID du fils.

3. Les deux processus ont des espaces mémoire distincts. Toutes les modifications apportées à la mémoire dans l'un des processus n'affectent pas l'autre processus, sauf si des mécanismes de communication interprocessus (IPC) sont utilisés.

La fonction `fork()` est souvent utilisée pour créer des processus parallèles. Un exemple courant est le lancement de processus fils pour effectuer des tâches indépendantes dans un programme. Par exemple, un programme peut utiliser `fork()` pour diviser son travail en plusieurs processus parallèles pour améliorer les performances.


- **un exemple simple d'utilisation de `fork()` :**

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Erreur lors de la création du processus fils");
        return 1;
    }

    if (pid == 0) {
        // Code exécuté par le processus fils
        printf("Je suis le processus fils (PID : %d).\n", getpid());
    } else {
        // Code exécuté par le processus parent
        printf("Je suis le processus parent (PID : %d). Le PID de mon fils est : %d.\n", getpid(), pid);
    }

    return 0;
}
```

### RQ 1: 

- Lorsque vous appelez la fonction ``fork()`` plusieurs fois dans un programme, vous créez plusieurs processus fils, chacun étant une copie du processus parent à l'instant où ``fork()`` a été appelé. Cela peut entraîner la création d'une arborescence de processus, où chaque processus fils peut à son tour appeler fork() pour créer d'autres processus.

- **exemple** : Boucle simple
Que fait le code suivant ?
```c
for(i=0; i< n; i++) {
    fork();
}


```
Il crée $2^n$ processus 


- comment creér un n processus ? :
La bonne solution : tester la valeur de retour de fork


```c

for(i=0; i< n; i++) {
int pid = fork();
if (! pid) // pid == 0, on est dans le fils, on break
    break;
}

```



### RQ 2 : 
- **La bibliothèque "unistd.h":**
 
- La bibliothèque "unistd.h"(qui signifie "UNIX Standard") est une bibliothèque standard en langage C, principalement utilisée sur les systèmes d'exploitation de type UNIX, tels que Linux. Elle fournit un ensemble de fonctions qui sont principalement liées à l'interaction avec le système d'exploitation, notamment l'accès aux fichiers, la gestion des processus, la gestion des entrées/sorties, etc. Voici quelques-unes des fonctionnalités les plus couramment utilisées de la bibliothèque "unistd.h" :

1. **Accès aux fichiers et aux répertoires** :
   - `open()`, `close()`: Pour ouvrir et fermer des fichiers.
   - `read()`, `write()`: Pour lire à partir de fichiers ou écrire dans des fichiers.
   - `lseek()`: Pour déplacer le pointeur de fichier.
   - `unlink()`: Pour supprimer un fichier.

2. **Gestion des processus** :
   - `fork()`: Pour créer un nouveau processus en copiant le processus appelant.
   - `exec*()`: Pour exécuter un programme dans le contexte du processus courant.
   - `exit()`: Pour terminer un processus.
   - `getpid()`: Pour obtenir l'identifiant de processus du processus en cours d'exécution.
   - `getppid()`: Pour obtenir l'identifiant de processus du parent du processus en cours d'exécution.

3. **Entrées/Sorties** :
   - `read()`, `write()`: Pour les opérations d'E/S brutes.
   - `pipe()`, `dup()`, `dup2()`: Pour la gestion des tubes (pipes) et des descripteurs de fichiers.

4. **Gestion du temps** :
   - `sleep()`: Pour mettre un processus en sommeil pendant un certain nombre de secondes.
   - `usleep()`, `nanosleep()`: Pour des délais plus précis.

5. **Autres** :
   - `access()`: Pour vérifier l'accès à un fichier ou répertoire.
   - `chdir()`, `getcwd()`: Pour changer de répertoire courant et obtenir le répertoire courant.
   - `chown()`, `chmod()`: Pour changer les propriétés de fichiers.





## 3. PID d'un processus :


### 3.1 : `pid_t` en C :


- `pid_t` c'est  un alias de type qui est généralement défini comme un entier signé pour représenter l'identifiant de processus (PID). 

- En d'autres termes, `pid_t` est un type de données entier utilisé pour stocker des PID, qui sont des identifiants uniques attribués à chaque processus sur un système d'exploitation de type Unix.

- La définition exacte de `pid_t` peut varier en fonction du système d'exploitation, mais elle est généralement définie dans l'en-tête `<sys/types.h>`.

Voici comment est généralement défini `pid_t` :

```c
typedef int pid_t;
```

- exemple :

```c
#include <stdio.h>
#include <sys/types.h>

int main() {
    pid_t my_pid = 12345; // Exemple de PID
    pid_t another_pid = 67890;

    if (my_pid == another_pid) {
        printf("Les PID sont égaux.\n");
    } else {
        printf("Les PID sont différents.\n");
    }

    return 0;
}
```

### 3.2 les fonctions : `getpid()` et `getppid()`

Les fonctions `getpid()` et `getppid()` en langage C sont utilisées pour obtenir l'identifiant de processus (PID) du processus en cours d'exécution (généralement le processus appelant) et l'identifiant de processus du parent du processus en cours d'exécution, respectivement.

1. **`getpid()`** :

   - Signature : `pid_t getpid(void);`
   - Rôle : Cette fonction renvoie l'identifiant de processus (PID) du processus en cours d'exécution. Chaque processus a un PID unique attribué par le système d'exploitation.

   Exemple d'utilisation de `getpid()` :

   ```c
   #include <stdio.h>
   #include <unistd.h>

   int main() {
       pid_t my_pid = getpid();
       printf("Mon PID est : %d\n", my_pid);
       return 0;
   }
   ```

2. **`getppid()`** :

   - Signature : `pid_t getppid(void);`
   - Rôle : Cette fonction renvoie l'identifiant de processus (PID) du parent du processus en cours d'exécution. Cela signifie qu'elle retourne le PID du processus qui a créé le processus en cours d'exécution (généralement, le processus parent).

   Exemple d'utilisation de `getppid()` :

   ```c
   #include <stdio.h>
   #include <unistd.h>

   int main() {
       pid_t parent_pid = getppid();
       printf("Le PID de mon parent est : %d\n", parent_pid);
       return 0;
   }
   ```

