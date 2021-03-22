#ifndef _GOL_H
#define _GOL_H

int **updateMap(int **map, int r, int c, int nbh);
int aliveNeighbours(int **map, int x, int y, int r, int c, int nbh);

#endif