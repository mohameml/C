/**
 * \file perfMesure.c
 * \brief Implemente perfMesure.h. Utilise getursage, getimeofday et les compteurs Intel RAPL pour afficher des performances dont l'energie consommée et la puissance moyenne 
 * /sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj 
 * \version 0.1
 * \date 20/10/2022 
 * \author Jean-Louis Roch (Ensimag, Grenoble-INP - University Grenoble-Alpes) jean-louis.roch@grenoble-inp.fr
 * Lecture directe des compteurs Intel RAPL (cf https://recherche.noiraudes.net/ecoinfo/numres/ressources/TP/04-mesure-conso.html )
 * C'est une laternative sur des machines sur lesquelles les oprtions de "perf" estimant l'énergie consommée ne sont pas installées:
 * par exemple:  perf stat   -e duration_time -e task-clock -e cpu-clock   -e page-faults  -e power/energy-cores/ -e power/energy-ram/ command
*/ 

#include "perfMesure.h" 
#include <sys/time.h> // pour gettimeof day
#include <sys/resource.h> // pour getrusage
#include <fcntl.h>
#include <stdio.h>
#include <string.h> // strcmp, strlen, strncat
#include <stdlib.h> // system
#include <err.h> // err, warn

/**
 * \fn int get_energy_uj_counter(unsigned long* rapl_uj_counters)
 * \brief store the value value of RAPL energy_uji counters
 * \param rapl_uj_counters preallocated array larger than the number of counters 
 * \return nunber of Intel RAPL counters found (ie number of cores) 
 */
int get_energy_uj_counter(unsigned long* rapl_uj_counters ) 
{
   // Read all counters in files RAPL energy_ul that are readable and copy their values in rapl_uj_counters
   const char* ENERGY_COUNTER_PREFIX="/sys/class/powercap/intel-rapl/intel-rapl:" ;
   const char* ENERGY_COUNTER_SUFFIX="/energy_uj" ;
   const int MAXLENGTH_ENERGY_COUNTER_NAME=100 ;

   int NbCore = 0 ;
   for( int i=0; i< NBMAXCORE; ++i) 
   {  char fich_energy[MAXLENGTH_ENERGY_COUNTER_NAME] ; // 
      snprintf( fich_energy, MAXLENGTH_ENERGY_COUNTER_NAME, "%s%d%s", ENERGY_COUNTER_PREFIX, i, ENERGY_COUNTER_SUFFIX);
      FILE* fd =  fopen( fich_energy, "r" );
      if (fd == NULL) 
      {  // no more cores 
         NbCore = i ;
         #ifdef DEBUG
           fprintf(stderr, "Number of intel-rapl counters found: %d\n", NbCore ) ;
         #endif
         break ;
      } 
      else  
      {  // reading unsigned long value of intel-rapl counter
         if (fscanf(fd, "%lu", &( rapl_uj_counters [i ] ) ) != 1)  
         {  warn( "get_energy_uj_counter: %s%d%s : error while reading the value of the counter (long int expected). Value is set to 0. ",  ENERGY_COUNTER_PREFIX, i, ENERGY_COUNTER_SUFFIX ) ;
         }
         fclose( fd ) ;
      }
   }
   if (NbCore==0) 
   {  warn( "get_energy_uj_counter: energy counter file %s0%s not found ",  ENERGY_COUNTER_PREFIX, ENERGY_COUNTER_SUFFIX ) ;
      rapl_uj_counters[ 0 ] = 0 ; 
   }
   return NbCore ;
}
      

/*
 * void perfstart(struct myperf*  p) 
 * copy the value of counters from getrusage, gettimeofday and RAPL energy in *p
 */
void perfstart(struct myperf*  p) // get values of current counters
{
    get_energy_uj_counter( p->current_rapl_energy_uj) ;
    gettimeofday( &(p->current_timeofday), NULL);
    getrusage(RUSAGE_SELF, &(p->current_rusage) );
    p->cumul_elapsed_time = 0;
    p->cumul_cpuusertime = 0;
    p->cumul_systime = 0;
    p->cumul_energy = 0;
    p->cumul_pagequeries = 0;
    p->cumul_pagefaults = 0;
    p->cumul_read_blk = 0;
    p->cumul_write_blk = 0;
}

/*
 * void perfstop_and_display( FILE* out, struct myperf* p) 
 * prints on out the difference between current performance counter values and previous ones stored in *p; *p is updated with current values. 
 * The printing is displayed in stream out in text format (using fprintf) 
 * At the call, the value of counters in p are used as reference initial values; at the end, those values are updated with the current ones 
 */
