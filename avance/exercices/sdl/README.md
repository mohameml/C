# Enoncé

Cet exercice traite de la compilation d'un programme qui utilise une
bibliothèque externe. Le but du jeu est d'écrire le `Makefile` qui
permet de générer un exécutable à partir du fichier de test `main.c`
et du module dessin, implémenté dans `dessin.c`, le tout sans toucher
aux fichiers source fournis.

Pour générer l'exécutable `main`, vous aurez besoin des fichiers
objets `main.o` et `dessin.o`, et de lier ces `.o` avec les
bibliothèques `SDL` et `m` (pour les fonctions mathématiques).

Pour générer `main.o` et `dessin.o`, vous aurez besoin de spécifier
l'emplacement de l'en-tête `SDL.h` sur votre système. A l'ensimag, les
fichiers en-tête de la bibliothèque SDL sont installés dans le
répertoire `/usr/include/SDL`.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/sdl/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* option de compilation pour spécifier l'emplacement d'un .h: `-I`
  (grand i)
* option de l'éditeur de liens pour spécifier l'emplacement d'une
  bibliothèque: `-l` (petit l)
* lier l'exécutable à la bibliothèque toto: `-ltoto` à l'édition de
  liens

</details>

# Compétences

* Option fichier objet
* Option fichier exécutable
* Edition de liens
* Lien avec librairies statiques personnelles
* Lien avec librairies dynamiques personnelles

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
# On rajoute aux options de compilation l'emplacement de SDL.h.
CFLAGS=-Wall -Wextra -g -std=c99 -I/usr/include/SDL
# On rajoute aux options de l'éditeur de liens les bibliothèques SDL et m.
LDFLAGS=-lSDL -lm

all: main

.PHONY: enonce
enonce:
	@echo "Commencez par compléter le Makefile de cet exercice."

# On indique au compilateur que l'exécutable est construit à partir des fichiers objet main.o ET dessin.o
main: main.o dessin.o

# et que si quelqu'un modifie dessin.h, il faut regénérer main.o et dessin.o
main.o: main.c dessin.h

dessin.o: dessin.c dessin.h

# et... c'est tout! Les règles implicites de make feront le reste!
# En pratique, on aurait pu écrire ça:

# main.o: main.c dessin.h
# 	$(CC) $(CFLAGS) -c $<

# dessin.o: dessin.c dessin.h
# 	$(CC) $(CFLAGS) -c $<

# main: main.o dessin.o
# 	$(CC) $^ -o $@ $(LDFLAGS)

# mais "make" fait ça tout seul!

.PHONY: clean
clean:
	rm -rf *.o *~ main

```

#### Corrigé du fichier dessin.c

```c
#include <math.h>
#include <SDL.h>

#include "dessin.h"

/*
 * This is a 32-bit pixel function created with help from this
 * website: http://www.libsdl.org/intro.en/usingvideo.html
 *
 * You will need to make changes if you want it to work with
 * 8-, 16- or 24-bit surfaces.  Consult the above website for
 * more information.
 */
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}

/*
 * This is an implementation of the Midpoint Circle Algorithm
 * found on Wikipedia at the following link:
 *
 *   http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
 *
 * The algorithm elegantly draws a circle quickly, using a
 * set_pixel function for clarity.
 */
void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{
    // if the first pixel in the screen is represented by (0,0) (which is in sdl)
    // remember that the beginning of the circle is not in the middle of the pixel
    // but to the left-top from it:

    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;

    while (x >= y)
    {
	set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
	set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);

	if (x != 0)
	{
	    set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
	    set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
	}

	if (y != 0)
	{
	    set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
	    set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
	}

	if (x != 0 && y != 0)
	{
	    set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
	    set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
	}

	error += y;
	++y;
	error += y;

	if (error >= 0)
	{
	    --x;
	    error -= x;
	    error -= x;
	}
    }
}

/*
 * SDL_Surface 32-bit circle-fill algorithm without using trig
 *
 * While I humbly call this "Celdecea's Method", odds are that the
 * procedure has already been documented somewhere long ago.  All of
 * the circle-fill examples I came across utilized trig functions or
 * scanning neighbor pixels.  This algorithm identifies the width of
 * a semi-circle at each pixel height and draws a scan-line covering
 * that width.
 *
 * The code is not optimized but very fast, owing to the fact that it
 * alters pixels in the provided surface directly rather than through
 * function calls.
 *
 * WARNING:  This function does not lock surfaces before altering, so
 * use SDL_LockSurface in any release situation.
 */
void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{
    // Note that there is more to altering the bitrate of this
    // method than just changing this value.  See how pixels are
    // altered at the following web page for tips:
    //   http://www.libsdl.org/intro.en/usingvideo.html
    static const int BPP = 4;

    double r = (double)radius;

    for (double dy = 1; dy <= r; dy += 1.0)
    {
	// This loop is unrolled a bit, only iterating through half of the
	// height of the circle.  The result is used to draw a scan line and
	// its mirror image below it.

	// The following formula has been simplified from our original.  We
	// are using half of the width of the circle because we are provided
	// with a center and we need left/right coordinates.

	double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
	int x = cx - dx;

	// Grab a pointer to the left-most pixel for each half of the circle
	Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
	Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;

	for (; x <= cx + dx; x++)
	{
	    *(Uint32 *)target_pixel_a = pixel;
	    *(Uint32 *)target_pixel_b = pixel;
	    target_pixel_a += BPP;
	    target_pixel_b += BPP;
	}
    }
}

```

#### Corrigé du fichier dessin.h

```c
#ifndef _DESSIN_H_
#define _DESSIN_H_

#include <SDL.h>

extern void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
extern void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);
extern void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);

#endif /* _DESSIN_H_ */

```

#### Corrigé du fichier main.c

```c
#include <math.h>
#include <stdbool.h>
#include <SDL.h>

#include "dessin.h"

int main(void)
{
    static const int width = 640;
    static const int height = 480;
    static const int max_radius = 64;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	return 1;
    }

    atexit(SDL_Quit);

    SDL_Surface *screen = SDL_SetVideoMode(width, height, 0, SDL_DOUBLEBUF);

    if (screen == NULL)
	return 2;

    bool loop = true;
    while(loop) {
	int x = rand() % (width - 4) + 2;
	int y = rand() % (height - 4) + 2;
	int r = rand() % (max_radius - 10) + 10;
	int c = ((rand() % 0xff) << 16) +
	    ((rand() % 0xff) << 8) +
	    (rand() % 0xff);

	if (r >= 4) {
	    if (x < r + 2) {
		x = r + 2;
	    } else if (x > width - r - 2) {
		x = width - r - 2;
	    }

	    if (y < r + 2) {
		y = r + 2;
	    } else if (y > height - r - 2) {
		y = height - r - 2;
	    }
	}

	SDL_LockSurface(screen);

	fill_circle(screen, x, y, r, 0xff000000 + c);
	draw_circle(screen, x, y, r, 0xffffffff);

	SDL_FreeSurface(screen);

	SDL_Flip(screen);
	/* verifie si la fenetre a ete fermee */
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
	    if(event.type == SDL_QUIT)
		loop = false;
	}
    }

    SDL_Quit();

    return 0;
}

```


</details>
