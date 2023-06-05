#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdint.h>

/* predeclaration de array */
struct array;

/* remttre les images du tableau "a" a l'echelle avec une nouvelle
   taille plus petite width x height */
struct array* image_downscale(const struct array* a,
			      uint32_t width, uint32_t height);

/* charger les images d'un fichier .gz au format MNIST (decrit
 * http://yann.lecun.com/exdb/mnist/) */
struct array* load_image_array(char *gzfilename);

/* charger les etiquettes correspondantes d'un fichier .gz, au format
 * MNIST (http://yann.lecun.com/exdb/mnist/) */
struct array* load_label_array(char *gzfilename);

/* charger un fichier pgm dans un tableau (a une seule entree) */
struct array* load_pgm_image(char *pgmfilename);

/* sauvegarder l'element d'indice "elem" du tableau au format pgm */
void save_pgm_image(char *filename, const struct array* a, uint32_t elem);

/* definit le type pointeur de fonction de distance entre deux images
 * (pointeur vers tableau d'octet brut tel que stockes pour chaque
 * element d'un tableau array). Necessite donc de passer la taille des
 * images weight x height */
typedef float (*image_distance)(const uint8_t* imga,
				const uint8_t* imgb,
				uint32_t width, uint32_t height);

/* une distance euclidienne est fournie entre deux images */
float image_euclidean_distance(const uint8_t* imga, const uint8_t* imgb,
			       uint32_t width, uint32_t height);

/* d'autres distances sont possibles */

#endif
