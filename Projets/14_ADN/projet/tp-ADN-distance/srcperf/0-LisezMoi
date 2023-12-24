Description: code pour lire les compteurs d'energie Intel RAPL sur le processeur (cf 
doc : https://recherche.noiraudes.net/ecoinfo/numres/ressources/TP/04-mesure-conso.html )

Les fichiers perfMesure.h et perfMesure.c contiennent la spécification et le code de deux fonctions C:
- void perfstart(struct myperf*  p) ; 
- void perfstop_and_display( FILE* out, struct myperf* p) ;
qui permettent d'afficher (dans le fichier out) des statistiques sur les ressources consommées:
- temps écoulé (utilisation de la fonction C gettimeofday).
- temps CPU, nombre de défats de pages  (utilisation de la fonction C getrusage).
- énergie CPU consommée pendant le temps écoulé par lecture des compteurs Intel RAPL: pour le coeur KK, la valeur courante
  est stockée dans le fichier  /sys/class/powercap/intel-rapl/intel-rapl:KK/energy_uj

########################
UTILISATION:
La déclaration : " struct myperf p ; "  permet à l'utilisateur d'accéder via la 
variable p aux valeurs des compteurs et aussi au cumul des ressources consommées depuis le 
dernier appel à perf_start(&p) et jusqu'au dernier appel à perfstop_and_display(stderr, &p). 

/**
 * \struct myperf
 * \brief stockage des valeurs des compteurs de performance. Les valeurs des cumuls sont la différence des compteurs entre le dernier appel à perfstart et le dernier appel à perfstop_and_display.
*/
struct myperf
{
  struct timeval current_timeofday ; /*!< compteurs de gettimeofday */
  struct rusage  current_rusage; /*!< compteurs de getrusage */
  unsigned long  current_rapl_energy_uj[ NBMAXCORE ]; /*!< compteurs Intel RAPL energy_uj */
  double cumul_elapsed_time ;  /*!< cumul du elapsed time en seconde*/
  double cumul_cpuusertime ;  /*!< cumul du temps cpu en seconde*/
  double cumul_systime ; /*!< cumul du temps systeme en seconde*/
  double cumul_energy ; /*!< cumul de l'energie consommée par le coeur en kWh  */
  double cumul_pagequeries ; /*!< cumul du nombre de requetes de pages */
  double cumul_pagefaults ; /*!< cumul du nombre de fautes de pages  */
  double cumul_read_blk ; /*!< cumul du nombre de blocs lus  */
  double cumul_write_blk ; /*!< cumul du nombre de blocs ecrits */

} ;

Le code des 2 fonctions est fourni et vous pouvez l'adapter librement à vos besoins
(par exemple pour faire pour chaque mesure 5 exécutions et afficher l'intervalle de confiance)

########################
EXEMPLE simple d'utilisation (cf par exemple les lignes 57-60 et 186-194 du fichier : 
/matieres/4MMAOD6/2022-10-TP-AOD-ADN-Docs-fournis/tp-ADN-distance/src/distanceEdition.c

   #include "/matieres/4MMAOD6/2022-10-TP-AOD-ADN-Docs-fournis/tp-ADN-distance/srcperf/perfMesure.c"
      // NB si plsuieurs programmes, inclure perfMesure.h au lieu de perfMesure.c qui devrait alors être compilé séparément):

   ...
   { struct myperf p;
     perfstart(&p) ;
     res = EditDistance_NW_Rec(seq[0], length[0], seq[1], length[1]); // Calcul qu'on veut mesurer
     perfstop_and_display( stderr, &p ) ;

     // Pour ajouter les performances dans un fichier latex en rw 
     fprintf(fichlatex, " %ld & %ld & %g & %g & %g \\\\\n ", length[0], length[1], 
        p.cumul_elapsed_time, p.cumul_cpuusertime, p.cumul_energy ) ;
     ...
   }

REMARQUE: lorsqu'elle est disponible (ce n'est pas le cas sur les pc ensimag en octobre 2022),
la commande "perf stat"  donne, avec les bonnes options, des mesures sur la consommation d'energie 
Exemple: 
perf stat -e power/energy-cores/ -e power/energy-gpu/ -e power/energy-pkg/ -e power/energy-psys/ -e power/energy-ram/ make
         5 005,68 Joules power/energy-cores/                                         
             34,22 Joules power/energy-gpu/                                           
          5 591,86 Joules power/energy-pkg/                                           
          9 401,78 Joules power/energy-psys/                                          
            711,85 Joules power/energy-ram/         
287,542923380 seconds time elapsed

