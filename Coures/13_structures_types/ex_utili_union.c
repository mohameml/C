
#include <stdio.h>

/*
Par exemple, imaginez que vous souhaitiez construire une structure pouvant accueillir plusieurs types possibles, 
par exemple des entiers et des flottants. Vous aurez besoin de trois champs : 
un indiquant quel type est stocké dans la structure et deux permettant de stocker soit un entier soit un flottant.

Toutefois, vous gaspillez ici de la mémoire puisque seul un des deux objets sera stocké. 
Une union est ici la bienvenue afin d’économiser de la mémoire.


Donc voici un exemple qui ulistre L'utilisation union : 
*/


struct nombre
{
    unsigned entier : 1;
    unsigned flottant : 1;
    union
    {
        int e;
        double f;
    } u;
};


static void affiche_nombre(struct nombre n)
{
    if (n.entier)
        printf("%d\n", n.u.e);
    else if (n.flottant)
        printf("%f\n", n.u.f);
}


int main(void)
{
    struct nombre a = { 0 };
    struct nombre b = { 0 };

    a.entier = 1;
    a.u.e = 10;
    b.flottant = 1;
    b.u.f = 10.56;

    affiche_nombre(a);
    affiche_nombre(b);
    return 0;
}