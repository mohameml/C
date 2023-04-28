#ifndef _NN_H_
#define _NN_H_

/* pre-declaration de la structure privee array (evite d'inclure
 * array.h) */
struct array;
#include "image.h"  // dist_func

/* recherche du plus proche voisin au sens de la distance "dist_func"
 * pour un groupe d'image tests, par l'algorithme naif exhaustif. La
 * table d'indices (de meme taille que test_images) est allouee et
 * doit etre liberee par l'appelant apres usage. */
uint32_t* brute_force_NN(struct array* dataset, struct array* test_images,
			  image_distance dist_func);

/* pre-declaration de la structure privee kdtree (evite d'inclure
 * kdtree.h) */
struct kdtree;

/* recherche du plus proche voisin au sens de la distance "dist_func"
 * pour un groupe d'image tests, grace a un kd-arbre "kdtree". La
 * table d'indices (de meme taille que test_images) est allouee et
 * doit etre liberee par l'appelant apres usage. */
uint32_t* kdtree_approx_NN(struct kdtree*, struct array* test_images,
			   image_distance dist_func);

#endif
