#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"
#include "image_io.h"
#include <sys/stat.h>

int aliveNeighbours(int **map, int x, int y, int r, int c)
{
    int a = 0;
    for (int i = y - 1; i < y + 2; i++)
    {
        for (int j = x - 1; j < x + 2; j++)
        {
            if (i >= 0 && i < r && y >= 0 && y < c && !(i == y && j == x))
            {
                if (map[i][j] == 1)
                    a++;
            }
        }
    }
    return a;
}

//0 - dead
//1 - alive

int **updateMap(int **map, int r, int c)
{
    int **newmap = copyMap(map, r, c);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int alive = aliveNeighbours(map, j, i, r, c);
            if (map[i][j] == 1 && !(alive == 2 || alive == 3))
                newmap[i][j] = 0;
            else if (map[i][j] == 0 && alive == 3)
                newmap[i][j] = 1;
        }
    }
    freeMap(map, r);
    return newmap;
}

int main(int argc, char **argv)
{

    int iterations = atoi(argv[1]);
    Map *map = readMap(argv[2]);
    char path[30];
    char pathGif[30];

    char *folder = malloc(strlen(argv[2]) - 4);
    strncpy(folder, argv[2], strlen(argv[2]) - 4);
    mkdir(folder, 0700);

    sprintf(pathGif, "./%s/map.gif", folder);
    initGif(pathGif, map->r, map->c);
    for (int i = 0; i < iterations; i++)
    {
        sprintf(path, "./%s/iter_%d", folder, i);
        saveMap(map, path, i);
        saveToBmp(path, map->data, map->r, map->c);
        addFrameGif(map->data);

        map->data = updateMap(map->data, map->r, map->c);
    }

    saveToGif();
}