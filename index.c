#include <stdlib.h>
#include <stdio.h>

#include "map.h"
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
}*/
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
    
    for (int i = 0; i < iterations; i++)
    {
        //printTest(map->data, map->r, map->c);
        saveMap(map, argv[2], i);
        map->data = updateMap(map->data, map->r, map->c);
    }
}