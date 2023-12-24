/**
 * \file perfMesureCommandch
 * \brief Utilise getursage, getimeofday et les compteurs Intel RAPL pour afficher des performances dont l'energie consommée et la puissance moyenne 
 * /sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj 
 * \version 0.1
 * \date 22/10/2022 
 * \author Jean-Louis Roch (Ensimag, Grenoble-INP - University Grenoble-Alpes) jean-louis.roch@grenoble-inp.fr
 * Usage : perfMesureCommand 
NAME
     perfMesureCommand - prints performance (energy) consumed by execution  of: command
SYNOPSIS
     perfMesureCommand [-h] cmd 
DESCRIPTION
     perfMesureCommand - prints some resource consumed by execution of cmd
     For energy, the value of the counter stored in /sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj is read before and
     after execution of:  system( cmd )
     The difference of the two values gives the number of uJ consumed, and is converted in kWh (dividing by 3.6e+9). 
     If there are several counters, till intel-rapl:K with K integer, the value of each difference (for each of the ++1 counters) are summed.
     The intantaneous power is given by dividing this energy by the elapsed time (measured by gettimeofday).
EXIT STATUS
     The program exits 0 on success, and >0 if an error occurs.
EXAMPLES
     perfMesureCommand  ls 
     perfMesureCommand bin/distanceEditionIter  tests/ba52_recent_omicron.fasta 153 30183 tests/wuhan_hu_1.fasta 116 30331  
ALTERNATIVE: "perf stat" such as command below:
     /usr/bin/time perf stat  -e duration_time -e task-clock -e cpu-clock -e page-faults  -e power/energy-cores/ -e power/energy-ram/ \ 
         bin/distanceEditionIter  tests/ba52_recent_omicron.fasta 153 30183 tests/wuhan_hu_1.fasta 116 30331  &> perfmon
*/ 

#include "perfMesure.h"
#include <stdio.h>
#include <string.h> // strcmp, strlen, strncat
#include <stdlib.h> // system
#include <err.h> // err, warn

/** 
  * \fn void printusage(int argc, char* argv)
  * \brief prints on stderr the correct usage 
  * \param argc number of args passed 
  * \param argv arguments
  */
void printusage(int argc, char** argv)
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
	"     The program exits 0 on success, and >0 if an error occurs.\n"
	"EXAMPLE\n"
	"           %s  sleep 5\n", 
		argv[0], argv[0], argv[0], argv[0], argv[0]) ;
}


/**
 * \fn int main(int argc, char** argv) 
 * \brief executes (with stdlib function system ) the command passed in argument and prints performance counters (recorded before and after the systeme command)
 * \param argc number of arguments
 * \param argv arguments (eithe -h or --h or the command itself
 */
int main(int argc, char** argv) 
{
   if (argc <= 1) 
   { printusage(argc, argv ) ;
     err(1, "%s : bad number or arguments (cf usage).", argv[0] ) ;
   }
   if ( (strcmp(argv[1], "-h")==0)  || (strcmp(argv[1], "--h")==0)  )
     printusage(argc, argv ) ;
   else
   {  // Building and running command in argument
      #define  _SIZEMAXCMD_JL  1000 
      char cmd [ _SIZEMAXCMD_JL + 15 ] = "/usr/bin/time "; // 15=strlen("/usr/bin/time ")+1
      {  // Recuperation des arguments pour la commande systeme
         int rem_size = sizeof( cmd ) - strlen(cmd) - 1 ;
         for (int arg=1; arg < argc ; ++arg) 
         { int arglen = strlen(argv[arg]) ;
           if (arglen > rem_size + 1) 
             err(1, "%s: command passed in argument would be truncated to %d char.", argv[0], _SIZEMAXCMD_JL);
           strncat(cmd, argv[arg], rem_size ) ;
           strncat(cmd, " ", 2 ) ;
           rem_size = rem_size - arglen - 1 ;
         }
      }
      #undef  _JLSIZEMAXCMD_JL  

      // Lancement du chronometre
      struct myperf p ;
      perfstart( &p ) ;
      int valcde = system(cmd) ; 
      perfstop_and_display(stdout, &p ) ;
      printf("%d\n", valcde) ;
   }
   return 0 ;
}
