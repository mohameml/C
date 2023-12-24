/*****************************************************
 * Copyright Grégory Mounié 2008-2015                *
 *           Simon Nieuviarts 2002-2009              *
 * This code is distributed under the GLPv3 licence. *
 * Ce code est distribué sous la licence GPLv3+.     *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "variante.h"
#include "readcmd.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>

#ifndef VARIANTE
#error "Variante non défini !!"
#endif

/* Guile (1.8 and 2.0) is auto-detected by cmake */
/* To disable Scheme interpreter (Guile support), comment the
 * following lines.  You may also have to comment related pkg-config
 * lines in CMakeLists.txt.
 */


#define MAX_JOBS 50  // nombre de job maximale e

/* structure  JOb :*/
struct Job 
{
    pid_t pid; // pid du processus 
    char command[1024];  // la commande 
};

int indexJob  =  0 ; 
struct Job listJobs[MAX_JOBS];



void executer_commande(struct cmdline *l);
void displayJobs() ;
void executer_pipe(int fd[2] , struct cmdline *l);
void gestion_Status_fils(int status);




#if USE_GUILE == 1
#include <libguile.h>

int question6_executer(char *line)
{
	/* Question 6: Insert your code to execute the command line
	 * identically to the standard execution scheme:
	 * parsecmd, then fork+execvp, for a single command.
	 * pipe and i/o redirection are not required.
	 */
	printf("Not implemented yet: can not execute %s\n", line);

	/* Remove this line when using parsecmd as it will free it */
	free(line);
	
	return 0;
}

SCM executer_wrapper(SCM x)
{
        return scm_from_int(question6_executer(scm_to_locale_stringn(x, 0)));
}
#endif


void terminate(char *line) {
#if USE_GNU_READLINE == 1
	/* rl_clear_history() does not exist yet in centOS 6 */
	clear_history();
#endif
	if (line)
	  free(line);
	printf("exit\n");
	exit(0);
}


int main() 
{



    printf("Variante %d: %s\n", VARIANTE, VARIANTE_STRING);

#if USE_GUILE == 1
        scm_init_guile();
        /* register "executer" function in scheme */
        scm_c_define_gsubr("executer", 1, 0, 0, executer_wrapper);
#endif

	while (1) 
	{
		struct cmdline *l;
		char *line=0;

		char *prompt = "ensishell>";

		/* Readline use some internal memory structure that
		   can not be cleaned at the end of the program. Thus
		   one memory leak per command seems unavoidable yet 
		*/
		
		line = readline(prompt);
		
		if (line == 0 || ! strncmp(line,"exit", 4)) 
		{
			terminate(line);
		}

#if USE_GNU_READLINE == 1
		add_history(line);
#endif


#if USE_GUILE == 1
		/* The line is a scheme command */
		if (line[0] == '(') 
		{
			char catchligne[strlen(line) + 256];
			sprintf(catchligne, "(catch #t (lambda () %s) (lambda (key . parameters) (display \"mauvaise expression/bug en scheme\n\")))", line);
			scm_eval_string(scm_from_locale_string(catchligne));
			free(line);
            continue;
        }
#endif

		/* parsecmd free line and set it up to 0 */
		l = parsecmd( & line);

		/* If input stream closed, normal termination */
		if (!l) 
		{
			terminate(0);
		}
		

		
		if (l->err) 
		{
			/* Syntax error, read another command */
			printf("error: %s\n", l->err);
			continue;
		}


	


		int save_in , save_out ;
		int fd_in , fd_out ;

		if (l->in)
		{

			fd_in = open(l->in , O_RDONLY , 0644); // ouvrir le fichier en mode lecture seulle 

			if(fd_in==-1)
			{
				printf("Erreur lors de l'ouverture du fichier : %s \n" , l->in);
				exit(1);
			}

			save_in = dup(STDIN_FILENO); // sauvegarnd du descripetur du STDIN

			dup2(fd_in , STDIN_FILENO);  // rédriction de l'entrée standsr vers le fichier l->in 




		} 
		
		if (l->out)
		{
			fd_out = open(l->out , O_WRONLY | O_CREAT | O_TRUNC, 0644);

			if(fd_out==-1)
			{
				printf("Erreur lors de l'ouverture du fichier : %s \n" , l->out);
				exit(1);
			}

			save_out = dup(STDOUT_FILENO); // sauvegarnd du descripetur du STDOUT 

			dup2(fd_out , STDOUT_FILENO);  // rédriction du sortie standsr vers le fichier l->out 

		} 








		if (strcmp(*(l->seq[0]) ,"jobs")==0)
		{
			// pour la commande jobs : 

			displayJobs();

		}
		else
		{
	
			int nombre_pipe = 0 ;

			for (int i=0; l->seq[i]!=0; i++) 
			{
				nombre_pipe++;
			}


			if(nombre_pipe > 1)
			{

				int fd[2];

				if(pipe(fd)==-1)
				{
					perror("Erreur lors de la pipe : \n");
					exit(1);
				}

				executer_pipe(fd , l);
			}
			else
			{
				// cas d'une commande simple :
				executer_commande(l);
			}


		}
		


		// on ferme tout le descripteru et on rédirige les canaux par défaut :

		if(l->in)
		{
			close(fd_in);

			dup2(save_in ,STDIN_FILENO); // on rétablit STDOUT par défaut 
		}

		if(l->out)
		{
			close(fd_out);

			dup2(save_out ,STDOUT_FILENO); // on rétablit STDOUT par défaut 
		}

	}

}




