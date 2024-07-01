/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/18/03 12:00:36 by agrun             #+#    #+#             */
/*   Updated: 2023/18/03 12:00:39 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/*	This function got split into two to fit norminette's rules.
	This part of the function only handles the first two values in stack A.	*/

static void	sort_3_ex(int *a, int *head, int min, int next_min)
{
	if (head[0] == min && head[1] != next_min)
	{
		rra(a);
		sa(a);
	}
	else if (head[0] == next_min)
	{
		if (head[1] == min)
			sa(a);
		else
			rra(a);
	}
	else
	{
		if (head[1] == min)
			ra(a);
		else
		{
			sa(a);
			rra(a);
		}
	}
}

/*	Using "next_min" to keep track of the 2nd smallest number. 
	Ensuring that the first two values in stack A will be the smallest. 	*/

static void	sort_3(int *a)
{
	int	*head;
	int	min;
	int	next_min;

	head = a;
	min = get_min(a, 0);
	next_min = get_min(a, min);
	if (!check_order(a))
		return ;
	sort_3_ex(a, head, min, next_min);
}

/*	Checking the list for the next smallest value. The previous smallest 
	one got pushed to stack B earlier and will be put back afterwards.	*/

static void	sort_4(int *a, int *b)
{
	int	distance;

	if (!check_order(a))
		return ;
	distance = get_distance(a, get_min(a, 0));
	if (distance == 1)
		ra(a);
	else if (distance == 2)
	{
		ra(a);
		ra(a);
	}
	else if (distance == 3)
		rra(a);
	if (!check_order(a))
		return ;
	pb(a, b);
	sort_3(a);
	pa(a, b);
}

/*	Extracting the distance to the smallest value in the list for sorting.
	Rotating/pushing the list to get that value to the top.
	
	The min-value "0" serves as a placeholder, it will change however.	*/

void	sort_5(int *a, int *b)
{
	int	distance;

	distance = get_distance(a, get_min(a, 0));
	if (distance == 1)
		ra(a);
	else if (distance == 2)
	{
		ra(a);
		ra(a);
	}
	else if (distance == 3)
	{
		rra(a);
		rra(a);
	}
	else if (distance == 4)
		rra(a);
	if (!check_order(a))
		return ;
	pb(a, b);
	sort_4(a, b);
	pa(a, b);
}

/*	Everything that doesn't require bruteforcing. Simple approach.		*/

void	simple_sorting(int *a, int *b)
{
	int	size;

	size = (array_size(a));
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_3(a);
	else if (size == 4)
		sort_4(a, b);
	else if (size == 5)
		sort_5(a, b);
}
