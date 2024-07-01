/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:45:46 by agrun             #+#    #+#             */
/*   Updated: 2023/04/05 10:45:49 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	Use this function in case malloc fails mid-way during copy creation.	*/

static void	ft_free_leftover(char **map_copy, int y)
{
	int	i;

	if (y == 0)
		return ;
	i = 0;
	while (map_copy[i])
	{
		free(map_copy[i]);
		map_copy[i] = NULL;
		i++;
	}
	if (map_copy)
	{
		free(map_copy);
		map_copy = NULL;
	}
}

/*	Creates a copy of the map for flooding/manipulation.			*/

static char	**copy_map(char **map, int x_size, int y_size)
{
	int		x;
	int		y;
	char	**map_copy;

	map_copy = malloc(sizeof(char *) * (y_size + 1));
	if (!map_copy)
		return (NULL);
	y = 0;
	while (map[y])
	{
		map_copy[y] = malloc(sizeof(char) * (x_size + 1));
		if (!map_copy[y])
		{
			ft_free_leftover(map_copy, y);
			return (NULL);
		}
		x = -1;
		while (map[y][++x])
			map_copy[y][x] = map[y][x];
		y++;
	}
	map_copy[y] = 0;
	return (map_copy);
}

/*	Simulates a flood which fills up the map, starting from the player-pos.
	Try to see if it can reach all the collectables as well as the exit!	*/

int	check_map_path(char **map, int *cep, int x_size, int y_size)
{
	int		*pp;
	char	**map_copy;

	pp = malloc(sizeof(int) * (3));
	if (!pp)
		return (ft_error(-4));
	find_player_pos(map, pp);
	map_copy = copy_map(map, x_size, y_size);
	if (!map_copy)
	{
		free(pp);
		pp = NULL;
		return (ft_error(-4));
	}
	if (flood_map(map_copy, pp, cep))
	{
		free(pp);
		pp = NULL;
		ft_free_array(map_copy);
		return (ft_error(6));
	}
	free(pp);
	pp = NULL;
	ft_free_array(map_copy);
	return (0);
}
