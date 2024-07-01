/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:29:14 by agrun             #+#    #+#             */
/*   Updated: 2023/04/05 10:29:17 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	Printing out the total amount of steps taken within the game.		*/

void	print_steps(int steps, t_root *root)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_itoa(steps);
	if (!str)
	{
		write(2, "Error\n", 6);
		write(2, "Malloc failed, not enough memory!\n", 34);
		root_destroy(root, 1);
	}
	write(1, "You have taken a total of ", 26);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, " step(s)!\n", 10);
	free(str);
	str = NULL;
}

/*	Useful function for finding the position of the player on the map.	*/

void	find_player_pos(char **map, int *pp)
{
	int	x;
	int	y;

	pp[0] = 0;
	pp[1] = 0;
	pp[2] = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				pp[0] = x;
				pp[1] = y;
				break ;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

/*	0 for an empty space,
	1 for a wall,
	C for a collectible,
	E for a map exit,
	P for the player’s starting position.

	Make sure the map is rectangular and can be solved.
	Also check for duplicates of the exit and player elements!		*/

static void	init_cep(int *cep)
{
	cep[0] = 0;
	cep[1] = 0;
	cep[2] = 0;
	cep[3] = 0;
}

int	check_map_elements(char **map, int *cep, int x, int y)
{
	init_cep(cep);
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				cep[0]++;
			else if (map[y][x] == 'E')
				cep[1]++;
			else if (map[y][x] == 'P')
				cep[2]++;
			else if (map[y][x] != '1' && map[y][x] != '0')
				return (ft_error(7));
			x++;
		}
		x = 0;
		y++;
	}
	if (cep[0] > 0 && cep[1] == 1 && cep[2] == 1)
		return (0);
	else if (cep[1] > 1 || cep[2] > 1)
		return (ft_error(4));
	return (ft_error(5));
}
