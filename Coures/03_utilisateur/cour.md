# cour 03 : 



## la fonction `fgets` :

- **Description :**

    - La fonction `fgets` en C est utilisée pour lire une chaîne de caractères à partir d'un flux (généralement un fichier ou l'entrée standard) et stocker cette chaîne dans un tableau de caractères (une chaîne de caractères). 

    - La fonction `fgets` permet de spécifier le nombre maximum de caractères à lire, ce qui est utile pour éviter un débordement de mémoire. 


- **le prototype de la fonction `fgets` :**

```c
char *fgets(char *str, int size, FILE *stream);
```

- `str` est un pointeur vers un tableau de caractères (chaîne de caractères) où les caractères lus seront stockés.

- `size` est le nombre maximal de caractères à lire, y compris le caractère de fin de ligne (`'\n'`). Il s'agit généralement de la taille du tableau `str`.

- `stream` est un pointeur vers le flux depuis lequel les caractères doivent être lus : 
    
    - Il peut s'agir d'un pointeur vers un fichier (obtenu avec `fopen`) .
    
    - ou d'un pointeur prédéfini, par exemple, `stdin` pour l'entrée standard (clavier).


- **fonctionnement :**

- La fonction `fgets` lira des caractères depuis le flux jusqu'à :
    
    - ce qu'elle atteigne le nombre maximal de caractères spécifié (`size - 1`) 
    
    - ou jusqu'à ce qu'elle atteigne un caractère de fin de ligne (`'\n'`), 
    
    - ou jusqu'à la fin du fichier. 

- Elle stockera les caractères lus dans le tableau `str`, ajoutera un caractère nul (`'\0'`) à la fin de la chaîne pour la terminer correctement, et renverra un pointeur vers `str`. 

- vSi la fin du fichier est atteinte avant de lire des caractères, ou si aucune donnée n'est lue en raison d'une erreur, `fgets` renverra un pointeur nul (`NULL`).


- **un exemple simple d'utilisation de `fgets` pour lire une ligne depuis l'entrée standard (clavier) :**

```c
#include <stdio.h>

int main() {
    char buffer[100];  // Tableau pour stocker la ligne lue

    printf("Entrez une ligne de texte : ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("Vous avez entré : %s", buffer);
    } else {
        printf("Erreur de lecture de l'entrée.\n");
    }

    return 0;
}
```

Dans cet exemple, `fgets` est utilisé pour lire une ligne de texte depuis l'entrée standard (`stdin`) et stocker la ligne lue dans le tableau `buffer`. La taille maximale de la ligne à lire est limitée à 99 caractères, et le dernier caractère du tableau est réservé pour le caractère nul de fin de chaîne. Une fois la ligne lue, elle est affichée à l'écran.