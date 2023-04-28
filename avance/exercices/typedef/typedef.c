#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

/*
   En C, définir un type revient à renommer un type existant. Il n'y a
   donc rien de fondamentalement compliqué, vous pouvez voir ce
   mécanisme comme un moyen d'attribuer des noms explicites à des
   types de données que votre programme manipule souvent.

   Voici les cas où on s'autorise à utiliser typedef :

   1- pour redéfinir un type de base (pour lui donner un nom
   explicite, indiquer que ce type de base représente en fait une
   donnée particulière de notre programme) ;

   2- pour redéfinir un type de base ;

   3- pour rédéfinir un type de base ;

   4- goto 1-.

   Dans TOUS les autres cas, utiliser typedef n'est JAMAIS une bonne
   idée.

   Voici quelques illustrations d'utilisation de typedef, à bon ou
   mauvais escient :
*/

/*
  [BIEN] On définit le type grey_scale_t, qui représente un niveau de
  gris sur un pixel. La valeur 0 représente le noir, la valeur 255 le
  blanc, tout valeur intermédiaire représente du gris (plus ou moins
  clair). Ici, l'utilisation de typedef est appropriée : on donne une
  information supplémentaire à la personne qui lit le code. Quand on
  déclare une variable de type grey_scale_t, elle sait qu'on y
  stockera un niveau de gris. Notez que rien ne change du point de vue
  de la compilation ou de l'exécution, on continue de manipuler des
  entiers non-signés codés sur 1 octet.
 */
typedef uint8_t grey_scale_t;

/*
  [PAS BIEN] On définit le type point_t, qui représente une
  structure. C'est mal. Des gens vous diront que c'est bien, d'autres
  que ce n'est pas si grave, que c'est toléré (même des profs de C,
  des fois!). Le verdict officiel est : c'est mal. Le mot-clé struct
  donne une information importante sur les variables de type struct
  point : elles contiennent d'autres variables! (les champs de la
  structure). On perd donc de l'information avec ce renommage. En
  plus, l'argument "je donne un nom de type explicite" ne tient plus
  la route, puisque vous pouvez très bien le faire en donnant à votre
  structure un nom explicite! Reste l'argument de la concision du
  code, qui ne doit jamais prévaloir sur sa lisibilité ou sa clarté.
 */
struct point
{
     uint8_t pos_x;
     uint8_t pos_y;
};

typedef struct point point_t;

/*
  [PASSIBLE D'EMPRISONNEMENT] C'est vraiment la pire utilisation du
  typedef (de loin). Ici, on renomme le type double ** en
  matrice_t. Par ce renommage, on cache à l'utilisateur qu'un objet de
  type matrice_t est en fait un pointeur de pointeur, avec tout ce que
  ça implique sur son initialisation, son allocation mémoire, son
  utilisation (opérateur *, etc.).

  Il existe bien des exceptions à cette règle qui impliquent un style
  de programmation bien particulier que l'on abordera pas ici (si on
  interdit à l'utilisateur de manipuler directement les variables de
  type matrice_t, c'est-à-dire qu'on ne peut les manipuler que via des
  appels de fonctions).

  Retenez donc que cette pratique est proscrite, et que tout
  contrevenant sera enfermé dans le cachot sous l'amphi D avec pour
  seule lecture le poly de C et le coding style Linux, jusqu'à ce
  qu'il admette ses fautes.
*/
typedef double ** matrice_t;
