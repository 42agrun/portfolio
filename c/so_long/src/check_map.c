/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:26:02 by agrun             #+#    #+#             */
/*   Updated: 2023/04/05 10:26:07 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	check_max_values(char **map, int max_y, int x)
{
	x = 0;
	while (map[max_y][x])
	{
		if (map[max_y][x] != '1')
			return (ft_error(3));
		x++;
	}
	return (0);
}

static int	check_map_walls(char **map, int size)
{
	int	x;
	int	y;
	int	max_y;

	max_y = 0;
	while (map[max_y])
		max_y++;
	x = 0;
	y = 0;
	while (map[y][x])
	{
		if (map[y][x] != '1')
			return (ft_error(3));
		x++;
	}
	if (check_max_values(map, max_y - 1, x))
		return (1);
	y = 0;
	while (map[y])
	{
		if (map[y][0] != '1' || map[y][size] != '1')
			return (ft_error(3));
		y++;
	}
	return (max_y);
}

/*	Example of a bare minimum map that would be allowed:
	
	1 1 1 1 1
	1 P C E 1
	1 1 1 1 1								
	
	This map should also work if placed vertically.
	Also make sure the mapsize limit is being respected.	*/

static int	check_map_size(char **map, int i, int y)
{
	int	x[3];

	x[0] = 0;
	x[2] = 0;
	while (map[y])
	{
		x[1] = 0;
		while (map[y][i])
		{
			x[1]++;
			i++;
		}
		if (x[0] == 0)
			x[0] = x[1];
		else if (x[0] != x[1])
			return (ft_error(1));
		i = 0;
		y++;
	}
	if (y > 2 && (y > 60 || x[0] > 90))
		return (ft_error(8));
	if (y < 5 && x[0] < 3)
		if (y < 3 && x[0] < 5)
			return (ft_error(2));
	return (x[0]);
}

/*	Setting up "CEP" (Collectables/Exit/Player) for checking map-elements.

	Making sure that the map has borderwalls as well as an available path
	for collecting all of the items	before exiting the map itself.		
	
	The "1" if-check for x- and y-integers stands for prev. returned errors.*/

int	check_map(char **map)
{
	int		x_size;
	int		y_size;
	int		cep[4];
	t_root	*root;

	cep[0] = 0;
	cep[1] = 0;
	cep[2] = 0;
	cep[3] = 0;
	x_size = check_map_size(map, 0, 0);
	if (x_size == 1)
		return (1);
	y_size = check_map_walls(map, (x_size - 1));
	if (y_size == 1)
		return (1);
	if (check_map_elements(map, cep, 0, 0))
		return (1);
	if (check_map_path(map, cep, x_size, y_size))
		return (1);
	root = root_setup(map, x_size, y_size);
	if (!root)
		return (1);
	if (game_setup(root, map))
		return (1);
	return (0);
}
