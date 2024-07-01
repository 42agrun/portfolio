/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_commands_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	flag_commands_1.c: 1.	*/

static void	extracting_dollar_flags(char *buf, char *str, int *i)
{
	int	x;
	int	y;
	int	z;

	x = i[0];
	if (str[i[0]] == '$')
		i[0]++;
	while (str[i[0]])
	{
		if (str[i[0]] == ' ' || str[i[0]] == 9 || str[i[0]] == '$')
			break ;
		i[0]++;
	}
	y = i[0] - 1;
	z = -1;
	while (++x <= y)
		buf[++z] = str[x];
	buf[z + 1] = 0;
}

/*	flag_commands_1.c: 2.	*/

static void	found_flag_command(char *str, char **env, int *i, int hide_e)
{
	char	buf[5000];

	extracting_dollar_flags(buf, str, i);
	display_found_flag(buf, env, -1, hide_e);
}

/*	flag_commands_1.c: 3.	*/
/*	Checking for single/double-quotation makes as well as brackets.		*/

void	skip_quotes_and_brackets(char *str, int *flag, int *i, int n)
{
	char	m;

	if (n == 0)
		m = 39;
	else if (n == 1)
		m = '"';
	else
		m = '(';
	if (str[i[0]] == m)
	{
		if (str[i[0]] == '(')
			m = ')';
		flag[n] = 1;
		while (str[i[0]] && str[i[0]] != m)
		{
			if (str[i[0]] == m)
			{
				flag[n] = 0;
				break ;
			}
			i[0]++;
		}
	}
}

/*	flag_commands_1.c: 4.	*/

static void	set_flag_variables(int *flag, int *i)
{
	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	i[0] = 0;
}

/*	flag_commands_1.c: 5.	*/
/*	Checking for anything with a dollar-sign in front of it.
	Usually this refers to content within envp, this also includes
	custom-set flags created via the export-command. Check for those!

	It is important to check for quotation marks and brackets, they are
	against the supported format of flags.

	The export-command without any further input should only print out the
	current version of env - respect custom additions done via "export"!

	If the hide_error flag is set to 0, only one flag has to be converted.
	It'll be displayed in a custom error message afterwards.		*/

int	check_flag_commands(char *str, char **env, int hide_e)
{
	int		flag[4];
	int		i[2];
	int		r;

	r = 0;
	if (check_echo_prefix(str) || ft_find_word(str, "$(", 0, 0)
		||ft_find_word(str, "$?", 0, 0))
		return (ft_return(r, 0));
	set_flag_variables(flag, i);
	while (str[i[0]])
	{
		skip_quotes_and_brackets(str, flag, i, 0);
		skip_quotes_and_brackets(str, flag, i, 1);
		skip_quotes_and_brackets(str, flag, i, 2);
		if (str[i[0]] == '$' && flag[0] == 0 && flag[1] == 0 && flag[2] == 0)
		{
			found_flag_command(str, env, i, hide_e);
			r = 1;
		}
		if (!hide_e && r == 1 && str[i[0]] != '$')
			break ;
		i[0]++;
	}
	return (ft_return(r, 0));
}
