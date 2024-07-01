/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:26:02 by agrun             #+#    #+#             */
/*   Updated: 2023/09/05 12:50:34 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../libft/includes/libft.h"

/*	Checking if the horizontal edges of the map are properly sealed off.
	Check extract_map_2 for context on this!				*/

int	check_map_edge(char *map, int x, int xx)
{
	int	flag;

	flag = 0;
	if (x < 0 || x > (int)ft_strlen(map) || (map[x] && map[x] == '1'))
		return (0);
	while (x <= (int)ft_strlen(map) && flag < 1)
	{
		x++;
		if (flag < 1 && (map[x] == 32 || map[x] == 9))
			return (ft_error(1));
		if (flag == 0 && map[x] == '1')
			flag++;
	}
	while (map[x] && xx > -1)
	{
		xx--;
		if (flag < 2 && (map[xx] == 32 || map[xx] == 9))
			return (ft_error(1));
		if (flag == 1 && map[xx] == '1')
			flag++;
	}
	if (flag == 2)
		return (0);
	return (ft_error(1));
}

static int	check_for_illegal(char **map, int x, int y)
{
	while (map[y])
	{
		while (map[y][x])
		{
			if (illegal_character(map[y], x))
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

static int	check_remaining_file(char **mapfile, int x, int y)
{
	while (mapfile[y])
	{
		x = skip_whitespaces(mapfile[y], x);
		if (!mapfile[y][x])
		{
			x = 0;
			y++;
		}
		else if (mapfile[y][x] != '1')
			return (1);
		else
			return (y);
	}
	return (1);
}

/*	Extracting the part of the mapfile which contains map-information.
	Checking for irregularities afterwards.					*/

int	extract_map(char **mapfile, char **map, int x, int y)
{
	int	z;

	y = check_remaining_file(mapfile, 0, y);
	if (y == 1)
		return (ft_error(2));
	z = 0;
	while (mapfile[y])
	{
		map[z] = malloc(sizeof(char) * (ft_strlen(mapfile[y]) + 1));
		if (!map[z])
			return (ft_error(-4));
		while (mapfile[y][x])
		{
			map[z][x] = mapfile[y][x];
			x++;
		}
		map[z][x] = 0;
		x = 0;
		z++;
		y++;
	}
	map[z] = 0;
	if (check_for_illegal(map, 0, 0))
		return (ft_error(4));
	return (check_walls(map, 0, 0, 0));
}
