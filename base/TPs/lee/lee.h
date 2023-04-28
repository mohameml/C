#ifndef _LEE_H_
#define _LEE_H_

#include <stdbool.h>
#include "maze.h"

/* maze must be initialized (eg by create_maze_from_file),
   values are among WALL, START, END, or EMPTY.
   Use Lee's algorithm to fill the maze, ie replace some
   or all EMPTY values with the number of steps to
   reach the corresponding position.
   Return true if a solution (path from START to END) exists,
   false otherwise.
*/
bool solve_maze(struct maze *maze);

/* maze must be filled by solve_maze, and a solution
   must exist (ie there must exist a path between D and A).
   Set values of cells on one of the best paths
   between D and A to BEST */
void build_path(struct maze *maze);

#endif
