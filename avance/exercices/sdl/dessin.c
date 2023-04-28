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
