/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_printout_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	check_printout_2.c: 1.	*/

static void	complex_errors_3(char *buf, char *str, int extra, int i)
{
	if (extra == 6)
	{
		apply_string(buf, "minishell: cd: ", i);
		while (buf[i])
			i++;
		apply_string(buf, str, i);
		while (buf[i])
			i++;
		apply_string(buf, ": Not a directory\n", i);
	}
	if (extra == 7)
	{
		apply_string(buf, "minishell: syntax error near unexpected token `", i);
		while (buf[i])
			i++;
		apply_string(buf, str, i);
		while (buf[i])
			i++;
		apply_string(buf, "'\n", i);
	}
}

/*	check_printout_2.c: 2.	*/

static void	complex_errors_2(char *buf, char *str, int extra, int i)
{
	if (extra == 3 || extra == 4)
	{
		apply_string(buf, "minishell: ", i);
		while (buf[i])
			i++;
		apply_string(buf, str, i);
		while (buf[i])
			i++;
		if (extra == 3)
			apply_string(buf, " : No such file or directory\n", i);
		else
			apply_string(buf, " : Is a directory\n", i);
	}
	if (extra == 5)
	{
		apply_string(buf, str, i);
		while (buf[i])
			i++;
		apply_string(buf, ": command not found\n", i);
	}
	if (extra > 5)
		complex_errors_3(buf, str, extra, i);
}

/*	check_printout_2.c: 3.	*/
/*	This function exists to circumvent line limits on other functions, 
	also to combine the error message with another string.			*/

void	complex_errors(char *buf, char *str, int extra, int i)
{
	if (extra == 1)
	{
		apply_string(buf, "minishell: syntax error near unexpected token `", i);
		while (buf[i])
			i++;
		apply_string(buf, str, i);
		while (buf[i])
			i++;
		apply_string(buf, "'\n", i);
	}
	else if (extra == 2)
	{
		apply_string(buf, "Command '", i);
		while (buf[i])
			i++;
		apply_string(buf, str, i);
		while (buf[i])
			i++;
		apply_string(buf, "' not found\n", i);
	}
	else if (extra > 2)
		complex_errors_2(buf, str, extra, i);
}
