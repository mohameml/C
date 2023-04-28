#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stdint.h>

/* structure privee de tableau d'images */
struct array;

/* creation d'un tableau de "size" images, toute de taille width x
 * height, chaque pixel faisant 1 octet */
struct array* create_array(uint32_t size, uint32_t width, uint32_t height);

/* changer la taille du tableau d'images */
void resize_array(struct array* array, uint32_t new_size);

/* liberer la memoire du tableau d'images */
void free_array(struct array* array);

/* accesseur/modifieur: renvoie un pointeur sur l'image no "elem",
 * c'est a dire un tableau de pixels adressables de la maniere
 * suivante ((uint8_t*)get_elem(a, elem))[y*get_width + x] */
/* precondition: elem est present dans a */
void* get_elem(const struct array* a, uint32_t elem);

/* nombre d'images dans le tableau a */
uint32_t get_size(const struct array* a);

/* largeur des images du tableau */
uint32_t get_width(const struct array* a);

/* hauteur des images du tableau */
uint32_t get_height(const struct array* a);

/* indice "elem" d'une image du tableau a, a partir de son pointeur
 * data (obtenu avec get_elem). */
/* precondition: elem est present dans a */
uint32_t get_index(const struct array* a, const void* data);

#endif
