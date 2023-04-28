#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

/*
    On définit un nouveau type pour représenter l'ensemble des
    compétences d'un élève. Manipuler un skill_set_t revient à
    manipuler un entier non-signé codé sur 8 bits, mais le fait de
    définir un type ici améliore la lisibilité du code : quand on
    définit une variable de type skill_set_t, on comprend qu'on fait
    spécifiquement référence à un ensemble de compétences. */
typedef uint8_t skill_set_t;

/* Même chose pour un examen: c'est un ensemble de matières. */
typedef uint8_t exam_t;

/*
    On définit une constante pour chaque matière, dont la valeur
    correspond à sa position dans l'octet représentant un ensemble.
*/
enum course_id
{
    MATHS = 0,
    PHYSIQUE,
    CHIMIE,
    FRANCAIS,
    HISTOIRE,
    GEO,
    PHILO,
    SPORT,
    NB_MATIERES /* Astuce répandue pour récupérer facilement le
                 * nombre d'éléments d'un type énuméré. */
};

/*
    Noms des matières rangés dans le même ordre que les éléments du type
    énuméré course_id, pour affichage.
*/
static const char *course_name[NB_MATIERES] = {
    "maths",
    "physique",
    "chimie",
    "francais",
    "histoire",
    "geo",
    "philo",
    "sport"
};

/*
    Renvoie true si le bit en position pos prend la valeur 1 dans
    l'octet u, false sinon.
*/
static bool u8_bit_is_set(uint8_t pos, uint8_t u)
{
    bool ret = false;
    return ret;
}

/*
    Change la valeur du bit en position pos dans l'octet u, pour lui
    donner la valeur 1 si val vaut true et 0 sinon. La fonction
    retourne l'octet modifié.
*/
static uint8_t u8_set_bit(uint8_t pos, uint8_t u, bool val)
{
    uint8_t ret = 0;
    return ret;
}

/*
    Parcourt l'ensemble s passé en paramètre et produit un affichage de
    la forme :

        Paul est nul en maths!
        Paul est nul en physique!
        Paul est nul en chimie!
        Paul est bon en francais!
        Paul est bon en histoire!
        Paul est nul en geo!
        Paul est bon en philo!
        Paul est nul en sport!

    où Paul est nom de l'élève contenu dans le paramètre nom, ou :

        Wow, Paul maitrise tout!

    si l'élève évalué maitrise toutes les matières.
*/
static void evaluer_eleve(const char *nom, skill_set_t s)
{
}

/*
    Fait passer un examen à un étudiant dont les compétences sont
    représentées par le paramètre s.

    En pratique, exam est l'ensemble des épreuves (matières) composant
    l'examen à passer. Pour se rapprocher de la vraie vie, on tirera un
    nombre aléatoire pour modéliser la réussite ou l'échec à une
    épreuve : si ce nombre est impair, l'épreuve est réussie, sinon,
    l'épreuve est échouée.

    Cette fonction renvoie une nouvelle version des compétences de
    l'élève, mise à jour en fonction de la réussite ou de l'échec des
    épreuves de l'examen passé en paramètre.
 */
static skill_set_t passer_examen(exam_t exam, skill_set_t s)
{
    skill_set_t ret = 0;
    return ret;
}


int main(void)
{
    /*
        Initialisation du générateur de nombres aléatoires nécessaire
        pour implémenter passer_examen (voir man 3 rand).
    */
    srand(time(NULL));

    skill_set_t s = 0;

    /*
        Hypothèses douteuses : les littéraires sont nuls en maths, en
        physique, en chimie et en sport...
    */
    s = u8_set_bit(FRANCAIS, s, true)
        | u8_set_bit(HISTOIRE, s, true)
        | u8_set_bit(GEO, s, true)
        | u8_set_bit(PHILO, s, true);
    evaluer_eleve("litteraire", s);
    evaluer_eleve("scientifique", ~s);

    /* un élève bon en sport et en chimie... */
    s = 132;
    evaluer_eleve("mystère", s);

    s = 0;
    evaluer_eleve("toto", s);

    /* Deuxième chance pour toto, il passe les examens littéraires. */
    exam_t e = 0;
    e = u8_set_bit(FRANCAIS, e, true)
        | u8_set_bit(HISTOIRE, e, true)
        | u8_set_bit(GEO, e, true)
        | u8_set_bit(PHILO, e, true);

    printf("toto repasse ses exams...\n");
    s = passer_examen(e, s);
    evaluer_eleve("toto", s);

    return EXIT_SUCCESS;
}
