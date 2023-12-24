/**
 * \file energieMesure.c
 * \brief Utilise les compteurs RAPL pour mesurer l'energie consommée et la puissance moyenne 
 * /sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj 
 * \version 0.1
 * \date 18/10/2022 
 * \author Jean-Louis Roch (Ensimag, Grenoble-INP - University Grenoble-Alpes) jean-louis.roch@grenoble-inp.fr
 * Usage : energieMesure command 
NAME
     energieMesure - prints energy consumed by execution  of: command
SYNOPSIS
     energieMesure [-h] cmd 
DESCRIPTION
     energieMesure - prints energy consumed by execution of cmd
     The value of the counter stored in /sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj is read before and
     after execution of:  system( cmd )
     The difference of the two values gives the number of uJ consumed, and is converted in kWh (dividing by 3.6e+9). 
     If there are several counters, till intel-rapl:K with K integer, the value of each difference (for each of the ++1 counters) are summed.
     The intantaneous power is given by dividing this energy by the elapsed time (measured by gettimeofday).

-weighted by the ratio of processor use (given by /usr/bin/time) and the el
      /usr/bin/time perf stat        -e duration_time -e task-clock -e cpu-clock   -e page-faults  -e power/energy-cores/ -e power/energy-ram/ bin/distanceEditionIter  tests/ba52_recent_omicron.fasta 153 30183 tests/wuhan_hu_1.fasta 116 30331  &> perfmon
1.97user 0.01system 0:02.03elapsed 98%CPU (0avgtext+0avgdata 17248maxresident)

EXIT STATUS
     The program exits 0 on success, and >0 if an error occurs.
EXAMPLE
           energieMesure.c  ls 
*/ 

void printusage(int argc, char* argv)
{
  fprintf(stderr, 
	"Usage : %s command\n"
	"NAME\n"
	"     %s - prints energy consumed by execution  of: command\n"
	"SYNOPSIS\n"
	"     %s [-h] cmd\n"
	"DESCRIPTION\n"
	"     %s - prints energy consumed by execution of cmd\n"
	"     The value of the counter stored in /sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj is read before and\n"
	"     after execution of:  system( cmd )\n"
	"     The difference of the two values gives the number of uJ consumed, and is converted in kWh (dividing by 3.6e+9).\n"
	"     If there are several counters, till intel-rapl:K with K integer, the value of each difference (for each of the ++1 counters) are summed.\n"
	"     The intantaneous power is given by dividing this energy by the elapsed time (measured by gettimeofday).\n"
	"EXIT STATUS\n"
	"     The program exits 0 on success, and >0 if an error occurs.\n"
	"EXAMPLE\n"
	"           %s  sleep 5\n", 
		argv[0], argv[0], argv[0], argv[0], argv[0]) ;
}
ZZZZZZZZZZZZ

#include <sys/time.h> // pour gettimeof day
#include <sys/resource.h> // pour getrusage
#include <stdio.h>
#include <ctype.h> // isdigit
#include <err.h> // err, warn

struct myperf 
{
  double elapsed_time_s;
  double user_time_s;
  double user_time_s;
  long   pagefaults_without_IO;
  long   pagefaults_with_IO;
  long   elapsedenergy_Wh;
  struct timeval current_timeofday ;
  struct rusage  current_rusage;
  unsigned long  current_rapl_energy_uj[ NMAXCORE ] = {0.0} ; 
}

#define ENERGY_COUNTER_PREFIX "/sys/class/powercap/intel-rapl/intel-rapl:"
#define ENERGY_COUNTER_SUFFIX "/energy_uj"
#define MAXLENGTH_ENERGY_COUNTER_NAME 100 ;

