/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:26:02 by agrun             #+#    #+#             */
/*   Updated: 2023/09/05 12:49:32 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../libft/includes/libft.h"

static int	check_element_5(int *el, char **map, char **data, int *xy)
{
	int	z;

	if (map[xy[1]][xy[0]] == 'F' && is_a_space(map[xy[1]], xy[0] + 1))
	{
		if (el[4])
			return (ft_error(2));
		data[4] = malloc(sizeof (char) * (ft_strlen(map[xy[1]])) + 1);
		if (!data[4])
			return (ft_error(-4));
		xy[0] = skip_whitespaces(map[xy[1]], xy[0] + 1);
		z = ft_strlen(map[xy[1]]) - 1;
		while (map[xy[1]][z] == 32 || map[xy[1]][z] == 9)
			z--;
		while (map[xy[1]][xy[0]] && xy[0] < z + 1)
		{
			data[4][xy[2]] = map[xy[1]][xy[0]];
			xy[2]++;
			xy[0]++;
		}
		data[4][xy[2]] = 0;
		xy[2] = 0;
		el[4] = 1;
		return (0);
	}
	return (check_element_ex(el, map, data, xy));
}

static int	check_element_4(int *el, char **map, char **data, int *xy)
{
	if (map[xy[1]][xy[0]] == 'E' && map[xy[1]][xy[0] + 1] == 'A')
	{
		if (el[3])
			return (ft_error(2));
		data[3] = malloc(sizeof (char) * (ft_strlen(map[xy[1]])) + 1);
		if (!data[3])
			return (ft_error(-4));
		xy[0] = skip_whitespaces(map[xy[1]], xy[0] + 2);
		while (map[xy[1]][xy[0]] && map[xy[1]][xy[0]] != 32)
		{
			data[3][xy[2]] = map[xy[1]][xy[0]];
			xy[2]++;
			xy[0]++;
		}
		data[3][xy[2]] = 0;
		xy[2] = 0;
		el[3] = 1;
	}
	else
		return (check_element_5(el, map, data, xy));
	return (0);
}

static int	check_element_3(int *el, char **map, char **data, int *xy)
{
	if (map[xy[1]][xy[0]] == 'W' && map[xy[1]][xy[0] + 1] == 'E')
	{
		if (el[2])
			return (ft_error(2));
		data[2] = malloc(sizeof (char) * (ft_strlen(map[xy[1]])) + 1);
		if (!data[2])
			return (ft_error(-4));
		xy[0] = skip_whitespaces(map[xy[1]], xy[0] + 2);
		while (map[xy[1]][xy[0]] && map[xy[1]][xy[0]] != 32)
		{
			data[2][xy[2]] = map[xy[1]][xy[0]];
			xy[2]++;
			xy[0]++;
		}
		data[2][xy[2]] = 0;
		xy[2] = 0;
		el[2] = 1;
	}
	else
		return (check_element_4(el, map, data, xy));
	return (0);
}

static int	check_element_2(int *el, char **map, char **data, int *xy)
{
	if (map[xy[1]][xy[0]] == 'S' && map[xy[1]][xy[0] + 1] == 'O')
	{
		if (el[1])
			return (ft_error(2));
		data[1] = malloc(sizeof (char) * (ft_strlen(map[xy[1]])) + 1);
		if (!data[1])
			return (ft_error(-4));
		xy[0] = skip_whitespaces(map[xy[1]], xy[0] + 2);
		while (map[xy[1]][xy[0]] && map[xy[1]][xy[0]] != 32)
		{
			data[1][xy[2]] = map[xy[1]][xy[0]];
			xy[2]++;
			xy[0]++;
		}
		data[1][xy[2]] = 0;
		xy[2] = 0;
		el[1] = 1;
	}
	else
		return (check_element_3(el, map, data, xy));
	return (0);
}

/*	elements[0] = 0;		// NO
	elements[1] = 0;		// SO
	elements[2] = 0;		// WE
	elements[3] = 0;		// EA
	elements[4] = 0;		// F
	elements[5] = 0;		// C
	elements[6] = 0;		// N/W/S/E (Player)			*/

int	check_element(int *el, char **map, char **data, int *xy)
{
	if (map[xy[1]][xy[0]] == 'N' && map[xy[1]][xy[0] + 1] == 'O')
	{
		if (el[0])
			return (ft_error(2));
		data[0] = malloc(sizeof (char) * (ft_strlen(map[xy[1]])) + 1);
		if (!data[0])
			return (ft_error(-4));
		xy[0] = skip_whitespaces(map[xy[1]], xy[0] + 2);
		while (map[xy[1]][xy[0]] && map[xy[1]][xy[0]] != 32)
		{
			data[0][xy[2]] = map[xy[1]][xy[0]];
			xy[2]++;
			xy[0]++;
		}
		data[0][xy[2]] = 0;
		xy[2] = 0;
		el[0] = 1;
	}
	else
		return (check_element_2(el, map, data, xy));
	return (0);
}
