#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>


#define PI 3.14159


float c(uint8_t  val)
{
    if( val==0)
    {
        return 1/sqrtf(2);
    }
    
    
    return 1;
    
    
}


void idct( int mat_entree[8][8], int mat_sortie[8][8])
{
    for(uint8_t  x=0;x<8;x++)
    {
        for(uint8_t  y=0;y<8;y++)
        {   
            float sum=0;
            
            for(uint8_t  i=0;i<8;i++)
            {
                for(uint8_t  j=0;j<8;j++)
                {
                    sum += c(i) * c(j) * (mat_entree[i][j]) * cosf( (float)((2*x+1) * i * PI)/16 ) * cosf((float)((2*y+1) * j * PI)/16) ;
                }
            }
            
            
            mat_sortie[x][y]= sum/4 + (float)128 < 0 ? 0 : sum/4 + (float)128 > 255 ? 255 :  sum/4 + (float)128; 

             

        }
    }

    


}


// on definit une rotation inverse qui prend en argument deux entrées x et y et *z , *t pour savoir au mettre le resultat de rotation :
void Rotation(float x, float y, float k, uint8_t n, float *z, float *t){
	*z = ( x*cos((n*PI)/16) - y*sin((n*PI)/16) )/k;
	*t = ( y*cos((n*PI)/16) + x*sin((n*PI)/16) )/k;
}

// on implemente loeffler qui prend en argument deux tableaux un d entrée et un de sorti

float* loeffler(float* stage_4, float res[8]){
    // on initialise 4 tableaux pour les 4 stages:
    float stage_3[8];
    float stage_2[8];
    float stage_1[8];
    float stage_0[8];

    // on multiplie par sqrt(n) ici n = 8: 
    for(uint8_t i=0; i<8 ;i++){
        stage_4[i] *= sqrt(8);
    }

    // 1er etape:
    stage_3[0] = stage_4[0];
    stage_3[1] = (stage_4[1] + stage_4[7])/2;
    stage_3[2] = stage_4[2];
    stage_3[3] = stage_4[3]/sqrt(2);
    stage_3[4] = stage_4[4];
    stage_3[5] = stage_4[5]/sqrt(2);
    stage_3[6] = stage_4[6];
    stage_3[7] = (stage_4[1] - stage_4[7])/2;

    // 2 eme etape:
    stage_2[0] = (stage_3[0] + stage_3[4])/2;
    stage_2[4] = (stage_3[0] - stage_3[4])/2;
    Rotation(stage_3[2],stage_3[6],sqrt(2),6,&stage_2[2],&stage_2[6]);
    stage_2[7] = (stage_3[7] + stage_3[5])/2;
    stage_2[5] = (stage_3[7] - stage_3[5])/2; 
    stage_2[1] = (stage_3[1] + stage_3[3])/2;
    stage_2[3] = (stage_3[1] - stage_3[3])/2;

    // 3 eme etape:
    stage_1[0] = (stage_2[0] + stage_2[6])/2;
    stage_1[6] = (stage_2[0] - stage_2[6])/2;
    stage_1[2] = (stage_2[4] - stage_2[2])/2;
    stage_1[4] = (stage_2[4] + stage_2[2])/2;
    Rotation(stage_2[7],stage_2[1],1,3,&stage_1[7],&stage_1[1]);
    Rotation(stage_2[3],stage_2[5],1,1,&stage_1[3],&stage_1[5]);

    // 4 eme etape: 
    stage_0[0] = (stage_1[0] + stage_1[1])/2;
    stage_0[1] = (stage_1[0] - stage_1[1])/2;
    stage_0[4] = (stage_1[4] + stage_1[5])/2;
    stage_0[5] = (stage_1[4] - stage_1[5])/2;
    stage_0[2] = (stage_1[2] + stage_1[3])/2;
    stage_0[3] = (stage_1[2] - stage_1[3])/2;
    stage_0[6] = (stage_1[6] + stage_1[7])/2;
    stage_0[7] = (stage_1[6] - stage_1[7])/2;

    // 5 eme etape: stockage du resultat
    res[0] = stage_0[0];
    res[1] = stage_0[4];
    res[2] = stage_0[2];
    res[3] = stage_0[6];
    res[4] = stage_0[7];
    res[5] = stage_0[3];
    res[6] = stage_0[5];
    res[7] = stage_0[1];

    return res;
}

void idct_rapide( int inp[8][8], int out[8][8]){
    float res[8];
    
    // on applique loeffler sur les lignes de la matrice d'entré:
    for(int i = 0; i < 8; i++) {
        float stage_4[8];
        for(int j = 0; j < 8; j++) {
            stage_4[j] = inp[i][j];
        }
        loeffler(stage_4, res);
        // mettre le resultat dans out 
        for(int j = 0; j < 8; j++) {
            out[i][j] = round(res[j]);
        }
    }

    // appliquer loeffler sur les colonnes de out :
    for (int j = 0; j < 8; j++) {
        float stage_4[8];
        for (int i = 0; i < 8; i++) {
            stage_4[i] = out[i][j];
        }
        loeffler(stage_4, res);

        // stockage du resultat final 
        for (int i = 0; i < 8; i++) {
            res[i] += 128;
            if(res[i] > 255){
                out[i][j] = 255;
            }
            else if (res[i] < 0){
                out[i][j] = 0;
            }
            else{
                out[i][j] = round(res[i]);
            }
        }
    }
}


