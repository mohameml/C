#ifndef _MAZEIO_H_
#define _MAZEIO_H_

#include "maze.h"

/* Read maze definition from file named infile.
   Allocate and initialize a struct maze with
   values in WALL, START, END, or EMPTY.
   Print error message to stderr and return NULL
   if an error occurred (eg if infile does not
   correspond to a valid maze).
*/
struct maze *create_maze_from_file(char *infile);

/* Print the maze to stdout.
   If values==true print the number of steps to reach
   each position (useful for debugging); otherwise
   just print the WALL, START, END and BEST positions,
   using appropriate characters (eg # for WALL and
   . for BEST).
*/
void print_maze(struct maze *maze, bool values);


#endif
