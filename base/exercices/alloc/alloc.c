#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t** creer_matrice(uint32_t rang)
{
    uint32_t** mat = calloc(rang, sizeof(uint32_t*));
    for (uint32_t i = 0; i < rang; i++) {
        mat[i] = calloc(rang, sizeof(uint32_t));
    }

    return mat;
}

static uint32_t** creer_matrice_a_plat(uint32_t rang)
{
    size_t len = rang * sizeof(uint32_t*) + rang * rang * sizeof(uint32_t);
    void* area = calloc(len, sizeof(uint8_t));

    uint32_t** mat = (uint32_t**)area;
    for (uint32_t i = 0; i < rang; i++) {
        mat[i] = area + rang * sizeof(uint32_t*) + i * sizeof(uint32_t);
    }

    return mat;
}

static void initialiser_matrice(uint32_t** mat, uint32_t rang)
{
    for (uint32_t i = 0; i < rang; i++) {
        for (uint32_t j = 0; j < rang; j++) {
            printf("%u %u\n", i, j);
            mat[i][j] = i * rang + j;
        }
    }
}

static void afficher_matrice(uint32_t** mat, uint32_t rang)
{
    for (uint32_t i = 0; i < rang; i++) {
        for (uint32_t j = 0; j < rang; j++) {
            printf("%02u%s", mat[i][j], j == rang - 1 ? "\n" : " ");
        }
    }
    printf("\n");
}

static void liberer_matrice(uint32_t** mat, uint32_t rang)
{
    for (uint32_t i = 0; i < rang; i++) {
        free(mat[i]);
    }

    free(mat);
}

static void liberer_matrice_a_plat(uint32_t** mat)
{
    free(mat);
}

int main(void)
{
    const uint32_t rang = 8;

    uint32_t** mat = creer_matrice(rang);
    initialiser_matrice(mat, rang);
    afficher_matrice(mat, rang);
    liberer_matrice(mat, rang);

    uint32_t** matapla = creer_matrice_a_plat(rang);
    initialiser_matrice(matapla, rang);
    afficher_matrice(matapla, rang);
    liberer_matrice_a_plat(matapla);

    return EXIT_SUCCESS;
}
