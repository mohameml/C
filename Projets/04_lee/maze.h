#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdint.h>


struct maze {
    uint32_t w; // width
    uint32_t h; // height
    uint32_t dx; // x and y coords of D (0-indexed)
    uint32_t dy;
    uint32_t ax; // x and y coords of A
    uint32_t ay;
    int32_t *m; /* array to store a value at each maze position.
		   value of (x,y) is stored at m[x+w*y]  */
    /* if you are more comfortable with 2D arrays, you can replace the
       1D array m with an array of w pointers to arrays of h values:
       int32_t **m;
       value of (x,y) is then stored at m[x][y] */
};

/* value at each position is the number of steps to
   reach this position, or one of: */
#define WALL -1
#define START -2
#define END -3
#define EMPTY -4
#define BEST -5

/* allocate memory for maze of size w*h.
   Set w, h and m, other fields and m values are not meaningful.
   Return NULL and print message to stderr if error.
*/
struct maze *alloc_maze(uint32_t w, uint32_t h);

/* free all memory in maze */
void free_maze(struct maze *maze);

#endif
