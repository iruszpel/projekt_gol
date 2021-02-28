#include <stdlib.h>
#include <stdio.h>

#include "map.h"
#include "image_io.h"
/*
void printTest(int **map, int r, int c)
{
    int i, j;
    printf("[ \n");
    for (i = 0; i < r; i++)
    {
        printf("  ");
        for (j = 0; j < c; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("; \n");
    }
    printf("]\n");
}
Do wyrzucenia później
*/
int aliveNeighbours(int **map, int x, int y, int r, int c)
{
    int a = 0;
    for (int i = y - 1; i < y + 2; i++)
    {
        for (int j = x - 1; j < x + 2; j++)
        {
            if (i >= 0 && i < r && y >= 0 && y < c && !(i == y && j == x)){
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
    //int iterations = 3;
    int iterations = atoi(argv[1]);
    Map *map = readMap(argv[2]);
    /*Map *map = malloc(sizeof *map);
    map->c = 3;
    map->r = 3;
    map->data = allocateMap(map->r, map->c);

    map->data[0][0] = 0;
    map->data[0][1] = 1;
    map->data[0][2] = 0;
    map->data[1][0] = 1;
    map->data[1][1] = 1;
    map->data[1][2] = 1;
    map->data[2][0] = 0;
    map->data[2][1] = 0;
    map->data[2][2] = 0;
*/
    for (int i = 0; i < iterations; i++)
    {
        char *filename[20];
        sprintf (filename, "iter_%d.bmp", i);
        saveToBmp(filename,map->data);
        map->data = updateMap(map->data, map->r, map->c);
    }
}