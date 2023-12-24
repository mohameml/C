/**
 * \file perfMesure.h
 * \brief Utilise getursage, getimeofday et les compteurs Intel RAPL pour afficher des performances dont l'energie consommée et la puissance moyenne 
 * /sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj 
 * \version 0.1
 * \date 20/10/2022 
 * \author Jean-Louis Roch (Ensimag, Grenoble-INP - University Grenoble-Alpes) jean-louis.roch@grenoble-inp.fr
*/ 

#ifndef __PERFMESURE_H__
#define __PERFMESURE_H__

/** 
 * \def NBMAXCORE
 * \brief Nombre maximum de coeurs ou compteurs rapl_energy_uj
 */ 
#define NBMAXCORE  8 

#include <sys/time.h> // for struct timeval 
#include <sys/resource.h> // for struct rusage
#include <stdio.h> // for FILE type

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


/**
 * \fn void perfstart(struct myperf*  p) 
 * \brief stores the value of performance counters in prallocated struct *p 
 * \param p struct where the current values of counters are copied 
 */
void perfstart(struct myperf*  p) ; 

/**
 * \fn void perfstop_and_display( FILE* out, struct myperf* p) 
 * \brief prints on out the difference between current performance counter values and previous ones stored in *p; *p is updated with current values. 
 * \param out ouput stream; the printing is displayed in text format (using fprintf) 
 * \param p struct where the old values of counters are copied; those values are updated with the current ones 
 */
void perfstop_and_display( FILE* out, struct myperf* p) ;


#endif //  __PERFMESURE_H__

