#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
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
void syntax(char *f)
{
    printf("%s -<flags> \n", f);
    printf("\t-f <filename> (*required)\n");
    printf("\t-i <number> - number of iterations (*required)\n");
    printf("\t-s <number> -  which iteration to save\n");
    printf("\t-g - creates GIF animation\n");
}
int main(int argc, char **argv)
{
    int opt;
    int iterations = 0;
    int f_check = 0;
    int gif = 0;
    int its;
    char path[30];
    char pathGif[30];
    Map *map;
    char *folder;

    while ((opt = getopt(argc, argv, "f:i:s:g")) != -1)
    {
        switch (opt)
        {
        case 'f': //filename
            f_check = 1;
            map = readMap(optarg);
            folder = malloc(strlen(optarg) - 4);
            strncpy(folder, optarg, strlen(optarg) - 4);
            mkdir(folder, 0700);
            break;
        case 'i': // how many iterations
            iterations = atoi(optarg);
            break;
        case 's': // which iteration to save
            its = atoi(optarg);
            break;
        case 'g': // creates GIF file
            gif = 1;
            break;
        default:
            fprintf(stderr, "%s: unknown option %c - ignored\n", argv[0], opt);
            break;
        }
    }
    if (iterations == 0 || f_check == 0)
    {
        syntax(argv[0]);
        return -1;
    }
    if (gif == 1)
    {
        sprintf(pathGif, "./%s/%s.gif", folder, folder);
        initGif(pathGif, map->r, map->c);
    }
    for (int i = 0; i < iterations; i++)
    {
        sprintf(path, "./%s/iter_%d", folder, i);
        saveToBmp(path, map->data, map->r, map->c);

        if (i == its)
            saveMap(map, path, i);

        if (gif == 1)
            addFrameGif(map->data);

        map->data = updateMap(map->data, map->r, map->c);
    }
    if (gif == 1)
        saveToGif();
}