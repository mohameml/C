# Enoncé

L'objectif de cet exercice est d'apprendre à se déplacer rapidement
dans un fichier pour lire du contenu positionné à des offsets
spécifiques.

L'objectif est d'afficher sur la sortie standard les caractères du
fichier `daddy.txt` dont les positions sont répertoriées dans le
tableau positions déclaré dans la fonction `main`.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/daddy-cool/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* jetez un oeil au manuel des fonctions `fseek` et `fgetc`

</details>

# Compétences

* Ouverture de fichier
* Fermeture de fichier
* Lecture caractère par caractère
* Déplacement au sein d'un fichier

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: daddy-cool

.PHONY: clean
clean:
	rm -f *~ *.o daddy-cool


```

#### Corrigé du fichier daddy-cool.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* Le nombre de caractères à afficher. */
#define NB_POS 455

int main(void)
{
    /* Tableau effectuant la correspondance entre la position du
     * caractère dans le message de sortie et sa position dans le
     * fichier daddy.txt. Par exemple, positions[0] == 9, ce qui veut
     * dire que le premier caractère du message de sortie est stocké
     * en position 9 dans le fichier.
     *
     * Oui, c'est moche.
     */
    long positions[NB_POS] = { 9,42,44,52,110,114,130,157,179,225,229,247,248,
	283,288,293,305,320,442,443,482,536,580,640,649,656,661,762,840,858,867,
	883,896,908,913,921,999,1011,1016,1042,1097,1117,1120,1131,1138,1193,1215,
	1233,1250,1251,1261,1278,1376,1400,1431,1458,1459,1466,1487,1504,1513,1558,
	1584,1637,1751,1812,1823,1832,1870,1900,1901,2043,2048,2060,2075,2077,2090,
	2105,2269,2276,2285,2350,2351,2367,2371,2381,2437,2446,2449,2467,2473,2496,
	2500,2537,2544,2622,2647,2667,2699,2710,2752,2753,2758,2791,2801,2829,2886,
	2898,2906,2912,2931,2936,2969,2986,2994,3000,3022,3027,3091,3095,3106,3118,
	3120,3161,3175,3184,3222,3236,3265,3303,3305,3310,3316,3319,3352,3358,3364,
	3369,3406,3409,3427,3467,3476,3500,3546,3586,3601,3604,3608,3618,3626,3637,
	3662,3671,3697,3699,3705,3720,3731,3742,3745,3749,3770,3784,3809,3954,3957,
	3983,4050,4094,4100,4121,4138,4161,4175,4186,4205,4243,4263,4282,4307,4310,
	4358,4388,4432,4446,4502,4549,4558,4560,4577,4721,4741,4745,4762,4840,4891,
	4935,4970,5044,5138,5159,5212,5256,5278,5288,5299,5342,5418,5463,5474,5495,
	5507,5629,5645,5668,5696,5697,5704,5714,5725,5760,5761,5796,5873,5883,5936,
	5965,5977,5978,5989,5994,6055,6056,6057,6076,6109,6118,6128,6138,6144,6147,
	6205,6218,6227,6228,6231,6237,6245,6294,6346,6349,6365,6370,6372,6395,6447,
	6474,6477,6494,6514,6522,6561,6585,6593,6599,6705,6706,6712,6743,6782,6805,
	6825,6857,6933,6999,7035,7038,7048,7076,7124,7140,7154,7159,7188,7205,7268,
	7276,7290,7364,7382,7401,7460,7488,7495,7505,7516,7526,7533,7553,7670,7717,
	7728,7729,7940,7942,7952,7962,7979,8004,8015,8017,8021,8041,8073,8074,8090,
	8208,8222,8254,8317,8357,8362,8391,8466,8469,8530,8574,8581,8645,8657,8670,
	8709,8730,8787,8788,8805,8815,8856,8875,8889,8892,8937,9007,9049,9055,9111,
	9130,9140,9157,9177,9188,9218,9222,9230,9239,9249,9311,9320,9324,9368,9399,
	9447,9484,9494,9501,9531,9560,9572,9623,9710,9745,9803,9836,9848,9851,9856,
	9858,9863,9909,9918,9941,9994,10028,10038,10039,10082,10091,10092,10098,
	10104,10110,10126,10145,10193,10234,10251,10304,10310,10356,10370,10381,
	10519,10522,10602,10627,10641,10645,10670,10732,10734,10753,10758,10802,
	10813,10907,10928,10986,11006,11007,11026,11027,11070,11081,11151,11183,
	11208,11211,11266,11304,11364,11425,11430,11436,11470,11511,11520,11544,
	11547,11561,11587,11605,11676,11688,11716,11729,11774,11796,11798,11889,
	11901,11957,11975,11978,11979 };

    /* On ouvre le fichier en lecture. */
    FILE *f = fopen("daddy.txt", "r");

    /* Pour tous les caractères du message de sortie... */
    for (uint32_t i = 0; i < NB_POS; i++) {
	/* ... on se déplace dans le fichier à la position indiquée... */
	fseek(f, positions[i], SEEK_SET);
	/* ... puis on affiche le caractère stocké à cette position. */
	printf("%c", fgetc(f));
    }
    /* Pour contenter la brigade du style. */
    printf("\n");

    /* Si on oublie de fermer le fichier, notre programme fuit!
     * (essayez de lancer valgrind sans cette ligne, pour voir). */
    fclose(f);

    return EXIT_SUCCESS;
}

```


</details>
