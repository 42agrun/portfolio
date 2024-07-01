/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:26:02 by agrun             #+#    #+#             */
/*   Updated: 2023/08/11 10:26:07 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../libft/includes/libft.h"

/*	Having a regular floortile next to a space is considered a leak.	*/

static int	check_space(char **map, int x, int y, int max_x)
{
	if (map[y][x] != 32 && map[y][x] != 9)
		return (0);
	if (x + 1 < max_x && x < (int)ft_strlen(map[y]) && (map[y][x + 1] == '0'
		|| (map[y][x + 1] == '2' || map[y][x + 1] == '3')
		|| (map[y][x + 1] == 'W' || map[y][x + 1] == 'E'
		|| map[y][x + 1] == 'S' || map[y][x + 1] == 'N')))
		return (1);
	if (x > 0 && x - 1 < (int)ft_strlen(map[y]) && (map[y][x - 1] == '0'
		|| (map[y][x - 1] == '2' || map[y][x - 1] == '3')
		|| (map[y][x - 1] == 'W' || map[y][x - 1] == 'E'
		|| map[y][x - 1] == 'S' || map[y][x - 1] == 'N')))
		return (1);
	if (map[y + 1] && x < (int)ft_strlen(map[y + 1]) && (map[y + 1][x] == '0'
		|| (map[y + 1][x] == '2' || map[y + 1][x] == '3')
		|| (map[y + 1][x] == 'W' || map[y + 1][x] == 'E'
		|| map[y + 1][x] == 'S' || map[y + 1][x] == 'N')))
		return (1);
	if (y > 0 && x < (int)ft_strlen(map[y - 1]) && (map[y - 1][x] == '0'
		|| (map[y - 1][x] == '2' || map[y - 1][x] == '3')
		|| (map[y - 1][x] == 'W' || map[y - 1][x] == 'E'
		|| map[y - 1][x] == 'S' || map[y - 1][x] == 'N')))
		return (1);
	return (0);
}

static int	check_doors(char **map, int x, int y)
{
	int	d[2];

	if (BONUS == 0)
		return (0);
	d[0] = 0;
	d[1] = 0;
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == '2' || map[y][x] == '3')
	{
		if (map[y + 1] && map[y + 1][x] == '1')
			d[0]++;
		if (y > 0 && map[y - 1][x] == '1')
			d[0]++;
		if (map[y][x + 1] && map[y][x + 1] == '1')
			d[1]++;
		if (x > 0 && map[y][x - 1] == '1')
			d[1]++;
		if (map[y + 1][x] == 0 || map[y - 1][x] == 0
			|| map[y][x + 1] == 0 || map[y][x - 1] == 0)
			return (ft_error(-7));
		if (d[0] != 2 && d[1] != 2)
			return (ft_error(-7));
	}
	return (0);
}

/*	Making sure that the upper/lower part of the column is sealed off.		*/

static int	check_top_bottom(char **map, int x, int y, int mode)
{
	if (x < 0 || x > (int)ft_strlen(map[y]) || (map[y][x] && map[y][x] == '1'))
		return (0);
	if (mode == 0)
	{
		while (y > -1 && map[y])
		{
			if (x <= (int)ft_strlen(map[y])
				&& (map[y][x] == 32 || map[y][x] == 9))
				return (ft_error(1));
			else if (x > -1 && x <= (int)ft_strlen(map[y]) && map[y][x] == '1')
				return (0);
			y--;
		}
		return (ft_error(1));
	}
	while (map[y])
	{
		if (x <= (int)ft_strlen(map[y]) && (map[y][x] == 32 || map[y][x] == 9))
			return (ft_error(1));
		else if (x > -1 && x <= (int)ft_strlen(map[y]) && map[y][x] == '1')
			return (0);
		y++;
	}
	return (ft_error(1));
}

/*	Extracting information about the length of the line.			*/

static int	map_edge(char **map, int x, int y)
{
	while (map[y][x])
		x++;
	while (map[y][x] != '1' && map[y][x] != '0' && x > -1)
		x--;
	return (x + 1);
}

/*	The map needs to have closed-off walls, spaces are allowed next to them.

	The first set of tests is to make sure that a wall is the very first
	character within the line.						*/

int	check_walls(char **map, int x, int y, int max_x)
{
	while (map[y])
	{
		max_x = map_edge(map, 0, y);
		x = skip_whitespaces(map[y], 0);
		if (map[y][x] != '1')
			return (ft_error(1));
		x++;
		while (map[y][x] && x < max_x + 1)
		{
			if (map[y][x] != ' ' && map[y][x] != 9)
				if (check_top_bottom(map, x, y, 0)
					|| check_top_bottom(map, x, y, 1)
					|| check_map_edge(map[y], x, x)
					|| check_doors(map, x, y))
					return (1);
			if (check_space(map, x, y, max_x))
				return (ft_error(1));
			x++;
		}
		y++;
	}
	return (0);
}
