#ifndef _GOL_TORUS_H
#define _GOL_TORUS_H

int **updateMapTorus(int **map, int r, int c, int nbh);
int aliveNeighboursTorus(int **map, int x, int y, int r, int c, int nbh);

#endif