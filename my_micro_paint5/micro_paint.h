#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_area
{
	int w;
	int h;
	char c;
	char **buf;
}			t_area;

typedef struct s_rect
{
	char r;
	float x;
	float y;
	float w;
	float h;
	char c;
}			t_rect;

#endif