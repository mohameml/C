/*
    Enoncé :

    Cet exercice va vous donner l'occasion d'analyser la prose de poêtes français
    parmi les plus talentueux de notre ère (ici, Annie Cordy et Carlos Dolto).

    On vous demande d'écrire un programme qui prend un fichier texte en argument
    de la ligne de commandes, l'analyse et affiche en sortie le nombre de fois
    qu'apparaissent chacune des lettres de l'alphabet dans ladite oeuvre.

    Par exemple, ./statphabet tatayoyo.txt doit afficher un rapport de la forme :

    a: 110
    b: 12
    c: 13
    d: 43
    e: 89
    f: 10
    g: 26
    h: 7
    i: 56
    j: 10
    k: 0
    l: 32
    m: 57
    n: 64
    o: 70
    p: 13
    q: 16
    r: 23
    s: 61
    t: 61
    u: 55
    v: 3
    w: 0
    x: 7
    y: 27
    z: 0
    caracteres speciaux: 326

    Vous noterez que tata yoyo ne contient aucune occurrence du caractère 'k', au
    contraire du titre "cho ka ka o" qui fait monter ce compteur en flèche grâce
    au fameux "ki ki ki le petit kiwi".

    Votre analyse ne doit pas être sensible à la case : on comptera indifféremment
    'a' et 'A' comme étant une occurrence de a.

    On considère que tout caractère non alphabétique (a-z ou A-Z) comme étant un
    caractère spécial.

    Vous pourrez tester votre implémentation sur les fichiers tatayoyo.txt et
    papayou.txt fournis, ou tout autre composition de votre choix, y compris le
    répertoire de Nana Mouskouri.

    Compétences : 26,18,31,42,48,49,50
    Difficulté : 3
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    /*
        Affiche un message d'erreur si l'utilisateur oublie l'argument
        à passer en ligne de commandes.
    */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s fichier.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* On récupère le nom du fichier à ouvrir sur la ligne de commandes. */
    const char *texte = argv[1];

    /*
        On va compter les caractères dits "spéciaux", c'est-à-dire
        tous ceux qui ne sont pas alpha (autres que a-z ou A-Z).
    */
    uint64_t caracteres_speciaux = 0;

    /* Ce tableau compte le nombre d'occurrences de lettres dans le fichier. */
    uint64_t alphabet[26] = { 0 };


    return EXIT_SUCCESS;
}
