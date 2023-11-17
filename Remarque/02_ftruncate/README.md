# **La fonction `ftruncate` :**


La fonction `ftruncate` en C est utilisée pour redimensionner un fichier à une taille spécifiée. Elle prend en entrée un descripteur de fichier et une nouvelle taille. Voici sa déclaration :

```c
#include <unistd.h>

int ftruncate(int fd, off_t length);
```

- `fd` : Le descripteur de fichier du fichier que vous souhaitez redimensionner.
- `length` : La nouvelle taille du fichier.

La fonction renvoie 0 en cas de succès et -1 en cas d'échec.

Exemple d'utilisation de `ftruncate` pour redimensionner un fichier :

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "exemple.txt";
    
    // Ouvre le fichier en écriture seulement
    int fd = open(filename, O_WRONLY);

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Redimensionne le fichier à une nouvelle taille
    if (ftruncate(fd, 1000) == -1) {
        perror("Erreur lors du redimensionnement du fichier");
        close(fd);
        return 1;
    }

    // Ferme le descripteur de fichier
    close(fd);

    return 0;
}
```

Dans cet exemple, le fichier "exemple.txt" est ouvert en écriture seulement avec `O_WRONLY`, puis la fonction `ftruncate` est utilisée pour redimensionner le fichier à une nouvelle taille de 1000 octets. Assurez-vous que le fichier existe avant d'essayer de le redimensionner.