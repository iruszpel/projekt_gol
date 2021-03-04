#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/libbmp.h"
#include "image_io.h"
#include "lib/gifenc.h"

static int width = 0;
static int height = 0;
static int desiredWidth = 512;
static int boxSize;
ge_GIF *gif = NULL;

void saveToBmp(char *path, int **map, int r, int c)
{
	boxSize = (desiredWidth) / c;
	width = boxSize * c + 1;
	height = boxSize * r + 1;
	bmp_img img;
	bmp_img_init_df(&img, width, height);

	for (size_t y = 0, x; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if ((y % boxSize == 0 || x % boxSize == 0))
			{
				bmp_pixel_init(&img.img_pixels[y][x], 230, 230, 230);
			}
			else if ((map[y / boxSize][x / boxSize] == 1) && !(y % boxSize == 0 || x % boxSize == 0))
			{
				bmp_pixel_init(&img.img_pixels[y][x], 255, 255, 255);
			}
			else
			{
				bmp_pixel_init(&img.img_pixels[y][x], 30, 30, 30);
			}
		}
	}
	char *new_path = malloc(sizeof path + 4);
	strcpy(new_path, path);
	strcat(new_path, ".bmp");

	bmp_img_write(&img, new_path);
	bmp_img_free(&img);
}

void initGif(char *path, int r, int c)
{
	boxSize = (desiredWidth) / c;
	width = boxSize * c + 1;
	height = boxSize * r + 1;
	gif = ge_new_gif(
		path,		   /* file name */
		width, height, /* canvas size */
		(uint8_t[]){
			0xE6, 0xE6, 0xE6, /* 0 -> grey */
			0xFF, 0xFF, 0xFF, /* 1 -> black */
			0x1E, 0x1E, 0x1E  /* 2 -> close to white */
		},
		2, /* palette depth == log2(# of colors) */
		0  /* infinite loop */
	);
}
void addFrameGif(int **map)
{
	if (width == 0 || height == 0)
		exit(1);
	for (size_t y = 0, x; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if ((y % boxSize == 0 || x % boxSize == 0))
			{
				gif->frame[y * width + x] = 0;
			}
			else if ((map[y / boxSize][x / boxSize] == 1) && !(y % boxSize == 0 || x % boxSize == 0))
			{
				gif->frame[y * width + x] = 1;
			}
			else
			{
				gif->frame[y * width + x] = 2;
			}
		}
	}
	ge_add_frame(gif, 25);
}
void saveToGif()
{
	ge_close_gif(gif);
}
/*

	/* draw some frames 
	for (int frames = 0; i < 4 * 6 / 3; i++)
	{
		for (size_t y = 0, x; y < height; y++)
		{
			for (x = 0; x < width; x++)
			{
				if ((y % boxSize == 0 || x % boxSize == 0))
				{
					gif->frame[y * width + x] = 0;
				}
				else if ((map[y / boxSize][x / boxSize] == 1) && !(y % boxSize == 0 || x % boxSize == 0))
				{
					gif->frame[y * width + x] = 1;
				}
				else
				{
					gif->frame[y * width + x] = 2;
				}
			}
		}
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				gif->frame[y * width + x] = (i * 3 + j) / 6 % 4;
			}
		}

		ge_add_frame(gif, 25);
	}
*/