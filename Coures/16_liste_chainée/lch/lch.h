#ifndef __LCH__
#define __LCH__

// On definit la structure de liste chainée : lch
typedef struct bloc
{
    /* data */
    int val;
    struct bloc *suiv;

} liste;

//  afficher le contenu d'une liste chainée :
void AfficheListe(liste *tete);
void AfficherlisteRec(liste *tete);
void AfficherListeRecInverse(liste *tete);

// Modifier le contenu d'une liste chainée :
liste *ModifierTete(liste *tete, int val);
liste *InsererMilieu(liste *tete, int valeur);
liste *InsererFin(liste *tete, int val);
liste *InsererFinRec(liste *tete, int valeur);
liste *SupprimerElt(liste *tete, int valeur);

// Concaténation de deux listes chainées  :
liste *Concat2Listes(liste *tete1, liste *tete2);
liste *Concat2listesSansRep(liste *tete1, liste *tete2);

// Comparaison de deux listes chainées :
void compare(liste *tete1, liste *tete2);

// Fusion de deux listes chainées :
liste *fusionner(liste *tete1, liste *tete2);
liste *fusionnerRec(liste *tete1, liste *tete2);
liste *fusionnerSansRep(liste *tete1, liste *tete2);
liste *fusionnerSansRepRec(liste *tete1, liste *tete2);

// fonctions connexes  :
bool existe(liste *tete, int val);
int somme(liste *tete);
int longueur(liste *tete);
int nb_elem_diff(liste *tete);

#endif