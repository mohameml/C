#include <stdio.h>
#include <string.h>

// definir de structure 

typedef struct Player 
{
    char username[256];
    int hp ;
    int mp ;
}Player;



int main(void)
{
    Player p1 ={"jason",100,100};
    // affichage de strcut Player 
    printf("-----------------affichage----------------\n");
    printf("Le Nom de palyer : %s \n",p1.username);
    printf("PV : %d | PM : %d \n",p1.hp , p1.mp);

    // mnt on veut changer le "Player"

    printf("------------changement de joueur--------------\n");
    strcpy(p1.username,"Nebil");
    p1.hp=50;
    p1.mp=50;
    printf("Le Nom de palyer : %s \n",p1.username);
    printf("PV : %d | PM : %d \n",p1.hp , p1.mp);


    // on veut maintenat interagi avec L'utilisatuer 

    printf("--------------L'utilisateur-----------------\n");
    definir_jouer(&p1);
    printf("Le Nom de palyer : %s \n",p1.username);
    printf("PV : %d | PM : %d \n",p1.hp , p1.mp);
    return 0 ;
}


void definir_jouer( Player *p)
{
    printf("What is your name ? ");
    scanf("%s", (*p).username);
    (*p).mp=100;
    (*p).hp=100;

}