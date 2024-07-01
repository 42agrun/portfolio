/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:26:02 by agrun             #+#    #+#             */
/*   Updated: 2023/08/11 10:26:07 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	skip_everything(char *str, int i)
{
	i = skip_whitespaces(str, i);
	if (str[i] == ',')
		i++;
	i = skip_whitespaces(str, i);
	return (i);
}

static void	reset_tmp(char *tmp)
{
	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = 0;
	tmp[3] = 0;
}

static int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i++] == '-')
			sign = -1;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i++] - '0';
	}
	result *= sign;
	return (result);
}

static int	check_colors_2(int *colors, char **data, int i, int j)
{
	char	tmp[4];
	int		flag;

	flag = 2;
	while (++flag < 6)
	{
		j = -1;
		reset_tmp(tmp);
		while (data[5][i] && data[5][i] != ',' && !(is_a_space(data[5], i)))
		{
			if (j == 3 || data[5][i] < '0' || data[5][i] > '9')
				return (ft_error(3));
			tmp[++j] = data[5][i];
			i++;
		}
		tmp[j + 1] = 0;
		colors[flag] = ft_atoi(tmp);
		i = skip_everything(data[5], i);
		if (data[5][i] && data[5][i] == ',')
			return (ft_error(2));
	}
	i = skip_whitespaces(data[5], i);
	if (data[5][i])
		return (ft_error(2));
	return (0);
}

/*	colors 0-2 refer to the RGB-values of the floor (F).
	colors 3-5 refer to the RGB-values of the ceiling (C).

	It is essential that none of them exceed 255 as a value.
	Data 4 and 5 contain the information for both these elements.		*/

int	check_colors(int *colors, char **data, int i, int j)
{
	char	tmp[4];
	int		flag;

	flag = -1;
	while (++flag < 3)
	{
		j = -1;
		reset_tmp(tmp);
		while (data[4][i] && data[4][i] != ',' && !(is_a_space(data[4], i)))
		{
			if (j == 3 || data[4][i] < '0' || data[4][i] > '9')
				return (ft_error(3));
			tmp[++j] = data[4][i];
			i++;
		}
		tmp[j + 1] = 0;
		colors[flag] = ft_atoi(tmp);
		i = skip_everything(data[4], i);
		if (data[4][i] && data[4][i] == ',')
			return (ft_error(2));
	}
	i = skip_whitespaces(data[4], i);
	if (data[4][i])
		return (ft_error(2));
	return (check_colors_2(colors, data, 0, 0));
}
