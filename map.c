#include <stdlib.h>
#include <string.h>
#include "map.h"

int **allocateMap(int r, int c)
{

    int **mat = malloc(sizeof(*mat) * r);

    for (int i = 0; i < r; i++)
    {
        mat[i] = calloc(c, sizeof(**mat));
    }

    return mat;
}
int **copyMap(int **oldMap, int r, int c)
{
    int **mat = malloc(sizeof(*mat) * r);

    for (int i = 0; i < r; i++)
    {
        mat[i] = calloc(c, sizeof(**mat));
        memcpy(mat[i],oldMap[i],sizeof(**mat)*c);
    }
    return mat;
}

void freeMap(int **map, int r)
{

    for (int i = 0; i < r; i++)
    {
        free(map[i]);
    }
    free(map);
}

Map *readMap(char *file)
{
    //Do napisania
}

void saveMap(Map *map, char *file)
{
    //Do napisania
}
