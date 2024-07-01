/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_head.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:13:13 by agrun             #+#    #+#             */
/*   Updated: 2023/03/18 10:13:18 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	get_smallest(int *head)
{
	int	i;
	int	h;
	int	next;

	i = 0;
	h = 0;
	next = 2147483647;
	while (head[i])
	{
		if (head[i] == -2147483648)
			h = 1;
		i++;
	}
	i = 0;
	if (h == 1)
	{
		while (head[i])
		{
			if (head[i] < next && head[i] != -2147483648)
				next = head[i];
			i++;
		}
		return (next);
	}
	return (0);
}

static int	get_small(int *head, int min, int check)
{
	int	i;
	int	next_min;

	i = 0;
	if (head[check] == -2147483648)
		return (-2147483648);
	next_min = 2147483647;
	while (head[i])
	{
		if (head[i] < next_min && head[i] != min && head[i] > min)
			next_min = head[i];
		i++;
	}
	return (next_min);
}

void	overwrite_head(int *head, int *stack)
{
	int	i;

	i = 0;
	head[0] = 0;
	while (i < array_size(stack))
	{
		head[i] = stack[i];
		i++;
	}
	head[i] = 0;
}

void	define_head(int *head, int *stack)
{
	int	i;
	int	small;
	int	steps;

	overwrite_head(head, stack);
	i = 0;
	steps = 1;
	small = -2147483648;
	while (head[i])
	{
		small = get_small(head, small, i);
		if (head[i] == small)
		{
			stack[i] = steps;
			if (get_smallest(head) && head[i] != -2147483648)
				stack[i]++;
			if (head[i] == 214783647)
				stack[i] = array_size(stack);
			steps = 0;
			small = -2147483648;
			i++;
		}
		steps++;
	}
	overwrite_head(head, stack);
}
