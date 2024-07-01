/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_operators_3.c  	          	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	check_for_operators_3.c : 1.	*/

void	final_conversion(char *prompt, char *buf, int *i)
{
	buf[i[1]] = 0;
	i[0] = 0;
	i[1] = 0;
	while (buf[i[0]])
	{
		prompt[i[1]] = buf[i[1]];
		i[1]++;
		i[0]++;
	}
	prompt[i[1]] = 0;
}

/*	check_for_operators_3.c : 2.	*/

void	skip_through_string(char *buff_1, char *buff_2, int *i, int *q)
{
	if ((buff_2[i[0]] == '$' && buff_2[i[0] + 1] == '"' && !q[1])
		|| (buff_2[i[0]] == '$' && buff_2[i[0] + 1] == 39 && !q[0]))
		i[0]++;
	else
	{
		buff_1[i[1]] = buff_2[i[0]];
		i[1]++;
		i[0]++;
	}
}

/*	check_for_operator_4.c : 3.	*/

void	extract_last_return_value(char *bf_1, char *bf_2, int *i, int x)
{
	char	itoa_n[5000];

	i[0] += 2;
	ft_itoa(ft_return(0, 1), itoa_n);
	while (itoa_n[x])
	{
		bf_1[i[1]] = itoa_n[x];
		i[1]++;
		x++;
	}
	while (bf_2[i[0]] && bf_2[i[0]] != ' ' && bf_2[i[0]] != 9
		&& bf_2[i[0]] != '$')
	{
		bf_1[i[1]] = bf_2[i[0]];
		i[1]++;
		i[0]++;
	}
	return ;
}

/*	check_for_operators_3.c : 4.	*/
/*	This function keeps track of quotation marks (single and double)
	to enable the recognition of unquoted separators.			*/

int	check_qm_prompt_flag(char *prompt, int i, int *qm)
{
	if (prompt[i] == 39)
	{
		if (qm[0] == 0 && qm[1] == 0)
			qm[0] = 1;
		else if (qm[0] == 1 && qm[1] == 0)
			qm[0] = 0;
		return (ft_return(1, 0));
	}
	else if (prompt[i] == '"')
	{
		if (qm[0] == 0 && qm[1] == 0)
			qm[1] = 1;
		else if (qm[0] == 0 && qm[1] == 1)
			qm[1] = 0;
		return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/*	check_for_operators_3.c : 5.	*/
/*	This function checks if the input contains a potential filename
	(either existing or yet to be created), in that instance it'd be 
	reasonable to return (1) to enable further processing by execve.	*/

int	check_potential_filenames(char *str, int flag, int i)
{
	while (str[i] && str[i] != ' ' && str[i] != 9)
	{
		if (str[i] == '.' && str[i - 1] && str[i - 1] != ' '
			&& str[i - 1] != 9 && str[i + 1]
			&& str[i + 1] != 9 && str[i + 1] != ' ')
			return (ft_return (1, 0));
		i++;
	}
	return (ft_return(flag, 0));
}
