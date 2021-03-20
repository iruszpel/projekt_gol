#include <stdlib.h>
#include <stdio.h>
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
    fclose(in);
    return map;
}

void saveMap(Map *map, char *path, int iter)
{
    char * new_path = malloc(strlen(path) + 5);
	strcpy(new_path, path);
    strcat(new_path, ".txt");

    FILE *out = fopen(new_path, "w+");
    fprintf(out, "%d %d\n", map->r, map->c);

    for (int i = 0; i < map->r; i++)
    {
        for (int j = 0; j < map->c; j++)
        {
            fprintf(out, "%d ", map->data[i][j]);
        }
        fprintf(out, "\n");
    }
    
    free(new_path);
    fclose(out);
}
