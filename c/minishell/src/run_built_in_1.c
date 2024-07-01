/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:48 by agrun             #+#    #+#             */
/*   Updated: 2023/06/05 10:30:53 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	run_built_in_1.c : 1.	*/
/*	Attention! The stored string will be erased from the static array
	after returning its content, so make sure to either save or use it!

	Mode 1 = PWD
	Mode 2 = ENV								*/

void	run_pwd_env(char **envp, int mode)
{
	char	tmp2[5000];

	if (mode == 1)
	{
		getcwd(tmp2, sizeof(tmp2));
		check_printout(0, tmp2, 0, 0);
		check_printout(0, "\n", 0, 0);
		check_printout(0, NULL, 2, 0);
	}
	else if (mode == 2)
	{
		print_env(envp, 0);
		check_printout(0, "\n", 0, 0);
		check_printout(0, NULL, 2, 0);
	}
}

/*	run_built_in_1.c : 2.	*/
/*	The different modes and what they mean:
	1 = ECHO command
	2 = EXPORT command

	IMPORTANT: IF (!ENVP) => CORRUPTION DETECTED. SHUT DOWN MINISHELL!	*/

char	**run_built_in_echo_export(char **tmp, char **envp, int mode)
{
	char	buffer[5000];

	if (mode == 1)
	{
		rewrite_buffer(tmp, buffer, 1, 5);
		print_echo(buffer, 0, 0, envp);
		check_printout(0, NULL, 2, 0);
		if (!envp)
			return (NULL);
	}
	else if (mode == 2)
	{
		print_export_list(envp, 0);
		check_printout(0, NULL, 2, 0);
	}
	return (envp);
}

/*	run_built_in_1.c : 3.	*/
/*	This function skips the commandpath and checks the commandname.		*/

static int	skip_and_search(char *str, char *ref, int i, int x)
{
	while (str[i] && str[i] != ' ' && str[i] != 9)
		i++;
	while (ref[x])
		x++;
	x--;
	i--;
	while (str[i] && i > -1)
	{
		if (str[i] == ref[x])
			x--;
		if (x == -1)
			return (ft_return (1, 0));
		i--;
	}
	return (ft_return(0, 0));
}

/*	run_built_in_1.c : 4.	*/
/*	Checking if any built-in commands are mentioned in the tmp-array.

	If "EXIT" appears as a command it should be ignored, the original
	bash doesn't even run it if it's embedded within a command chain.

	EXPORT with an argument shouldn't work, neither should UNSET.
	These commands simply get ignored by bash in a command chain.		*/

char	**run_built_in(char **tmp, char **envp)
{
	if (skip_and_search(tmp[0], "echo", 0, 0))
		envp = run_built_in_echo_export(tmp, envp, 1);
	else if (skip_and_search(tmp[0], "export", 0, 0) && !tmp[1])
		envp = run_built_in_echo_export(tmp, envp, 2);
	else if (skip_and_search(tmp[0], "pwd", 0, 0))
		run_pwd_env(envp, 1);
	else if (skip_and_search(tmp[0], "env", 0, 0))
		run_pwd_env(envp, 2);
	if (!envp)
		return (NULL);
	return (envp);
}
