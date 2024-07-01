/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c             	                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:45:46 by agrun             #+#    #+#             */
/*   Updated: 2023/04/05 10:45:49 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	Starting the search on the 2nd row since the first one only has walls.	*/

static int	find_water(char **map, int *xy)
{
	int	x;
	int	y;

	x = 0;
	y = 1;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'W')
			{
				xy[0] = x;
				xy[1] = y;
				map[y][x] = 'w';
				return (1);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (0);
}

/*	Gives instructions to the flood function for flooding the area.		*/

static int	flood_extension(int flag, int x, int y)
{
	if (flag == 0)
	{
		if (x)
			return (x);
		return (y - 1);
	}
	else if (flag == 1)
	{
		if (x)
			return (x);
		return (y + 1);
	}
	else if (flag == 2)
	{
		if (x)
			return (x - 1);
		return (y);
	}
	else if (flag == 3)
	{
		if (x)
			return (x + 1);
		return (y);
	}
	return (0);
}

/*	Converts every space that's being touched by the water into a "W".
	Starts by flooding each available space next to the player position.
	That's why this action needs to be performed four times (see flag).

		if (map[y][x] && map[y][x] != '1' && map[y][x] != 'w'
			&& map[y][x] != 'W')					*/

static void	flooding_map(char **map, int *cep, int *xy)
{
	int	flag;
	int	x;
	int	y;

	flag = 0;
	while (flag < 4)
	{
		x = xy[0];
		y = xy[1];
		x = flood_extension(flag, xy[0], 0);
		y = flood_extension(flag, 0, xy[1]);
		if (map[y][x] == 'P' || map[y][x] == 'C'
			|| map[y][x] == 'E' || map[y][x] == '0')
		{
			if (map[y][x] == 'C')
				cep[0]++;
			else if (map[y][x] == 'E')
				cep[1] = 2;
			map[y][x] = 'W';
		}
		flag++;
	}
}

int	flood_map(char **map, int *pp, int *cep)
{
	int	c;
	int	xy[3];

	c = cep[0];
	xy[0] = pp[0];
	xy[1] = pp[1];
	flooding_map(map, cep, xy);
	while (find_water(map, xy))
		flooding_map(map, cep, xy);
	if (c * 2 == cep[0] && cep[1] == 2)
		return (0);
	return (1);
}
