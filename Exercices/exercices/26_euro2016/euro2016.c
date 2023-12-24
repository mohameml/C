#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

struct equipe;


/**
 * @brief Simule un match entre deux équipes passées en paramètre.
 *
 * Cette fonction simule un match entre deux équipes, en simulant
 * le nombre de buts marqués par chacun d'elle et en mettant à jour
 * les informations contenues dans chacune des struct equipe
 * associées à e1 et e2.
 *
 * @param e1 la première équipe
 * @param e2 la seconde équipe
 */
static void jouer_match(struct equipe* e1, struct equipe* e2)
{
}

/**
 * @brief Affiche les statistiques de l'équipe passée en paramètre.
 *
 * @param e l'équipe dont on souhaite afficher les statistiques
 */
static void afficher_equipe(struct equipe* e)
{
}

int main(void)
{
    /* Initialisation du générateur de nombres aléatoires, utilisé
     * dans jouer_match(). */
    srand(time(NULL));


    return EXIT_SUCCESS;
}
