#ifndef IDCT
#define  IDCT
#include <stdio.h>
#include <stdint.h>
#include <math.h>


#define PI 3.14159
/* MODULE : IDCT */

/*----------------------  IDCT ------------------------*/
float c(uint8_t  val);
void idct( int mat_entree[8][8], int matrice_sortie[8][8]);

/*----------------------- IDCT_RAPIDE -------------------------------*/

void Rotation(float x, float y, float k, uint8_t n, float *z, float *t);
float* loeffler(float* stage_4, float res[8]);
void idct_rapide( int inp[8][8], int out[8][8]);




#endif 