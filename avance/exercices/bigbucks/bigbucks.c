#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "salarie.h"

void afficher_salarie(void *sal) {
    /*
	Version qui n'utilise pas votre définition de struct salarie,
	mais s'appuie sur le cahier des charges, en allant lire directement
	en mémoire depuis l'adresse de base de l'objet "sal" passé en paramètre.
    */

    /*
	En première position dans la structure, on doit retrouver
	une chaine de caractères de longueur 16.
    */
    const char *prenom = sal;

    /*
	Le nom vient en 2e position dans la structure, il doit donc
	se trouver 16 octets après l'adresse de base.
    */
    const char *nom = sal + 16;

    /*
	Ensuite vient l'age, qui se trouve après le prénom (16 octets)
	et le nom (32 octets). L'age est codé sur 1 octet.
    */
    uint8_t age = *(uint8_t *)(sal + 16 + 32);

    /*
	Ensuite vient l'ancienneté, qui se trouve après le prénom (16 octets),
	le nom (32 octets) et l'age (1 octet). L'ancienneté est codée sur 1 octet.
    */
    uint8_t anciennete = *(uint8_t *)(sal + 16 + 32 + 1);

    /*
	Enfin vient le salaire, qui se trouve après le prénom (16 octets),
	le nom (32 octets), l'age (1 octet) et l'ancienneté (1 octet).

	Attention, chaud cacao : on avance de deux octets supplémentaires,
	parce qu'un mot de 4 octets commence toujours à une adresse
	multiple de 4 octets. Voir le commentaire de la fonction allouer_salarie()
	dans la correction pour plus de détails.

	Le salaire est codé sur 4 octets.
    */
    uint32_t salaire = *(uint32_t *)(sal + 16 + 32 + 1 + 1 + 2);

    printf("%s %s a %u ans.\n", prenom, nom, age);
    printf("Il est dans l'entreprise depuis %u années et gagne %u euros par mois.\n",
	   anciennete, salaire);
}

int main(void)
{
    struct salarie *s1, *s2;

    /*
	On créé le premier salarié. Il est dans l'entreprise depuis
	longtemps, son salaire est mirobolant!

	Ici on sépare l'allocation de l'initialisation de la structure.
    */
    s1 = allouer_salarie();
    init_salarie(s1, "Donald", "Trump", 70, 70, -1);
    afficher_salarie(s1);

    /*
	Un deuxième salarié, plus modeste.

	Ici, on utilise creer_salarie() qui effectue l'allocation
	ET l'initialisation du salarié.
    */
    creer_salarie(&s2, "John", "Doe", 34, 10, 2500);
    afficher_salarie(s2);

    /* On met la clé sous la porte, tout le monde passe à la trappe! */
    plan_social(&s1);
    plan_social(&s2);

    return EXIT_SUCCESS;
}
