/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dupes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:13:13 by agrun             #+#    #+#             */
/*   Updated: 2023/03/18 10:13:18 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/*	This function is used on "check_input" to create a copy of the argument
	without the potential zeroes in front of the number.
	
	Example: "0000000000000000000000001234" => "1234"			*/

void	assign_buffer(char *buff, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] == '-')
	{
		buff[j] = str[i];
		j++;
		i++;
	}
	while (str[i] == '0' || str[i] == '+')
		i++;
	while (str[i])
	{
		buff[j] = str[i];
		j++;
		i++;
	}
	buff[j] = 0;
}

static int	*sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i;
	int				buff;

	i = 0;
	while (i < (size - 1))
	{
		if (tab[i] > tab[i + 1])
		{
			buff = tab[i + 1];
			tab[i + 1] = tab[i];
			tab[i] = buff;
			i = 0;
		}
		else
			i++;
	}
	return (tab);
}

static int	*fill_tmp(int *tmp, int *a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		tmp[i] = a[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

/*	Creating a copy of stack A to sort and then check it for duplicates.
	Beware, sorting the original stack would alter its content permanently!
	If dupes are found the program is supposed to return an ERROR.		*/

int	check_dupes(int *stack)
{
	int	*tmp;
	int	i;

	i = 0;
	if (!stack)
		return (1);
	while (stack[i])
		i++;
	tmp = malloc(sizeof(int) * (i + 1));
	if (!tmp)
		return (-1);
	tmp = fill_tmp(tmp, stack);
	tmp = sort_int_tab(tmp, i);
	i = 0;
	while (tmp[i] && tmp[i + 1])
	{
		if (tmp[i] == tmp[i + 1])
		{
			ft_free(&tmp);
			return (ft_error(1));
		}
		i++;
	}
	ft_free(&tmp);
	return (0);
}
