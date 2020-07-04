#include "micro_paint.h"

int	set_area(t_area *area, FILE *stream)
{
	int y;

	fscanf(stream, "%d %d %c", &area->w, &area->h, &area->c);
	if (area->w <= 0 || area->w > 300 || area->h <= 0 || area->h > 300)
		return (0);
	if (!(area->buf = malloc(sizeof(char *) * area->h)))
		return (0);
	y = -1;
	while (++y < area->h)
	{
		if (!(area->buf[y] = calloc(area->w, sizeof(char))))
			return (0);
		memset(area->buf[y], area->c, area->w);
	}
	return (1);
}

int set_rectangles(t_rect *rect, FILE *stream)
{
	memset(rect, 0, sizeof(t_rect));
	if (fscanf(stream, "\n%c %f %f %f %f %c", &rect->mode, &rect->x, &rect->y, &rect->wid, &rect->hei, &rect->c) < 0)
		return (-1);
	if (rect->mode)
		return (0);
	if (!(rect->mode == 'R' || rect->mode == 'r'))
		return (-1);
	return (1);
}

void draw_rectangles(t_rect rect, int x_max, int y_max, char **buf)
{
	int x;
	int y;

	y = (int)rect.y;
	while (y >= 0 && y < y_max && y < (int)(rect.y + rect.hei))
	{
		x = (int)rect.x;
		while (x >= 0 && x < x_max && x < (int)(rect.x + rect.wid))
		{
			if (rect.mode == 'R' || x == (int)rect.x || x == (int)(rect.x + rect.wid - 1) || y == (int)rect.y || y == (int)(rect.y + rect.hei - 1))
				buf[y][x] = rect.c;
			x++;
		}
		y++;
	}
}

void draw_result(t_area area)
{
	int x;
	int y;

	y = -1;
	while (++y < area.h)
	{
		x = -1;
		while (++x < area.w)
			write(1, &area.buf[y][x], 1);
		write(1, "\n", 1);
		free(area.buf[y]);
	}
	free(area.buf);
}

int main(int ac, char **av)
{
	FILE *stream;
	t_area area;
	t_rect rect;
	int ret;

	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	stream = fopen(av[1], "r");
	if (stream == NULL)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	if (!set_area(&area, stream))
		return (1);
	while ((ret = set_rectangles(&rect, stream)) && ret > 0)
		draw_rectangles(rect, area.w, area.h, area.buf);
	if (ret == -1)
		return (1);
	draw_result(area);
	fclose(stream);
	return (0);
}