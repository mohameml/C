# cour 17 : Allocateur Et Ramaseee-miette 

**L'objectif de ce cour est de definir un allocateur persenolle et un ramasse_miette gc(Garbage Collector ) pour un pool d’objets identiques**


## 1. Pool d'objets :


-  Un "pool d'objets identiques" est une structure de données utilisée en programmation pour gérer un ensemble d'objets qui sont tous du même type et ont la même structure. 

- L'objectif principal d'un pool d'objets identiques est d'améliorer l'efficacité de l'allocation et de la désallocation de ces objets, en évitant les frais généraux associés à l'allocation dynamique de mémoire à chaque utilisation.

Voici quelques caractéristiques importantes d'un pool d'objets identiques :

1. **Objets du même type** : Tous les objets stockés dans le pool sont du même type, c'est-à-dire qu'ils ont la même structure de données et le même comportement. Par exemple, si vous avez une structure de données représentant des éléments d'une liste chaînée, tous les éléments du pool auront la même structure.

2. **Allocation préalable** : Les objets du pool sont alloués en mémoire au début du programme ou à un moment donné avant leur utilisation. Contrairement à l'allocation dynamique, où la mémoire est allouée au fur et à mesure des besoins, le pool alloue la mémoire en une seule opération. Cela réduit les coûts d'allocation de mémoire pendant l'exécution.

3. **Réutilisation** : Au lieu de créer de nouveaux objets à chaque fois qu'ils sont nécessaires, les objets du pool sont réutilisés. Lorsqu'un objet n'est plus nécessaire, il est renvoyé dans le pool pour être utilisé à nouveau.

4. **Gestion efficace de la mémoire** : En préallouant une quantité fixe de mémoire pour les objets du pool, celui-ci évite les problèmes de fragmentation de la mémoire et permet une gestion efficace de la mémoire.

5. **Amélioration des performances** : En réduisant la création et la destruction fréquentes d'objets, les pools d'objets identiques peuvent améliorer les performances de l'application, notamment dans les situations où l'allocation dynamique de mémoire est coûteuse.

## 2. code source de l' Allocateur Et Ramaseee-miette :

```c
#include <stdbool.h>
#include <stdio.h>

#define MEM_POOL_SIZE 1000

// Définition de la structure "elem" avec deux champs : val et next
struct elem {
    int val;
    struct elem *next;
};

// Mémoire préallouée pour stocker les structures "elem"
static unsigned char memoire_elem_pool[sizeof(struct elem) * MEM_POOL_SIZE];

// Tableau de booléens pour suivre l'utilisation des éléments dans le pool
static bool elements_utilises[MEM_POOL_SIZE];

// Initialisation des éléments
void init_elems() {
    for (int i = 0; i < MEM_POOL_SIZE; i++) {
        elements_utilises[i] = false;
    }
}

// Fonction d'allocation d'un élément "elem"
struct elem *alloc_elem() {
    for (int i = 0; i < MEM_POOL_SIZE; i++) {
        if (!elements_utilises[i]) {
            elements_utilises[i] = true;
            return (struct elem *)(memoire_elem_pool + i * sizeof(struct elem));
        }
    }
    return NULL; // Aucun élément disponible
}

// Fonction de collecte des éléments non utilisés
void gc_elems(struct elem **heads, int nbheads) {
    for (int i = 0; i < MEM_POOL_SIZE; i++) {
        elements_utilises[i] = false;
    }

    for (int h = 0; h < nbheads; h++) {
        struct elem *current = heads[h];
        while (current != NULL) {
            int indice = ((unsigned char *)current - memoire_elem_pool) / sizeof(struct elem);
            if (indice >= 0 && indice < MEM_POOL_SIZE) {
                elements_utilises[indice] = true;
            }
            current = current->next;
        }
    }
}

// Fonction pour afficher une liste chaînée de structures "elem"
void affichage_liste(struct elem *liste) {
    if (liste == NULL) {
        printf("Votre liste est vide\n");
    } else {
        struct elem const *ptr = liste;
        while (ptr->next != NULL) {
            printf("%d -> ", ptr->val);
            ptr = ptr->next;
        }
        printf("%d\n", ptr->val);
    }
}

int main(void) {
    // Allocation de deux éléments et création d'une liste chaînée
    struct elem *e1 = alloc_elem();
    e1->val = 1;
    e1->next = alloc_elem();
    e1->next->val = 2;
    e1->next->next = NULL;

    // Affichage de la liste chaînée
    affichage_liste(e1);

    return 0;
}

```

