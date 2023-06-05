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
