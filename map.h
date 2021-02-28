#ifndef _MAP_H
#define _MAP_H

typedef struct {
				int r,c;
				int **data;
} Map;

int **allocateMap(int r, int c); /*Allocates memory for a map*/
int **copyMap(int **oldMap, int r, int c);
void freeMap(int **map, int r);
Map *readMap(char *file); /*Reads map from file and returns Map struct */
void saveMap(Map *map, char *file, int iter); /*Writes map to file */

#endif