#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "map.h"
#include "game.h"
#include "image_io.h"

void syntax(char *f)
{
    printf("%s -<flags> \n", f);
    printf("\t-f <filename> - file with data (*required)\n");
    printf("\t-i <number> - number of iterations (*required)\n");
    printf("\t-s <number> -  which iteration to save\n");
    printf("\t-g - creates GIF animation\n");
}

int main(int argc, char **argv)
{
    int iterations = 0;
    int file_check = 0;
    int gif = 0;
    int ITS; // iteration to save
    char path[30];
    char pathGif[30];
    Map *map;
    char *folder;

    int opt;
    while ((opt = getopt(argc, argv, "f:i:s:g")) != -1)
    {
        switch (opt)
        {
        case 'f': //filename
            file_check = 1;
            map = readMap(optarg);

            folder = malloc(strlen(optarg) - 4);
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

        map->data = updateMap(map->data, map->r, map->c);
    }

    if (gif == 1)
        saveToGif();

    freeMap(map->data, map->r);
    free(map);
    free(folder);

    return 0;
}