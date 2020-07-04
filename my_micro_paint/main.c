#include "micro_paint.h"

int get_area_size(FILE *stream, t_area *area)
{
	fscanf(stream, "%d ", &area->width);
	fscanf(stream, "%d ", &area->height);
	fscanf(stream, "%c\n", &area->backg);
	if (area->height > 300 || area->height < 0)
		return (-1);
	if (area->width > 300 || area->width < 0)
		return (-1);
	return (0);
}

int get_rect_params(FILE *stream, t_rect *rect)
{
	if (fscanf(stream, "%c ", &rect.type) == 0)
		return (0);
	if (fscanf(stream, "%f ", &rect.x) == 0)
		return (0);
	if (fscanf(stream, "%f ", &rect.y) == 0)
		return (0);
	if (fscanf(stream, "%f ", &rect->width) == 0)
		return (0);
	if (fscanf(stream, "%f ", &rect->height) == 0)
		return (0);
	if (fscanf(stream, "%c\n", &rect->bord) == 0)
		return (0);
	if (rect->type == 0 || rect->width == 0.0 || rect->height == 0.0)
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	FILE *stream;
	char **buf;
	t_area area;
	t_rect rect;

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
	if (get_area_size(stream, &area) == -1)
		return (1);
	if ((buf = prepare_area(&area)) == NULL)
		return (1);
	while (get_rect_params(stream, &rect))
	{
		draw_rectangles(buf, &area, &rect);
		memset(&rect, 0, sizeof(t_rect));
	}
	draw_buffer(buf, &area);
	free(buf);
	return (0);
}