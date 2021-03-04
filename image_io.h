#ifndef _IMAGE_IO_H
#define _IMAGE_IO_H

void saveToBmp(char *file, int **map, int r, int c);
void initGif(char *path, int r, int c);
void addFrameGif(int **map);
void saveToGif();

#endif