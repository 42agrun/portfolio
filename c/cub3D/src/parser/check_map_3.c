/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:26:02 by agrun             #+#    #+#             */
/*   Updated: 2023/09/05 12:49:42 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../libft/includes/libft.h"

/*	The number tells us which direction the player is facing.		
		69 = E | 78 = N | 83 = S | 87 = W 				*/

static int	check_element_p(int *el, char **map, int *xy)
{
	int	x;
	int	y;

	x = xy[0];
	y = xy[1];
	if (el[0] && el[1] && el[2] && el[3] && el[4] && el[5])
	{
		if (map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'W' || map[y][x] == 'E')
		{
			if (el[6])
				return (ft_error(2));
			el[6] = (int)map[y][x];
		}
	}
	return (0);
}

int	check_element_ex(int *el, char **map, char **data, int *xy)
{
	int	z;

	if (map[xy[1]][xy[0]] == 'C' && is_a_space(map[xy[1]], xy[0] + 1))
	{
		if (el[5])
			return (ft_error(2));
		data[5] = malloc(sizeof (char) * (ft_strlen(map[xy[1]])) + 1);
		if (!data[5])
			return (ft_error(-4));
		xy[0] = skip_whitespaces(map[xy[1]], xy[0] + 1);
		z = ft_strlen(map[xy[1]]) - 1;
		while (map[xy[1]][z] == 32 || map[xy[1]][z] == 9)
			z--;
		while (map[xy[1]][xy[0]] && xy[0] < z + 1)
		{
			data[5][xy[2]] = map[xy[1]][xy[0]];
			xy[2]++;
			xy[0]++;
		}
		data[5][xy[2]] = 0;
		xy[2] = 0;
		el[5] = 1;
		return (0);
	}
	return (check_element_p(el, map, xy));
}
