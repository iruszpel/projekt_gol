#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
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
        memcpy(mat[i], oldMap[i], sizeof(**mat) * c);
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
    Map *map = malloc(sizeof *map);
    FILE *in = fopen(file, "r");

    fscanf(in, "%d %d", &map->r, &map->c);
    map->data = allocateMap(map->r, map->c);

    for (int i = 0; i < map->r; i++)
    {
        for (int j = 0; j < map->c; j++)
        {
            fscanf(in, "%d", &map->data[i][j]);
        }
    }

    return map;
}

void saveMap(Map *map, char *file, int iter)
{
    char *folder = malloc(strlen(file) - 4);
    strncpy(folder, file, strlen(file) - 4);
    mkdir(folder, 0700);

    int new_len = strlen(file) + 10;
    char *filename = malloc(new_len);

    snprintf(filename, new_len, "./%s/iter_%d.txt", folder, iter);

    FILE *out = fopen(filename, "w+");
    fprintf(out, "%d %d\n", map->r, map->c);

    for (int i = 0; i < map->r; i++)
    {
        for (int j = 0; j < map->c; j++)
        {
            fprintf(out, "%d ", map->data[i][j]);
        }
        fprintf(out, "\n");
    }
}
