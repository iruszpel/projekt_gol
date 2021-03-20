#include "gol.h"
#include "../map.h"
#define TMOD(a,b) ((((a)%(b))+(b))%(b)) //Torusowe modulo

int aliveNeighboursTorus(int **map, int x, int y, int r, int c)
{
    /*
    Plansza jest torusem i idąc ciągle w jednym kierunku 
    wrócimy do tego punktu z którego wyszliśmy
    */
    int a = 0;
    int i2 = 0;
    int j2 = 0;
    for (int i = TMOD((y - 1), r); i2 < 3; i=TMOD((i+1), r),i2++)
    {
        
        for (int j = TMOD((x - 1), c),j2=0; j2 < 3; j=TMOD((j+1), c),j2++)
        {   
            if (!(i == y && j == x))
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

int **updateMapTorus(int **map, int r, int c)
{
    int **newmap = copyMap(map, r, c);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int alive = aliveNeighboursTorus(map, j, i, r, c);
            if (map[i][j] == 1 && !(alive == 2 || alive == 3))
                newmap[i][j] = 0;
            else if (map[i][j] == 0 && alive == 3)
                newmap[i][j] = 1;
        }
    }
    freeMap(map, r);
    return newmap;
}