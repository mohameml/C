#ifndef _DESSIN_H_
#define _DESSIN_H_

#include <SDL.h>

extern void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
extern void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);
extern void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);

#endif /* _DESSIN_H_ */
