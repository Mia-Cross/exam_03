#include "micro_paint.h"

void draw_buffer(t_area *area)
{
	int x;
	int y;

	y = -1;
//	printf("lol");
	while (++y < area->h)
	{
		x = -1;
		while (++x < area->w)
			write(1, &area->buf[y][x], 1);
		write(1, "\n", 1);
		free(area->buf[y]);
	}
	free(area->buf);
}

int set_area(t_area *area, FILE *stream)
{
	int y;

	if (fscanf(stream, "%d %d %c", &area->w, &area->h, &area->c) == -1)
		return (0);
//	printf("%d %d %c", area->w, area->h, area->c);
	if (area->w <= 0 || area->h <= 0 || area->w > 300 || area->h > 300)
		return (0);
	if (!(area->buf = malloc(sizeof(char *) * area->h)))
		return (0);
	y = -1;
	while (++y < area->h)
	{
		if (!(area->buf[y] = malloc(sizeof(char) * area->w)))
			return (0);
		memset(area->buf[y], area->c, area->w);
	}
	return (1);
}

int set_rectangle(t_rect *rect, FILE *stream)
{
	printf("SR-go:");
	memset(rect, 0, sizeof(t_rect));
	if (fscanf(stream, "\n%c %f %f %f %f %c", &rect->r, &rect->x, &rect->y, &rect->w, &rect->h, &rect->c) < 0)
		printf("bad read");
		return (-1);
	printf("\n%c %f %f %f %f %c", rect->r, rect->x, rect->y, rect->w, rect->h, rect->c);
	if (rect->r == 0)
		printf("return 0");
		return (0);
	if (!(rect->r == 'R' || rect->r == 'r') || !rect->w || !rect->h)
		printf("bad parm");
		return (-1);
	printf("end'SR\n");
	return (1);
}

void draw_rectangle(t_rect rect, t_area *area)
{
	int y;
	int x;

//	printf("DR-go:");
	y = (int)rect.y;
	while (y >= 0 && y < area->h && y < (int)(rect.y + rect.h))
	{
		x = (int)rect.x;
		while (x >= 0 && x < area->w && x < (int)(rect.x + rect.w))
		{
			if (rect.r == 'R' || x == (int)rect.x || x == (int)(rect.x + rect.w - 1) || y == (int)(rect.y + rect.h - 1) || y == (int)rect.y)
				area->buf[y][x] = rect.c;
			x++;
		}
		y++;
	}
//	printf("end-DR\n");
}

int main(int ac, char **av)
{
	t_area area;
	t_rect rect;
	FILE *stream;
	int ret;

	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!(stream = fopen(av[1], "r")))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	if (!set_area(&area, stream))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	while ((ret = set_rectangle(&rect, stream) && ret > 0))
		draw_rectangle(rect, &area);
//	printf("ret = %d\n", ret);
	if (ret == -1)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
//	printf("et la ?\n");
	draw_buffer(&area);
//	fclose(stream);
	return (0);
}