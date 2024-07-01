/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_3.c     	               	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/18/03 12:00:36 by agrun             #+#    #+#             */
/*   Updated: 2023/18/03 12:00:39 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/*	Using ra and rb at the same time.
	Shifting up all elements of both stacks by 1.				*/

void	rr(int *a, int *b)
{
	if (!a[0] || !b[0])
		return ;
	ra(a);
	ra(b);
	write(1, "rr\n", 3);
}

/*	Rearranging the stack after having created zero-bits.			*/

void	rearrange_stack(int *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		s[i - 1] = s[i];
		i++;
	}	
	s[i - 1] = 0;
	s[i] = 0;
}

void	ft_free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	if (array)
		free(array);
	array = NULL;
}

void	ft_free(int **s)
{
	if (*s)
		free(*s);
	*s = NULL;
}

/*	Use this to measure the size of a stack. Useful for setting up buffers.
	Also used to extract the position of the final number within the array.	*/

int	array_size(int *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
