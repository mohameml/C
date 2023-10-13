# cour 07 : les signaux en C 


## 1. Introduction :

- En langage C, les signaux sont des mécanismes qui permettent aux processus de communiquer entre eux et avec le système d'exploitation. 

- Les signaux sont utilisés pour notifier un processus de certains événements, tels que les interruptions, les erreurs, ou pour demander au processus de terminer son exécution. 


- les  concepts de base liés aux signaux en C :

    1. **Génération de signaux :** 
        - Les signaux sont générés par divers événements, tels que : 
            - des erreurs matérielles, 
            - des interruptions clavier, 
            - des terminaisons de processus .
        
        - Les signaux peuvent également être générés manuellement par un processus en utilisant des appels système tels que `kill`.

    2. **Réception de signaux :** 
        
        - Un processus peut recevoir des signaux de plusieurs sources, y compris d'autres processus ou du système d'exploitation. 
        
        - Lorsqu'un processus reçoit un signal, il peut prendre des mesures en conséquence.

    3. **Actions des signaux :** 
        
        - Chaque signal a une action par défaut associée à sa réception:  
            - Par exemple, le signal SIGTERM (15) demande à un processus de se terminer. 
            
        - un processus peut choisir de redéfinir l'action par défaut d'un signal en utilisant la fonction `signal()` ou, de manière plus moderne, `sigaction()`.

    4. **Liste des signaux courants :** 
    
    - Il existe un certain nombre de signaux prédéfinis dans les systèmes Unix/Linux :
        - **SIGINT (2)** : Interruption depuis le clavier (généralement Ctrl+C).
        - **SIGTERM (15)** : Demande de terminaison propre du processus.
        - **SIGKILL (9)** : Terminaison immédiate du processus (non redéfinissable).
        - **SIGALRM (14)** : Alarme d'horloge (utilisé avec `alarm()`).
        - **SIGHUP (1)** : Hang-up, déconnexion du terminal.
        - **SIGUSR1 (10)** et SIGUSR2 (12) : Signaux personnalisables.
        - **SIGCHLD (17)** : Indique qu'un enfant a changé d'état (utilisé avec `wait()` ou `waitpid()`).
        - **SIGSTOP (17)** : est utilisé pour suspendre un processus en cours d'exécution. Il arrête le processus et le place en état d'arrêt
        - **SIGCONT (18)** : Ce signal est utilisé pour reprendre un processus qui a été suspendu avec SIGSTOP.
        - **SIGCHLD (20)** : Ce signal est envoyé au processus parent lorsqu'un de ses processus fils se termine.




## 2. la fonction `kill` :

- La fonction `kill()` en langage C est utilisée pour envoyer un signal à un processus ou un groupe de processus. 

- Cette fonction peut être utilisée pour communiquer avec d'autres processus et les informer de certaines actions à effectuer. 

- la signature de la fonction `kill()` :

```c
#include <signal.h>

int kill(pid_t pid, int sig);
```

- `pid` est le PID (identifiant de processus) du processus auquel vous souhaitez envoyer le signal. Vous pouvez spécifier `pid` de la manière suivante :
  - Un PID positif pour cibler un processus spécifique.
  - 0 pour envoyer le signal à tous les processus du même groupe de processus.
  - -1 pour envoyer le signal à tous les processus du même utilisateur.
  - Un PID négatif pour envoyer le signal à tous les processus dans le groupe de processus spécifié par `pid`.

- `sig` est le numéro du signal que vous souhaitez envoyer. Vous pouvez spécifier un numéro de signal (par exemple, `SIGTERM` pour terminer un processus de manière propre) ou un numéro de signal personnalisé que vous avez défini.

- un exemple simple d'utilisation de la fonction `kill()` pour envoyer le signal SIGTERM à un processus spécifique :

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>



int main(void)
{

    int pid = fork();


    if(pid==0)
    {
        while(1)
        {
            printf("I do somethig here  .....can you wait please ...\n");
            sleep(1);
        }
    }
    else 
    {   sleep(3);
        printf("I dont care ,  I will kill you fu** you , son of b*** ... \n");
        kill(pid,SIGKILL);
        wait(NULL);
    }




    return 0 ;
}
```



## 3. la fonction ``signal()` :

- La fonction `signal()` en langage C est utilisée pour définir la manière dont un processus réagira à la réception d'un signal spécifique. 

- Elle permet de personnaliser la gestion des signaux par un processus. 

- la signature de la fonction `signal()` :

```c
#include <signal.h>

_sighandler_t signal(int signo, void handler(int) );
```

- `signo` est le numéro du signal que vous souhaitez gérer. Vous spécifiez le numéro du signal, tel que `SIGINT` (pour Ctrl+C) ou `SIGTERM` (pour terminer proprement un processus).

- `handler` est un pointeur vers la fonction de gestion de signal (signal handler) que vous souhaitez exécuter lorsque le signal est reçu. Le gestionnaire de signal est une fonction qui prend un argument entier (le numéro du signal) et ne renvoie rien (`void`).

- La fonction `signal()` renvoie un pointeur vers l'ancien gestionnaire de signal du signal spécifié. Vous pouvez utiliser cette valeur de retour pour restaurer le gestionnaire de signal par défaut après l'avoir modifié.


- un exemple simple d'utilisation de la fonction `signal()` pour personnaliser la gestion du signal SIGINT (généralement généré par Ctrl+C) :

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void custom_handler(int signo) {
    if (signo == SIGINT) {
        printf("Signal SIGINT (Ctrl+C) reçu. Ignoré.\n");
    }
}

int main() {
    // Définir un gestionnaire de signal personnalisé pour SIGINT
    signal(SIGINT, custom_handler);

    while (1) {
        printf("En attente...\n");
        sleep(1);
    }

    return 0;
}
```

Dans cet exemple, nous utilisons `signal()` pour définir un gestionnaire de signal personnalisé (`custom_handler`) pour le signal SIGINT. Lorsque le signal SIGINT est reçu (par exemple, en appuyant sur Ctrl+C), le gestionnaire `custom_handler` sera appelé, affichant un message personnalisé. 




