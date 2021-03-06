#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "map.h"
#include "automata/gol.h"
#include "automata/gol_torus.h"
#include "image_io.h"

void syntax(char *f)
{
    printf("%s -<flags> \n", f);
    printf("\t-f <filename> - file with data (*required)\n");
    printf("\t-i <number> - number of iterations (*required)\n");
    printf("\t-s <number> -  which iteration to save\n");
    printf("\t-g - creates GIF animation\n");
    printf("\t-t <number> - type of automaton (default: 1 )\n");
    printf("\t-l - list available automata\n");
}

void list_automata()
{
    printf("1. Conway's Game of Life (Moore neighborhood, 2d map) \n");
    printf("2. Conway's Game of Life (Von Neumann neighborhood, 2d map) \n");
    printf("3. Conway's Game of Life (Moore neighborhood, torus map) \n");
    printf("4. Conway's Game of Life (Von Neumann neighborhood, torus map) \n");
}

int **updateMapFunction(int type, int **map, int r, int c)
{
    switch (type)
    {
    case 1:
        return updateMap(map, r, c, 0);
    case 2:
        return updateMap(map, r, c, 0);
    case 3:
        return updateMapTorus(map, r, c, 1);
    case 4:
        return updateMapTorus(map, r, c, 1);
        
    }
}

int main(int argc, char **argv)
{
    int iterations = 0;
    int file_check = 0;
    int gif = 0;
    int ITS = 0;  // iteration to save
    int type = 1; //default type of automaton
    char path[30];
    char pathGif[30];
    Map *map;
    char *folder;
    int neighborhood = 0; // 0 - Moore, 1 - von Neumann
    int opt;
    while ((opt = getopt(argc, argv, "f:i:s:t:lg")) != -1)
    {
        switch (opt)
        {
        case 'f': //filename
            file_check = 1;
            map = readMap(optarg);
            folder = calloc(strlen(optarg) - 3, sizeof(char));
            strncpy(folder, optarg, strlen(optarg) - 4);
            mkdir(folder, 0700);
            break;

        case 'i': // how many iterations
            iterations = atoi(optarg);
            break;
        case 's': // which iteration to save
            ITS = atoi(optarg);
            break;
        case 'g': // creates GIF file
            gif = 1;
            break;
        case 't': // type of automaton
            type = atoi(optarg);
            break;
        case 'l': // lists available automata
            list_automata();
            return 0;
            break;

        default:
            fprintf(stderr, "%s: unknown option %c - ignored\n", argv[0], opt);
            break;
        }
    }

    if (iterations == 0 || file_check == 0)
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

        if (i == ITS)
            saveMap(map, path, i);

        if (gif == 1)
            addFrameGif(map->data);

        map->data = updateMapFunction(type, map->data, map->r, map->c);
    }

    if (gif == 1)
        saveToGif();

    freeMap(map->data, map->r);
    free(map);
    free(folder);

    return 0;
}