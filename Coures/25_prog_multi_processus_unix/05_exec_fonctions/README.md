# cour 05 : La famille de fonctions `exec`

- La famille de fonctions `exec` en langage C est utilisée pour remplacer l'image du processus actuel par une nouvelle image de programme. 

- Ces fonctions sont couramment utilisées pour exécuter un nouveau programme ou une nouvelle commande à l'intérieur d'un processus existant. 

- Les principales fonctions de la famille `exec` incluent :

1. `execl` : Cette fonction est utilisée pour exécuter un programme spécifié en passant les arguments en tant que liste d'arguments individuels. La liste se termine par un pointeur NULL. Voici un exemple d'utilisation :
   
   ```c
   execl("/bin/ls", "ls", "-l", NULL);
   ```

2. `execv` : Cette fonction est similaire à `execl`, mais au lieu de spécifier les arguments en tant qu'arguments distincts, vous passez un tableau d'arguments terminé par un pointeur NULL. Voici un exemple :
   
   ```c
   char *args[] = {"/bin/ls", "-l", NULL};
   execv("/bin/ls", args);
   ```

3. `execle` : Similaire à `execl`, cette fonction permet de spécifier un environnement personnalisé pour le programme en plus des arguments.
   
   ```c
   char *envp[] = {"VAR=value", NULL};
   execle("/path/to/program", "program", "arg1", "arg2", NULL, envp);
   ```

4. `execve` : Similaire à `execv`, cette fonction permet de spécifier un environnement personnalisé pour le programme.
   
   ```c
   char *args[] = {"/path/to/program", "arg1", "arg2", NULL};
   char *envp[] = {"VAR=value", NULL};
   execve("/path/to/program", args, envp);
   ```

5. `execp` : Cette fonction recherche le programme spécifié dans les répertoires répertoriés dans la variable d'environnement `PATH`.

   ```c
   execp("ls", "ls", "-l", NULL);
   ```

6. `execvp` : Cette fonction est similaire à `execp`, mais vous pouvez également spécifier des arguments.

   ```c
   char *args[] = {"ls", "-l", NULL};
   execvp("ls", args);
   ```

7. `execvpe` : Similaire à `execvp`, cette fonction vous permet de spécifier un environnement personnalisé pour le programme.

   ```c
   char *args[] = {"ls", "-l", NULL};
   char *envp[] = {"VAR=value", NULL};
   execvpe("ls", args, envp);
   ```

8. `execlp` :

    - La fonction `execlp` est une fonction de la famille `exec` en langage C utilisée pour exécuter un programme en spécifiant son nom sans préciser le chemin d'accès complet. Cette fonction recherche le programme dans les répertoires répertoriés dans la variable d'environnement `PATH`. Si le programme est trouvé dans l'un de ces répertoires, il est exécuté. La signature de la fonction `execlp` est la suivante :

    ```c
    #include <unistd.h>

    int execlp(const char *file, const char *arg0, ... /*, (char *)0 */);
    ```

    - `file` est le nom du programme à exécuter, sans le chemin d'accès complet.

    - `arg0` est le nom du programme (premier argument), qui est généralement le même que `file`.

    - Les arguments suivants, s'ils sont spécifiés, sont les arguments du programme à exécuter.

    - La liste d'arguments se termine généralement par un pointeur NULL.

    Voici un exemple d'utilisation de `execlp` pour exécuter la commande "ls" sans préciser le chemin complet :

    ```c
    #include <unistd.h>

    int main() {
        execlp("ls", "ls", "-l", NULL);

        // Si l'appel à execlp réussit, cette partie du code ne sera pas atteinte.
        return 0;
    }
    ```

    Dans cet exemple, `execlp("ls", "ls", "-l", NULL)` exécute la commande "ls" en recherchant le programme "ls" dans les répertoires répertoriés dans la variable d'environnement `PATH`. Il est équivalent à exécuter "ls -l" dans un terminal.





### RQ : **un environnement personnalisé :**

- Un environnement personnalisé dans le contexte des fonctions `exec` en langage C fait référence à l'ensemble des variables d'environnement spécifiques à un processus. 

- Les variables d'environnement sont des valeurs clés-valeurs qui sont accessibles par un processus et qui définissent divers aspects de son comportement.

- Lorsque vous exécutez un programme, il a accès à un ensemble de variables d'environnement qui sont héritées du processus parent. 

- Ces variables d'environnement peuvent contenir des informations telles que les répertoires de recherche pour les exécutables, les variables de configuration, les chemins de bibliothèques, les informations de localisation, etc.

- Lorsque vous utilisez les fonctions `exec` telles que `execle`, vous avez la possibilité de spécifier un nouvel environnement personnalisé pour le programme que vous allez exécuter. Cela signifie que vous pouvez définir vos propres variables d'environnement et leurs valeurs avant de lancer le nouveau programme. Cela peut être utile pour personnaliser l'environnement du programme en cours d'exécution.

- Un exemple courant d'utilisation d'un environnement personnalisé est la modification de la variable d'environnement `PATH` pour contrôler les répertoires de recherche pour les exécutables. Vous pouvez également définir d'autres variables d'environnement spécifiques à votre application si nécessaire.

