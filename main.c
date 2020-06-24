/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:30:20 by abourin           #+#    #+#             */
/*   Updated: 2020/02/03 14:59:14 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct s_a
{
	int	width;
	int height;
	char b_char;
};

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	first_line(FILE *file, struct s_a *a)
{
	if (fscanf(file, "%d %d %c\n", &(a->width), &(a->height), &(a->b_char)) != 3)
		return (1);
	return (0);
}

void	ft_display(char **map, int width, int height)
{
	int i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_putstr(map[i]);
		write(1, "\n", 1);
		i++;
	}
}

int	ft_fill(FILE *file, char **map, struct s_a a)
{
	char type;
	float x;
	float y;
	float width;
	float height;
	char c;
	int i;
	int j;
	int xmax;
	int ymax;

	i = 0;
	j = 0;
	while ((fscanf(file, "%c %f %f %f %f %c\n", &type, &x, &y, &width, &height, &c)) == 6)
	{
		xmax = (int)x + width;
		ymax = (int)y + height;
		while (i < a.width)
		{
			j = 0;
			while (j < a.height)
			{
				if ((j >= (int)x && j <= xmax) && (i >= (int)y && i <= ymax))
				{
					if (type == 'R')
						map[i][j] = c;
					else if (type == 'r')
						if ((i == (int)y || i == ymax) || j == (int)x || j == xmax)
							map[i][j] = c;
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}

int main(int av, char **ac)
{
	FILE	*file;
	struct s_a a;
	char	**map;
	int width;
	int height;
	int i;
	int j;

	if (av != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	file = fopen(ac[1], "r");
	if (!file)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	if (first_line(file, &a) == 1)
	{
		ft_putstr("Error: Operation file corrupted\n");
        return (1);
	}
	if (!(map = malloc(sizeof(char *) * (a.height + 1))))
		return (1);
	i = 0;
	while (i < a.height)
	{
		if (!(map[i] = malloc(sizeof(char) * (a.width + 1))))
			return (1);
		map[i][a.width] = '\0';
		i++;
	}
	i = 0;
	map[a.height] = NULL;
	while (i < a.height)
    {
		memset(map[i], a.b_char, a.width);
        i++;
    }
	ft_fill(file, map, a);
	ft_display(map, a.width, a.height);
}
