/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                             	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/18/03 12:00:36 by agrun             #+#    #+#             */
/*   Updated: 2023/18/03 12:00:39 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/*	Norminette dislikes	cmp = {2, 1, 4, 7, 4, 8, 3, 6, 4, 7, 8};
	...so this is the only way to circumvent this issue.			*/

static void	assign_array(int *cmp)
{
	cmp[0] = 2;
	cmp[1] = 1;
	cmp[2] = 4;
	cmp[3] = 7;
	cmp[4] = 4;
	cmp[5] = 8;
	cmp[6] = 3;
	cmp[7] = 6;
	cmp[8] = 4;
	cmp[9] = 7;
	cmp[10] = 8;
	cmp[11] = 0;
}

static int	check_beyond(char *str, int i)
{
	int	cmp[12];
	int	tmp;
	int	j;
	int	r;

	j = i;
	if (str[0] == '-')
		j--;
	if (i == 10)
		j = 10;
	tmp = str[i] - 48;
	assign_array(cmp);
	if (tmp > cmp[j])
		r = 0;
	if (tmp < cmp[j])
		r = 1;
	if (tmp == cmp[j])
		r = 2;
	return (r);
}

static int	check_minmax(char *str, int i)
{
	int		r;
	char	buff[12];

	assign_buffer(buff, str);
	if (buff[0] == '-' && i == 10)
		return (1);
	i -= 10;
	while (buff[i])
	{
		r = check_beyond(buff, i);
		if (r == 0)
			return (0);
		else if (r == 1)
			break ;
		else if (r == 2)
			i++;
	}
	return (1);
}

/*	Measure for dealing with multiple zeroes at start of string. 
	Also gotta consider a single zero! That's why we return (1).		*/

static int	ft_strlen(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[j] == '-')
	{
		j++;
		i++;
	}
	while (s[j] == '0' || s[j] == '+')
		j++;
	while (s[j])
	{
		i++;
		j++;
	}
	if (i == 0)
		return (1);
	return (i);
}

/*	Making sure that no broken values are entered. (0) return = not good.
	INT_MIN = -2147483648 & INT_MAX = 2147483647 are the limits.		*/

int	check_input(char **args)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (args[i])
	{
		l = ft_strlen(args[i]);
		if (l > 10)
		{
			if (l > 11)
				return (0);
			if (args[i][0] != '-' && l > 10)
				return (0);
			if (!check_minmax(args[i], l))
				return (0);
		}
		else if (l == 10)
		{
			if (!check_minmax(args[i], l))
				return (0);
		}
		i++;
	}
	return (1);
}
