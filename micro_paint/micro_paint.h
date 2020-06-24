#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_area
{
	int		width;
	int		height;
	char	backg;
}				t_area;

typedef struct	s_rect
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	bord;
}				t_rect;

char **prepare_area(t_area *area);
void draw_rectangles(char **buf, t_area *area, t_rect *rect);
void draw_buffer(char **buf, t_area *area);

#endif