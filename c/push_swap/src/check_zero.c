/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_zero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:13:13 by agrun             #+#    #+#             */
/*   Updated: 2023/03/18 10:13:18 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/*	Extracting the exact position of the gap within the list.		*/

static void	get_smallest(int *c, int *min, int pos)
{
	int	i;
	int	next_min;

	next_min = c[0];
	i = 0;
	while ((c[i] || i == pos) && min[1] == 0)
	{
		if (c[i] < min[0] && c[i] > 0)
			min[0] = c[i];
		i++;
	}
	i = 0;
	while (c[i] || i == pos)
	{
		if (c[i] < next_min && c[i] > min[0] && c[i] > 0)
			next_min = c[i];
		i++;
	}
	if (min[0] == 2147483647)
		min[2] = 1;
	else if (next_min == min[0] + 1)
		min[1] = next_min;
	else
		min[2] = min[0] + 1;
}

/*	Finding the gap within the list to know how much I am allowed to move.	*/

static void	check_room(int *c, int pos)
{
	int	i;
	int	min[4];

	min[0] = 2147483647;
	min[1] = 0;
	min[2] = 0;
	min[3] = 0;
	while (min[2] == 0)
	{
		get_smallest(c, min, pos);
		if (min[2] == 0)
			min[0] = min[1];
	}
	i = 0;
	if (min[2] == 1)
		c[pos] = 1;
	else
	{
		while (c[i] || i == pos)
		{
			if (c[i] >= 0 && c[i] < min[2])
				c[i] += 1;
			i++;
		}
	}
}

/*	Moving everthing by 1 to create space for the zero buffer.		*/

static void	rearrange(int *c, int mode, int pos, int i)
{
	i = 0;
	if (mode == 0)
		check_room(c, pos);
	if (mode == 1)
	{
		while (c[i] || i == pos)
		{
			if (c[i] < 0)
				c[i]--;
			if (c[i] == 0)
				c[i] = -1;
			i++;
		}
	}
	if (mode == 2)
	{
		while (c[i] || i == pos)
		{
			if (c[i] > 0)
				c[i] += 1;
			if (c[i] == 0)
				c[i] = 1;
			i++;
		}
	}
}

/*	Checking if any of the extreme ends has been filled up yet.		*/

static void	zero_protection(int *c, int pos)
{
	int	i;
	int	m;
	int	p;

	i = 0;
	m = 0;
	p = 0;
	while (c[i] || c[i + 1])
	{
		if (c[i] == 2147483647)
			p = 1;
		if (c[i] == -2147483648)
			m = 1;
		i++;
	}
	if (p == 1 && m == 0)
		rearrange(c, 1, pos, i);
	else if (p == 0 && m == 1)
		rearrange(c, 2, pos, i);
	else if (p == 0 && m == 0)
		rearrange(c, 2, pos, i);
	else
		rearrange(c, 0, pos, i);
}

/*	Converting the arguments via atoi for easier handling.
	Using a long long as a temporary solution to hold the zero substitute.
	Make sure there's no second zero on the array ("z" for checking).	*/

int	*fill_stack(int *stack, char **args)
{
	int	i;
	int	z;
	int	nb;

	i = 0;
	z = -1;
	while (args[i])
	{
		nb = ft_atoi(args[i]);
		if (z > -1 && nb == 0)
			return (NULL);
		if (nb == 0)
			z = i;
		stack[i] = nb;
		i++;
	}
	stack[i] = 0;
	if (z > -1)
		zero_protection(stack, z);
	return (stack);
}