- Ce code en langage C montre la mise en œuvre d'un allocateur de mémoire personnalisé pour une structure de données `struct elem`,  

- Le code utilise un "pool" de mémoire préalloué pour stocker les structures `struct elem`. 


- Explication détaillée du code :

1. Nous définissons une structure `struct elem` qui représente les éléments de notre liste chaînée. Chaque élément a un champ `val` pour stocker une valeur entière et un champ `next` qui pointe vers l'élément suivant dans la liste.

2. Nous utilisons un tableau de `unsigned char` appelé `memoire_elem_pool` pour préallouer un bloc de mémoire qui sera utilisé pour stocker les éléments. La taille de ce bloc est calculée en fonction de la taille de la structure `struct elem` et de la constante `MEM_POOL_SIZE`.

3. Un tableau de booléens `elements_utilises` est utilisé pour suivre l'état d'utilisation de chaque élément dans le pool.

4. La fonction `init_elems` initialise le tableau `elements_utilises` en marquant tous les éléments comme non utilisés (false).

5. La fonction `alloc_elem` alloue un nouvel élément en recherchant le premier élément non utilisé dans le pool, le marquant comme utilisé (true), puis renvoyant un pointeur vers cet élément. Si aucun élément n'est disponible, elle renvoie NULL.

6. La fonction `gc_elems` est utilisée pour marquer les éléments comme utilisés en fonction des têtes de liste passées en argument.



Ce code illustre la gestion d'une liste chaînée dans un pool de mémoire préalloué, ce qui permet d'éviter l'allocation dynamique de mémoire pour chaque élément de la liste.*

## 3. la fonction `alloc_elem` :

La fonction `alloc_elem` est une fonction qui alloue dynamiquement un élément de type `struct elem` à partir d'un pool de mémoire préalloué. Cette fonction permet de récupérer un élément libre du pool, de le marquer comme utilisé, puis de renvoyer un pointeur vers cet élément nouvellement alloué. Voici une explication détaillée de cette fonction :

```c
struct elem *alloc_elem() {
    for (int i = 0; i < MEM_POOL_SIZE; i++) {
        if (!elements_utilises[i]) {
            elements_utilises[i] = true; // Marque l'élément comme utilisé
            return (struct elem *)(memoire_elem_pool + i * sizeof(struct elem));
        }
    }
    return NULL; // Aucun élément disponible
}
```

Explication de la fonction `alloc_elem` :

1. La fonction a un type de retour `struct elem *`, ce qui signifie qu'elle renvoie un pointeur vers une structure `struct elem`.

2. La fonction commence par une boucle `for` qui parcourt le tableau `elements_utilises` pour trouver un élément libre dans le pool de mémoire.

3. À chaque itération de la boucle, la fonction vérifie si `elements_utilises[i]` est `false`. Si c'est le cas, cela signifie que l'élément à l'indice `i` n'est pas utilisé.

4. Lorsqu'un élément non utilisé est trouvé, la fonction effectue les étapes suivantes :
   - Elle marque l'élément comme utilisé en affectant `true` à `elements_utilises[i]`. Cela indique que cet élément est maintenant utilisé et ne peut pas être alloué à nouveau tant qu'il n'est pas libéré.
   - Elle calcule l'adresse mémoire de l'élément dans le pool en utilisant `memoire_elem_pool + i * sizeof(struct elem)`. Cela permet d'obtenir un pointeur vers la mémoire où l'élément `struct elem` sera stocké.

