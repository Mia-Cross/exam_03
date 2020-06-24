#include "micro_paint.h"

char **prepare_area(t_area *area)
{
	char	**buf;
	int		y;

	if (!(buf = malloc(sizeof(char *) * area->height)))
		return (NULL);
	y = -1;
	while (++y < area->height)
	{
		if (!(buf[y] = malloc(sizeof(char) * area->width)))
			return (NULL);
		memset(buf[y], area->backg, area->width);
	}
	return(buf);
}

void draw_rectangles(char **buf, t_area *area, t_rect *rect)
{
	int x;
	int y;
	int h;
	int w;

	x = (int)rect->x;
	w = -1;
	while (x >= 0 && x < area->width && ++w < rect->width)
	{
		y = (int)rect->y;
		h = -1;
		while (y >= 0 && y < area->height && ++h < rect->height)
		{
			if (rect->type == 'R' || h == 0 || h == rect->height - 1.0 || w == 0 || w == rect->width - 1.0)
				buf[y][x] = rect->bord;
			y++;
		}
		x++;
	}
}

void draw_buffer(char **buf, t_area *area)
{
	int x;
	int y;

	y = -1;
	while (++y < area->height)
	{
		x = -1;
		while (++x < area->width)
			write(1, &buf[y][x], 1);
		write(1, "\n", 1);
	}
}