void executer_pipe(int fd[2] , struct cmdline *l)
{
	// version simple du pie 

	int id = fork();

	if(id==-1)
	{
		perror("Erreur lors du fork dans pipe() \n");
		exit(2);
	}


	if(id==0)
	{
		// le processus fils :
		close(fd[0]); // on ferme le descripteur de lecture pour le fils 
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		execvp(*(l->seq[0]) , l->seq[0]);

		printf("il y' aun errure lors de l'exécution de la commande : %s \n" , *(l->seq[0]));
		exit(1);


	}
	else
	{




		int id2 = fork() ; 


		if(id2==-1)
		{
			perror("Erreur lors du fork dans pipe() \n");
			exit(3);	
		}


		if(id2==0)
		{

			close(fd[1]);
			dup2(fd[0] , STDIN_FILENO);
			close(fd[0]);

			execvp(*(l->seq[1]) , l->seq[1]);	
		
			printf("il y' un errure lors de l'exécution de la commande : %s \n" , *(l->seq[1]));
			exit(1);
		}
		else
		{
			close(fd[1]);
			close(fd[0]);
			int status_id2 ;
			int status ;

			waitpid(id,&status , 0);

		gestion_Status_fils(status);

			waitpid(id2,&status_id2 , 0);

			gestion_Status_fils(status_id2);
		}

	}

}



void executer_commande(struct cmdline *l)
{

	int id = fork();

	if(id==-1 )
	{
		printf("Erreur lors de la fork() \n");
		exit(1);
	}

	if(id==0)
	{
		// exectuion de la commande de l'utilisateur : 

		execvp(*(l->seq[0]) , l->seq[0] );
		printf("il y' aun errure lors de l'exécution de la commande : %s \n" , *(l->seq[0]));
		exit(1);
	}
	else
	{
		int status ;

		if(l->bg)
		{
			// on ajoute la tache  à la liste de jobs :
			
			if(indexJob < MAX_JOBS)
			{
				printf("processus : [%d] %d in background \n" , indexJob + 1 , id);

				listJobs[indexJob].pid = id; // le id de fils 

				strcpy(listJobs[indexJob].command , *(l->seq[0]));

				indexJob++;
			}
			else
			{
                printf("Nombre maximal de travaux atteint. Ne peut pas ajouter de nouveau travail.\n");

			}


		}
		else
		{
			waitpid(id,&status , 0);

			gestion_Status_fils(status);
		}
	}
}




void displayJobs() 
{
	int status ;

	for(int i =0 ; i<indexJob ; i++)
	{
		int res = waitpid(listJobs[i].pid , &status , WNOHANG);

		if(res==-1)
		{
			printf("Errure waitpid dans dipslayJobs \n");
		}
		else if(res==0)
		{
			// donc le processus fils n'est pas encore terminée :

			printf("[%d] %d  Running \t  %s \n" , i + 1, listJobs[i].pid , listJobs[i].command);
		}
		else
		{
			printf("[%d] %d  Done \t  %s \n" , i+1 , listJobs[i].pid , listJobs[i].command);


			// ajuster la table de jobs :
			for(int j =i ; j< indexJob -1 ; j++)
			{
				listJobs[j] = listJobs[j+1];
			}

			indexJob-- ;
		}	
	}

}


void gestion_Status_fils(int status)
{
	if (WIFEXITED(status)==0) 
	{

		perror("Le processus enfant est pas terminé d'une maniére anormale \n");
		exit(1);
		

	}
	else
	{
		if(WEXITSTATUS(status)!=0)
		{
			printf("le processus enfnat se termine avce un code de retour = %d \n" , WEXITSTATUS(status));
		}
					
	}

}

