#ifndef __MOTIF_H
#define __MOTIF_H
#include <inttypes.h>

/* Type couleur 
 * Contient une couleur en RGB, le rouge est sur l'octet de poids faible, le
 * vert celui en deuxieme position et le bleu celui en troiseme. le quatrieme
 * est sans effet. */
typedef uint32_t couleur;

/* Structure de donnees definisant un motif rectangulaire de lxh
 * pixels. Le champ valeur contient la couleur de chaque pixel. */
struct motif {
        uint16_t l; // largeur du motif
        uint16_t h; // Hauteur du motif
        couleur **valeur; // Contenu du motif dans un tableau l*h
};

/* Donne le sens de rotation pour une operation de pivotement. */
typedef enum _dir {
        d90,
        g90
} dir;

/* Donne l'axe de symetrie pour une operation de retournement. */
typedef enum _axe {
        hori,
        verti
} axe;

/* Definition d'un point en adresse relative. */
struct point {
        float x; // abscisse relative du point dans le motif : la valeur 1
                 // correspond a l'indice min(l,h) dans l'image 
        float y; // ordonnee relative du point
};

/* Definition d'une droite en adresse relative. */
struct droite {
        struct point depart; // point de depart
        struct point arrivee; // point d'arrivee
        couleur coul; // couleur de la droite
};

/* Definition d'un cercle en adresse relative. */
struct cercle {
        struct point centre; // point au centre du cercle
        struct point depart; // point de depart du trace
        float ang; // angle du trace en degre (valeur entre 0 et 360)
        couleur coul; // couleur du cercle
};

/* Alloue un motif de taille lxh et l'initialise avec la couleur fond
 * et renvoie un pointeur vers le motif alloue ou NULL en cas d'echec
 * d'allocation. */
extern struct motif *creer_motif(uint16_t l, uint16_t h, couleur fond);

/* Alloue et initialise un motif identique a celui pointe par src et
 * renvoie un pointeur vers ce motif.  */
extern struct motif *copier_motif(struct motif *src);

/* Initialise le motif pointe par m avec la couleur de fond fond. */
extern void init_motif(struct motif *m, couleur fond);

/* Libere la memoire utilisee par le motif pointe par m. */
extern void detruire_motif(struct motif *m);

/* Trace la droite relative pointe par d dans le motif pointe par
 * m. */
extern void tracer_droite(struct motif *m, struct droite *d);

/* Trace l'arc de cercle relatif pointe par arc dans le motif pointe
 * par m. */
extern void tracer_cercle(struct motif *m, struct cercle *arc);

/* Remplit par diffusion autour du point pointe par p le motif pointe
 * par m avec la couleur coul.  */
extern void remplir(struct motif *m, struct point *p, couleur coul);

/* Realise la rotation du motif pointe par m soit a droite soit a
 * gauche selon la valeur de la direction passee en parametre. */
extern void pivoter(struct motif *m, dir direction);

/* Realise un retournement du motif pointe par m selon l'axe passe en
 * parametre. */
extern void retourner(struct motif *m, axe axe);

/* Realise l'export du motif pointe par m au format PPM (P6) dans le
 * fichier chemin. */ 
extern void exporter_PPM(struct motif *m, const char *chemin);

/* Extrait un motif du fichier chemin au format PPM (P6) et renvoie un
 * pointeur sur ce motif. */ 
extern struct motif *importer_PPM(const char *chemin);

/* Debug purpose */
extern void afficher_motif(struct motif *m);

#endif