5. La fonction renvoie ensuite ce pointeur comme résultat, ce qui signifie qu'elle retourne un pointeur vers l'élément `struct elem` nouvellement alloué et marqué comme utilisé.

6. Si la boucle se termine sans trouver d'élément libre (c'est-à-dire que tous les éléments du pool sont déjà utilisés), la fonction renvoie `NULL` pour indiquer qu'aucun élément n'est disponible.

En résumé, la fonction `alloc_elem` permet d'allouer et de retourner un élément `struct elem` du pool de mémoire préalloué, en veillant à ce que l'élément soit marqué comme utilisé pour qu'il ne soit pas alloué à nouveau tant qu'il n'est pas libéré. Cela permet d'éviter l'allocation dynamique coûteuse à chaque fois qu'un nouvel élément est nécessaire.

## 4. la fonction `gc_elems`:

La fonction `gc_elems` (pour Garbage Collector des éléments) est une fonction qui a pour but de marquer les éléments d'un pool comme utilisés ou non utilisés en fonction des têtes de liste passées en argument. Elle parcourt les listes chaînées de têtes de liste et met à jour le tableau `elements_utilises` en conséquence. Voici une explication détaillée de cette fonction :

```c
void gc_elems(struct elem **heads, int nbheads) {
    for (int i = 0; i < MEM_POOL_SIZE; i++) {
        elements_utilises[i] = false; // Réinitialise tous les éléments comme non utilisés
    }

    for (int h = 0; h < nbheads; h++) {
        struct elem *current = heads[h]; // Pointeur pour parcourir la liste courante

        while (current != NULL) {
            int indice = ((unsigned char *)current - memoire_elem_pool) / sizeof(struct elem);
            // Calcule l'indice de l'élément dans le pool

            if (indice >= 0 && indice < MEM_POOL_SIZE) {
                elements_utilises[indice] = true; // Marque l'élément comme utilisé
            }

            current = current->next; // Passe à l'élément suivant dans la liste
        }
    }
}
```

Explication de la fonction `gc_elems` :

1. La fonction commence par une boucle `for` pour réinitialiser tous les éléments du pool comme non utilisés en affectant `false` à chaque élément du tableau `elements_utilises`. Cette étape permet de remettre à zéro l'état d'utilisation des éléments avant de le recalculer en fonction des têtes de liste.

2. Ensuite, la fonction utilise une autre boucle `for` pour parcourir toutes les têtes de liste passées en argument. Chaque tête de liste est représentée par un pointeur vers la première structure `struct elem` de cette liste.

3. À l'intérieur de la boucle externe, un pointeur `current` est utilisé pour parcourir la liste courante. La boucle interne `while (current != NULL)` parcourt la liste chaînée à partir de la tête de liste.

4. Pour chaque élément `current` de la liste, la fonction calcule l'indice de cet élément dans le pool de mémoire. Cela se fait en soustrayant l'adresse de `current` de l'adresse de `memoire_elem_pool` et en divisant le résultat par la taille de `struct elem`. Cela donne l'indice de l'élément dans le pool.

5. Si l'indice calculé est valide (c'est-à-dire qu'il est compris entre 0 et `MEM_POOL_SIZE - 1`), la fonction marque l'élément correspondant comme utilisé en affectant `true` à `elements_utilises[indice]`.

6. Enfin, la boucle interne se déplace vers l'élément suivant dans la liste en mettant à jour `current` avec `current->next`.

7. La fonction répète ce processus pour toutes les têtes de liste, ce qui permet de marquer les éléments utilisés dans le pool en fonction de ces listes.

En résumé, la fonction `gc_elems` met à jour l'état d'utilisation des éléments du pool en fonction des têtes de liste passées en argument. Elle marque les éléments comme utilisés s'ils sont présents dans au moins l'une des listes chaînées. Cette fonction est utile pour suivre quels éléments du pool sont actuellement référencés et utilisés par votre programme.