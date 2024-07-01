/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:26:02 by agrun             #+#    #+#             */
/*   Updated: 2023/08/13 10:26:07 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	skip_commas(char *str, int i)
{
	while (str[i] == ',')
		i++;
	return (i);
}

int	is_a_space(char *str, int i)
{
	if (str[i] == ' ' || str[i] == 9)
		return (1);
	return (0);
}

int	illegal_character(char *str, int i)
{
	if (BONUS == 1)
	{
		if (str[i] != 32 && str[i] != 9 && str[i] != 10
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E'
			&& str[i] != 'W' && str[i] != '0' && str[i] != '1'
			&& str[i] != '2' && str[i] != '3')
			return (1);
	}
	else
	{
		if (str[i] != 32 && str[i] != 9 && str[i] != 10
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E'
			&& str[i] != 'W' && str[i] != '1' && str[i] != '0')
			return (1);
	}
	return (0);
}

int	skip_whitespaces(char *str, int i)
{
	while (str[i] == 32 || str[i] == 9)
		i++;
	return (i);
}

int	ft_array_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