int getElapsedEnergy(unsigned long* rapl_uj_counters) 
{
   int NbCore = 0 ;
   char fich_energy[MAXLENGTH_ENERGY_COUNTER_NAME] ; // 
   for( int i=0; i< NBMAXCORE; ++i) 
   {  int fd =  open( snprintf( %s%d%s", ENERGY_COUNTER_PREFIX, i, MAXLENGTH_ENERGY_COUNTER_NAME), O_RDONLY));
      if (fd == -1) 
      {  // no more cores 
         NbCore = i ;
         #ifdef DEBUG
           fprintf(stderr, "Number of intel-rapl counters found: %d\n", NbCore ) ;
         #endif
         break ;
      } 
      else  
      {  // reading value of intel-rapl counter
         int c ;
         unsigned long val = 0 ;
         energy_uj [i ] = 0 ;
         while ( isdigit (c = getc(fd)) )
            val = 10 * val + (c - (int)'0') ; 
         rapl_uj_counters[ i ] = val ; 
         //energy_uj [i ] = atof( buf ) / 3600.0e9 ; // Conversion 1 kWh = 3600*1e9 microJoule
      }
   }
   if (NbCore==0) 
   {  warn( "getElapsedEnergy: counter %s0%s not found.\n",  ENERGY_COUNTER_PREFIX, ENERGY_COUNTER_SUFFIX ) ;
      rapl_uj_counters[ 0 ] = 0 ; 
   }
   return NbCore ;
}
      

void perfstart(struct myperf*  p) // get values of current counters
{
    getElapsedEnergy( p->current_rapl_energy_uj) ;
    gettimeofday(&(p->current_timeofday), NULL);
    getrusage(RUSAGE_SELF, &(p->current_rusage);
}
#ifdef DEBUG
    printf("seconds : %ld\nmicro seconds : %ld", current_time.tv_sec, current_time.tv_usec);
#endif //DEBUG
    elapsed_time = current_time.tv_sec + 1e-6 * current_time.tv_usec
}

void perfstop_and_display( FILE* out, struct myperf* p) // get values of current counters
{
   struct myperf old = *p ; 

   getrusage(RUSAGE_SELF, &(p->current_rusage);
   gettimeofday(&(p->current_timeofday), NULL);
   int nb_core = getElapsedEnergy( p->current_rapl_energy_uj) ;

   { // Compute and display elpased energy from old to p 
     double  energy = 0 ;
     for (int i = 0 ; i < nb_core; ++i) 
       energy += (p->current_rapl_uj_counters[ i ] - old.current_rapl_uj_counters[ i ]) ;
     energy = energy / 3600.0e9 ; // Conversion 1 kWh = 3600*1e9 microJoule
     fprintf("out, "Elapsed energy (sum of intel-rapl:uj counters, in kWh) : %g\n", energy ) ; 
   }

   { // compute elapsed time in second
     double elapsed_time = -( old.current_timeofday.tv_sec + 1e-6 * old.current_timeofday.tv_usec ) ; 
     elapsed_time += (p->current_timeofday.tv_sec + 1e-6 *  p->current_timeofday.tv_usec ) ; 
     fprintf("out, "Elapsed time (in s) (from gettimeofday) : %g\n", elapsed_time ) ; 
   }

   { // compute cpu time in second
     double cpuusertime = -( old.current_rusage.ru_utime.tv_sec + 1e-6 * old.current_rusage.ru_utime.tv_usec ) ; 
     cpuusertime        += (  p->current_rusage.ru_utime.tv_sec + 1e-6 *  p->current_rusage.ru_utime.tv_usec ) ; 
     fprintf("out, "CPU user time (in s) (from getrusage) : %g\n", cpuusertime ) ; 
   }

   { // compute sys time in second
     double systime = -( old.current_rusage.ru_stime.tv_sec + 1e-6 * old.current_rusage.ru_stime.tv_usec ) ; 
     systime        += (  p->current_rusage.ru_stime.tv_sec + 1e-6 *  p->current_rusage.ru_stime.tv_usec ) ; 
     fprintf("out, "CPU user time (in s) (from getrusage) : %g\n", systime ) ; 
   }

   { // compute page faults (without I/O and that required I/O)
     double pagefaultswoIO = p->current_rusage.ru_minflt - old.current_rusage.ru_minflt  ;
     fprintf("out, "Number of page queries (soft, from getrusage) : %g\n", pagefaultswoIO ) ; 
     double pagefaultswIO = p->current_rusage.ru_majflt - old.current_rusage.ru_majflt ;
     fprintf("out, "Number of page faults (hard, from getrusage) : %g\n", pagefaultswIO ) ; 
   }

   { // compute number of blocks read and written
     double read_blk = p->current_rusage.ru_inblock - old.current_rusage.ru_inblock  ;
     fprintf("out, "Number of block reads : %g\n", read_blk ) ; 
     double write_blk = p->current_rusage.ru_outblock - old.current_rusage.out_inblock  ;
     fprintf("out, "Number of block writes : %g\n", write_blk ) ; 
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
    getElapsedEnergy( p->current_rapl_energy_uj) ;
    gettimeofday(&(p->current_timeofday), NULL);
    getrusage(RUSAGE_SELF, &(p->current_rusage);
}


