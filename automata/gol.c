#include "gol.h"
#include "../map.h"

int aliveNeighbours(int **map, int x, int y, int r, int c, int nbh)
{
    //Na brzegach wszystko jest martwe
    int a = 0;
    int check;
    for (int i = y - 1; i < y + 2; i++)
    {
        for (int j = x - 1; j < x + 2; j++)
        {
            check = 1;
            if(nbh == 1) // von Neumann
                check = (i == y || j == x);

            if (i >= 0 && j>= 0 && i < r && j < c && !(i == y && j == x) && check)
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

int **updateMap(int **map, int r, int c, int nbh)
{
    int **newmap = copyMap(map, r, c);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int alive = aliveNeighbours(map, j, i, r, c, nbh);
            if (map[i][j] == 1 && !(alive == 2 || alive == 3))
                newmap[i][j] = 0;
            else if (map[i][j] == 0 && alive == 3)
                newmap[i][j] = 1;
        }
    }
    freeMap(map, r);
    return newmap;
}


