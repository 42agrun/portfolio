/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_commands_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	flag_commands_3.c: 1.	*/

void	extract_last_return(char *bf_1, int *i, int x)
{
	char	itoa_n[5000];

	i[0] += 2;
	itoa_n[0] = 0;
	ft_itoa(ft_return(0, 1), itoa_n);
	while (itoa_n[x])
	{
		bf_1[i[1]] = itoa_n[x];
		i[1]++;
		x++;
	}
	return ;
}

/*	flag_commands_3.c 2.	*/

int	check_flag_conditions(char *s, int *i, int *q)
{
	if (!q[0] && s[i[0]] == '$' && s[i[0] + 1] && s[i[0] + 1] != ' ')
		if (s[i[0] + 1] != 9 && s[i[0] + 1] != '(' && s[i[0] + 1] != ')')
			if (s[i[0] + 1] != '"' && s[i[0] + 1] != 39 && s[i[0] + 1] != '$')
				return (ft_return(1, 0));
	return (ft_return(0, 0));
}