void perfstop_and_display( FILE* out, struct myperf* p) // get values of current counters
{
   struct myperf old = *p ; 

   getrusage(RUSAGE_SELF, &(p->current_rusage) );
   gettimeofday(&(p->current_timeofday), NULL);
   int nb_core = get_energy_uj_counter( p->current_rapl_energy_uj) ;

   { // Compute and display elpased times and energy from old to p 
     // compute elapsed time in second
     double elapsed_time = -( old.current_timeofday.tv_sec + 1e-6 * old.current_timeofday.tv_usec ) ; 
     elapsed_time += (p->current_timeofday.tv_sec + 1e-6 *  p->current_timeofday.tv_usec ) ; 
     fprintf(out, "Elapsed time (in s) (from gettimeofday) .................. %g\n", elapsed_time ) ; 
     p->cumul_elapsed_time += elapsed_time;
    
     // compute cpu time in second
     double cpuusertime = -( old.current_rusage.ru_utime.tv_sec + 1e-6 * old.current_rusage.ru_utime.tv_usec ) ; 
     cpuusertime        += (  p->current_rusage.ru_utime.tv_sec + 1e-6 *  p->current_rusage.ru_utime.tv_usec ) ; 
     fprintf(out, "CPU user time (in s) (from getrusage) .................... %g\n", cpuusertime ) ; 
     p->cumul_cpuusertime += cpuusertime;
    
     // compute sys time in second
     double systime = -( old.current_rusage.ru_stime.tv_sec + 1e-6 * old.current_rusage.ru_stime.tv_usec ) ; 
     systime        += (  p->current_rusage.ru_stime.tv_sec + 1e-6 *  p->current_rusage.ru_stime.tv_usec ) ; 
     fprintf(out, "CPU user time (in s) (from getrusage) : %g\n", systime ) ; 
     fprintf(out, "CPU usage ratio (CPU user time/elapsed time) ............. %g\n", cpuusertime/elapsed_time ) ; 
     p->cumul_systime += systime;
    
     if (nb_core != 0) 
     {
        // energy in kWh
        double  energy = 0 ;
        for (int i = 0 ; i < nb_core; ++i) 
          energy += (p->current_rapl_energy_uj[ i ] - old.current_rapl_energy_uj[ i ]) ;
        energy = energy / 3600.0e9 ; // Conversion 1 kWh = 3600*1e9 microJoule
     fprintf(out, "Elapsed energy (sum of intel-rapl:uj counters, in kWh) ... %g\n", energy ) ; 
     fprintf(out, "Energy for CPU usage ratio (in kWh) ...................... %g\n", energy*cpuusertime/elapsed_time ) ; 
     fprintf(out, "Energy meanpower (Energy / elapsed time, in W) ........... %g\n", energy/elapsed_time ) ; 
        p->cumul_energy += energy;
     }
   }

   { // compute page faults (without I/O and that required I/O)
     double pagefaultswoIO = p->current_rusage.ru_minflt - old.current_rusage.ru_minflt  ;
     fprintf(out, "Number of page queries (soft, from getrusage) ............ %g\n", pagefaultswoIO ) ; 
     double pagefaultswIO = p->current_rusage.ru_majflt - old.current_rusage.ru_majflt ;
     fprintf(out, "Number of page faults (hard, from getrusage) ............. %g\n", pagefaultswIO ) ; 
     p->cumul_pagequeries += pagefaultswoIO;
     p->cumul_pagefaults += pagefaultswIO;
   }

   { // compute number of blocks read and written
     double read_blk = p->current_rusage.ru_inblock - old.current_rusage.ru_inblock  ;
     fprintf(out, "Number of block reads .................................... %g\n", read_blk ) ; 
     double write_blk = p->current_rusage.ru_oublock - old.current_rusage.ru_oublock  ;
     fprintf(out, "Number of block writes ................................... %g\n", write_blk ) ; 
     p->cumul_read_blk += read_blk;
     p->cumul_write_blk += write_blk;
   }

   /* Other counters ingnored in rusage : 
             long  ru_maxrss;         // Taille résidente maximale 
             long  ru_ixrss;          // Taille de mémoire partagée 
             long  ru_idrss;          // Taille des données non partagées
             long  ru_isrss;          // Taille de pile              
             long  ru_nswap;          // Nombre de swaps              
             long  ru_msgsnd;         // Nombre de messages IPC émis   
             long  ru_msgrcv;         // Nombre de messages IPC reçus   
             long  ru_nsignals;       // Nombre de signaux reçus         
             long  ru_nvcsw;          // Chgmnts de contexte volontaires  
             long  ru_nivcsw;         // Chgmnts de contexte involontaires
     */

    /* mise à jour des valeurs courantes des compteurs (hors cumul) */
    get_energy_uj_counter( p->current_rapl_energy_uj) ;
    gettimeofday(&(p->current_timeofday), NULL);
    getrusage(RUSAGE_SELF, &(p->current_rusage) );
}
 
