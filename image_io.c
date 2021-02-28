#include <stdio.h>
#include <string.h>
#include "libbmp.h"
#include "image_io.h"

void saveToBmp(char *path, int **map, int r, int c)
{
	int desiredWidth = 512;
	int boxSize = (desiredWidth) / c;
	int width = boxSize * c + 1;
	int height = boxSize * r + 1;
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
	char * new_path = malloc(sizeof path + 4);
	strcpy(new_path, path);
    strcat(new_path, ".bmp");
	
	bmp_img_write(&img, new_path);
	bmp_img_free(&img);
}