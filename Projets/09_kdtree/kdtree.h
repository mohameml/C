#ifndef _KDTREE_H_
#define _KDTREE_H_

#include <stdint.h>

/* pre-declaration du type noeud du kdtree */
struct kdnode;

/* les noeuds du kdtree peuvent etre de 2 types: interne ou feuille */
/* noeud interne */
struct kdbranch {

	const uint8_t *split_image;   /* pointeur sur l'image separatrice */
	uint32_t split_pixel;	      /* indice du pixel separateur */

	/* pointeur vers les sous-arbres divisés selon la valeur du
	 * pixel "split_pixel" de l'image separatrice */
	struct kdnode *left, *right;
};

/* feuille */
struct kdleaf {
	/* ensemble d'images de la feuille (tableau de pointeurs vers
	 * les donnees de chaque image) */
	const uint8_t **images;

	/* nombre d'images de la table se rapportant a cette feuille */ 
	uint32_t size;
};

/* type enumere permettant de caracteriser le type d'un noeud kdnode */
typedef enum {
	BRANCH,                /* caracterisation noeud interne */
	LEAF                   /* caracterisation feuille */
} kdnode_type;

/* structure de noeud du kd-arbre */
struct kdnode {
	kdnode_type type;
	union {
		struct kdleaf leaf;
		struct kdbranch branch;
	} node;
};

/* structure encapsulant un kd-arbre */
struct kdtree {
	const struct array *dataset;  /* pointeur sur images de la base*/
	struct kdnode *root;          /* racine du kd-tree */
	uint32_t nb_pixel;            /* nb de pixels d'une image*/
	uint32_t linear_cutoff;       /* taille max des feuilles */
};


/* functions pour creer et detruire un kdtree */

/* creer un kdtree a partir d'un jeu de donnees. NOTE: le kd-tree peut
 * stocker des pointeurs sur des images du jeu de donnees et donc
 * l'utilisation du kdtree suppose que le dataset associe n'est pas
 * modifie ou desalloue */
struct kdtree* create_kdtree(const struct array* dataset, uint32_t linear_cutoff);

/* libere toute la memoire du kdtree */
void free_kdtree(struct kdtree*);

#endif // KDTREE_H
