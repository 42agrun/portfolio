/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_4.c: 1.	*/
/*	Look up echo_2 for context. This is mainly used to shorten the number
	of used lines on the handle_dollar_sign function.

	This function gets used if you encounter a ($)-sign.
	Always print single ($)-signs, no matter what. Return (4) for that.	*/

int	check_alpha_num(char *echo, int *i, int *q)
{
	int	flag;

	flag = 0;
	if (!q[0] && q[1] && echo[i[0] + 1] == '"')
		return (ft_return(4, 0));
	else if (echo[i[0] + 1] == ' ' || echo[i[0] + 1] == 9 || !echo[i[0] + 1])
		return (ft_return(4, 0));
	else if (echo[i[0] + 1] >= '0' && echo[i[0] + 1] <= '9')
		flag = 1;
	else if (echo[i[0] + 1] >= 'A' && echo[i[0] + 1] <= 'Z')
		flag = 1;
	else if (echo[i[0] + 1] >= 'a' && echo[i[0] + 1] <= 'z')
		flag = 1;
	return (ft_return(flag, 0));
}

/*	utils_4.c: 2.	*/
/*	This makes sure that the whole input will be displayed, for instance:
	$?a -> [last returned value]a -> "0a" (as an example).

	The error-message ("Command not found") only refers to the first word
	and will omit the rest of the string, this is normal behavior.		*/

void	adjust_flag_string(char *str, char *buf, int i)
{
	int	x;
	int	flag;

	x = 0;
	i = skip_spaces(str, i);
	flag = 0;
	if (str[i] == '"')
		flag = 1;
	else if (str[i] == 39)
		flag = 2;
	if (flag > 0)
		i++;
	while (str[i])
	{
		if (flag == 1 && str[i] == '"')
			break ;
		else if (flag == 2 && str[i] == 39)
			break ;
		else if (flag == 0 && (str[i] == ' ' || str[i] == 9))
			break ;
		buf[x] = str[i];
		x++;
		i++;
	}
	buf[x] = 0;
}

/*	utils_4.c: 3.	*/
/*	Using the $? command returns the latest received exit value.
	The input "$?a" should display "1a" for example.
	The command used on its own will return an error however.		*/

int	check_qm_prompt(char *str, int hide_error)
{
	char	buf[1024];
	char	itoa_n[1024];
	int		i;

	if (ft_find_word(str, "$?", 0, 0))
	{
		ft_itoa(ft_return(0, 1), itoa_n);
		i = skip_spaces(str, 0);
		if (str[i] == '$' && str[i + 1] == '?')
			i += 2;
		adjust_flag_string(str, buf, i);
		if (hide_error == 0)
		{
			e_print(itoa_n, 0, 0, 0);
			e_print(buf, 0, 0, 5);
		}
		else
		{
			check_printout(0, itoa_n, 0, 0);
			check_printout(0, buf, 0, 0);
		}
		return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/*	utils_4.c: 4.	*/
/*	This function will only skip flags if they're properly formatted,
	else the original i-value will be returned to avoid complications.	*/

int	skip_flags(char *str, int i)
{
	int	j;

	j = i;
	if (str[j] == '$' && str[j + 1] == '(')
	{
		j++;
		while (str[j] && str[j] != ')')
		{
			if (str[j] == '$' || str[j] == '(')
				return (i);
			else
				j++;
		}
		if (str[j] == ')')
			return (j + 1);
		return (i);
	}
	return (i);
}

/*	utils_4.c: 5.	*/

int	skip_spaces(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == 9))
		i++;
	return (ft_return(i, 0));
}
