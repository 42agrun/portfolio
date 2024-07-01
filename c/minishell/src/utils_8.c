/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_8.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_8.c: 1.	*/
/*	This function skips any relative or absolute path and returns the
	position of the first character after the last found slash in a word.

	A word is defined by being cut off by a space or horizontal tab.
	A flag will only be returned if the slash is neither at the start
	or end of the token.							*/

int	skip_command_paths(char *str, int i)
{
	int	x;

	x = i;
	while (str[i] && str[i] != ' ' && str[i] != 9)
		i++;
	i--;
	while (str[i])
	{
		if (str[i] == '/')
		{
			x = i + 1;
			break ;
		}
		i--;
	}
	return (ft_return(x, 0));
}

/*	utils_8.c: 2.	*/

int	skip_spaces_and_paths(char *str)
{
	int	i;

	i = 0;
	i = skip_spaces(str, i);
	i = skip_command_paths(str, i) - 1;
	return (ft_return(i, 0));
}
