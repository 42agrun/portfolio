/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/18/03 12:00:36 by agrun             #+#    #+#             */
/*   Updated: 2023/18/03 12:00:39 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/*	Swap the first 2 elements at the top of stack B.			*/

void	sb(int *b)
{
	int	tmp;

	if (!b[0] || !b[1])
		return ;
	tmp = b[0];
	b[0] = b[1];
	b[1] = tmp;
	write(1, "sb\n", 3);
}

/*	Swap the first 2 elements at the top of stack A.			*/

void	sa(int *a)
{
	int	tmp;

	if (!a[0] || !a[1])
		return ;
	tmp = a[0];
	a[0] = a[1];
	a[1] = tmp;
	write(1, "sa\n", 3);
}

/*	Using sa and sb at the same time.
	Swapping the first 2 elements at the top of both stack A & B.		*/

void	ss(int *a, int *b)
{
	sa(a);
	sb(b);
	write(1, "ss\n", 3);
}

/*	Take the first element at the top of A and put it at the top of B.	*/

void	pb(int *a, int *b)
{
	int	tmp;
	int	i;
	int	j;

	if (!a[0])
		return ;
	tmp = a[0];
	a[0] = 0;
	rearrange_stack(a);
	i = array_size(b);
	j = i + 1;
	while (i > -1)
	{
		b[i + 1] = b[i];
		i--;
	}
	b[0] = tmp;
	b[j] = 0;
	write(1, "pb\n", 3);
}

/*	Take the first element at the top of B and put it at the top of A.	*/

void	pa(int *a, int *b)
{
	int	tmp;
	int	i;
	int	j;

	if (!b[0])
		return ;
	tmp = b[0];
	b[0] = 0;
	rearrange_stack(b);
	i = array_size(a);
	j = i + 1;
	while (i > -1)
	{
		a[i + 1] = a[i];
		i--;
	}
	a[0] = tmp;
	a[j] = 0;
	write(1, "pa\n", 3);
}
