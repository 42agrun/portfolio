/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/18/03 12:00:36 by agrun             #+#    #+#             */
/*   Updated: 2023/18/03 12:00:39 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/*	Shift down all elements of stack B by 1.
	The last element becomes the first one.					*/

void	rrb(int *b)
{
	int	tmp;
	int	i;
	int	j;

	j = array_size(b) - 1;
	i = j;
	tmp = b[i];
	while (i >= 0)
	{
		b[i] = b[i - 1];
		i--;
	}
	b[0] = tmp;
	b[j + 1] = 0;
	write(1, "rrb\n", 4);
}

/*	Shift down all elements of stack A by 1.
	The last element becomes the first one.					*/

void	rra(int *a)
{
	int	tmp;
	int	i;
	int	j;

	j = array_size(a) - 1;
	i = j;
	tmp = a[i];
	while (i >= 0)
	{
		a[i] = a[i - 1];
		i--;
	}
	a[0] = tmp;
	a[j + 1] = 0;
	write(1, "rra\n", 4);
}

/*	Perform rra and rrb for both stacks (a & b).
	Their elements get moved down by 1 and the last one becomes first.	*/

void	rrr(int *a, int *b)
{
	if (!a[0] || !b[0])
		return ;
	rra(a);
	rrb(b);
	write(1, "rrr\n", 4);
}

/*	Shift up all elements of stack B by 1.
	The first element becomes the last one.					*/

void	rb(int *b)
{
	int	tmp;
	int	i;

	i = 1;
	tmp = b[0];
	while (b[i])
	{
		b[i] = b[i + 1];
		i++;
	}
	b[i - 1] = tmp;
	b[i] = 0;
	write(1, "rb\n", 3);
}

/*	Shift up all elements of stack A by 1.
	The first element becomes the last one.					*/

void	ra(int *a)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = a[0];
	while (a[i])
	{
		a[i] = a[i + 1];
		i++;
	}
	a[i - 1] = tmp;
	a[i] = 0;
	write(1, "ra\n", 3);
}
