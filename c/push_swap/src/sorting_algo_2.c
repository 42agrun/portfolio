/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algo_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/18/03 12:00:36 by agrun             #+#    #+#             */
/*   Updated: 2023/18/03 12:00:39 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/*	This function only will be used by the simple sorting algorithm.	*/

int	get_min(int *stack, int val)
{
	int	*head;
	int	min;
	int	i;

	head = stack;
	min = head[0];
	i = 0;
	while (head[i] && (i < array_size(stack) - 1))
	{
		i++;
		if (head[i] < min && head[i] != val)
			min = head[i];
	}
	return (min);
}

/*	This function will search out the biggest available value in stack A 
	instead	of the smallest one (unlike the simple sorting method).		
	
	It will return the necessary number of bits required to generate
	the maximum number. Example: [20] = 0001 0100 = first 5 bits required!
				            ---+ ++++				*/

int	get_max_bits(int *head)
{
	int	max;
	int	max_bits;
	int	i;

	i = 0;
	max = head[0];
	max_bits = 0;
	while (head[i])
	{
		if (head[i] > max)
			max = head[i];
		i++;
	}
	while ((max >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

/*	This sorting algorithm will bruteforce through the list, it will not
	give you the shortest answer but it will still be a valid one.
	
	The algorithm is based on "RADIX". This function will gradually check
	the bit-length of each value and rotate the list until the smallest 
	value is at the top of stack A. That value then gets pushed to stack B.
	
	Stack B will be gradually filled up and then pushed back at the end.
	It is imperative to use simplified numbers to speed up the process.
	This is why the integer array "head_a" exists!				*/

void	complex_sorting(int *a, int *b, int *head_a)
{
	int	i;
	int	j;
	int	max_bits;
	int	size;

	i = 0;
	define_head(head_a, a);
	max_bits = get_max_bits(head_a);
	size = array_size(head_a);
	while (i < max_bits)
	{
		j = 0;
		while (j++ < size)
		{
			overwrite_head(head_a, a);
			if (((head_a[0] >> i) & 1) == 1)
				ra(a);
			else
				pb(a, b);
		}
		while (array_size(b) != 0)
			pa(a, b);
		i++;
	}
}

/*	Checking the distance to the smallest available number in stack A.	*/

int	get_distance(int *stack, int index)
{
	int	*head;
	int	distance;
	int	i;

	i = 0;
	distance = 0;
	head = stack;
	while (head[i])
	{
		if (head[i] == index)
			break ;
		distance++;
		i++;
	}
	return (distance);
}
