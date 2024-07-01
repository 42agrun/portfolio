/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:48 by agrun             #+#    #+#             */
/*   Updated: 2023/06/05 10:30:53 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	run_built_in_2.c : 1.	*/

static int	rewrite_buffer_2(char *buffer)
{
	buffer[0] = 'e';
	buffer[1] = 'c';
	buffer[2] = 'h';
	buffer[3] = 'o';
	buffer[4] = ' ';
	return (0);
}

/*	run_built_in_2.c : 2.	*/
/*	This function joins all strings within the dimensional one into a 
	single one and then forwards the content to the various subfunctions.

	Spaces are added between the various words/tokens if necessary.
	Basically creates a readable string without the filepath in it.
	Mandatory to make the built-in functions work within minishelll's code. */

void	rewrite_buffer(char **tmp, char *buffer, int i, int x)
{
	int	j;

	j = rewrite_buffer_2(buffer);
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			buffer[x] = tmp[i][j];
			x++;
			j++;
		}
		if (tmp[i + 1])
		{
			buffer[x] = ' ';
			x++;
		}
		else
			break ;
		i++;
	}
	buffer[x] = 0;
}
