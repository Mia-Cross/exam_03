#include "micro_paint.h"

void ft_free_from(char **buf, int y)
{
	while (--y >= 0)
		free(buf[y]);
	free(buf);
}

int get_area(FILE *stream, t_area *area)
{
	int y;

	if (fscanf(stream, "%d %d %c", &area->w, &area->h, &area->c) == -1)
		return (0);
	if (area->h <= 0 || area->w <= 0 || area->h > 300 || area->w > 300)
		return (0);
	if (!(area->buf = malloc(sizeof(char *) * area->h)))
		return (0);
	y = -1;
	while (++y < area->h)
	{
		if (!(area->buf[y] = malloc(sizeof(char) * area->w)))
		{
			ft_free_from(area->buf, y);
			return (1);
		}
		memset(area->buf[y], area->c, area->w);
	}
	return (1);
}

int get_rectangle(FILE *stream, t_rect *rect)
{
	int ret;

	memset(rect, 0, sizeof(t_rect));
	ret = fscanf(stream, "\n%c %f %f %f %f %c", &rect->r, &rect->x, &rect->y, &rect->w, &rect->h, &rect->c);
//	printf("ret = %d\tr = %c\tx = %f\n", ret, rect->r, rect->x);
	if (!rect->r && ret == -1)
		return (0);
	if (ret == -1)
		return (-1);
	if (rect->w <= 0 || rect->h <= 0 || !(rect->r == 'R' || rect->r == 'r'))
		return (-1);
	return (1);
}

void draw_rectangle(t_rect rect, t_area *area)
{
	int x;
	int y;

	y = (int)(rect.y);
	while (y < area->h && y < (int)(rect.y + rect.h))
	{
		x = (int)(rect.x);
		while (x < area->w && x < (int)(rect.x + rect.w))
		{
			if (x >= 0 && y >= 0 && (rect.r == 'R' || x == (int)rect.x || y == (int)rect.y || x == (int)(rect.x + rect.w - 1) || y == (int)(rect.y + rect.h - 1)))
				area->buf[y][x] = rect.c;
			x++;
		}
		y++;
	}
}

void draw_buffer(t_area area)
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
	}
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
	if (!(stream = fopen(av[1], "r")) || stream == NULL)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	if (!get_area(stream, &area))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		fclose(stream);
		return (1);
	}
	while ((ret = get_rectangle(stream, &rect)) && ret)
	{
		if (ret == -1)
		{
			write(1, "Error: Operation file corrupted\n", 32);
			ft_free_from(area.buf, area.h);
			fclose(stream);
			return (1);
		}
		draw_rectangle(rect, &area);
	}
	draw_buffer(area);
	ft_free_from(area.buf, area.h);
	fclose(stream);
	return (0);
}