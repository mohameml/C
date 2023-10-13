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
    __sighandler_t ancien = signal(SIGINT, custom_handler);

    int count = 0 ;
    while (1) {
        printf("En attente...\n");
        sleep(1);
        count++ ;

        if(count==6)
        {
            signal(SIGINT,ancien);
        }
    }

    return 0;
}