#include <stdlib.h>
#include <stdio.h>

#include "array.h"
#include "image.h"
#include "kdtree.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
	printf("Usage: %s test_file.pgm\n", argv[0]);
	return EXIT_FAILURE;
    }

    /* charge la base MNIST de 60'000 examples d'apprentissage, les remettre a
     * l'echelle 10x10 et charger les etiquettes d'identite correspondantes */
    /* NOTE: PREFERER LIER LES FICHIERS DE DONNEES SUR LE COMPTE
     * ENSEIGNNT AVEC ln -s pour ne pas prendre trop de place sur
     * les disques*/
    struct array *train  = load_image_array("data/train-images-idx3-ubyte.gz");
    struct array *strain = image_downscale(train, 10, 10);
    struct array *labels = load_label_array("data/train-labels-idx1-ubyte.gz");

    /* charger l'image a reconnaitre */
    struct array *test   = load_pgm_image(argv[1]);
    struct array  stest  = image_downscale(test, get_width(strain),
					   get_height(strain));

    /* construire le kd-arbre */
    struct kdtree *tree = create_kdtree(strain, 10);
    printf("Created kd-tree for %d training examples.\n", get_size(strain));

    /* A FAIRE */

    return EXIT_SUCCESS;
}
