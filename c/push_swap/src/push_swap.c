/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:13:13 by agrun             #+#    #+#             */
/*   Updated: 2022/12/07 10:13:18 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/*	Checking if the listed numbers are in ascendant order already.		*/

int	check_order(int *a)
{
	int	i;

	i = 0;
	while (a[i] && a[i + 1])
	{
		if (a[i] < a[i + 1])
			i++;
		else
			return (1);
	}
	return (0);
}

/*	Check if stack A requires any sorting, otherwise quit the program.	*/

void	push_swap(int *a)
{
	int	*b;
	int	*head_a;

	if (!check_order(a))
		return ;
	b = malloc(sizeof(int) * (array_size(a) + 1));
	if (!b)
	{
		write(2, "Error\n", 6);
		return ;
	}
	b[0] = 0;
	head_a = malloc(sizeof(int) * (array_size(a) + 1));
	if (!head_a)
	{
		ft_free(&b);
		write(2, "Error\n", 6);
		return ;
	}
	if (array_size(a) <= 5)
		simple_sorting(a, b);
	else
		complex_sorting(a, b, head_a);
	ft_free(&head_a);
	ft_free(&b);
}
