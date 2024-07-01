/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_1.c: 1.	*/
/*	The n-variable is there to determine if a newline should be printed
	at the end or not. Context relies on usage, for instance during echo.	*/

void	print_env(char **env, int n)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!env[i + 1])
			check_printout(0, env[i], 0, 0);
		else
		{
			check_printout(0, env[i], 0, 0);
			check_printout(' ', NULL, 0, 0);
		}
		if (n == 1)
			check_printout(0, "\n", 0, 0);
		else if (n == 2)
		{
			if (env[i + 1])
				check_printout(0, "\n", 0, 0);
		}
	}
}

/*	utils_1.c: 2.	*/
/*	It is essential to skip through any spaces if there are any between
	the command and an option (-c or -n), the original commands allow this!	

	Check out shell_commands.c: 3 for "check_extended_shell".		*/

int	ft_strncmp(char *ref, char *input, int i, int j)
{
	i = skip_spaces(input, i);
	while (input[i])
	{
		if (input[i] == ref[j])
		{
			j++;
			i++;
		}
		else
			return (ft_return(0, 0));
		if (!ref[j])
			break ;
		if (input[i - 1] == ' ' && (input[i] == ' ' || input[i] == 9))
			i = skip_spaces(input, i);
	}
	if (ref[j])
		return (ft_return(0, 0));
	if (check_extended_shell(ref, input, 0))
		return (ft_return(1, 0));
	i = skip_spaces(input, i);
	if (input[i] != 0)
		return (ft_return(0, 0));
	return (ft_return(1, 0));
}

/*	utils_1.c: 3.	*/
/*	Making sure the rest of the input/line contains no further characters.	*/

int	empty_check(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == 9)
			i++;
		else
			return (ft_return(0, 0));
	}
	return (ft_return(1, 0));
}

/*	utils_1.c: 4.	*/

int	ft_exit(char *str, char **env)
{
	if (!str || ft_strncmp("exit", str, 0, 0))
	{
		rl_clear_history();
		if (str != NULL)
			ft_free(&str);
		ft_free_array(env);
		return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/*	utils_1.c: 5.	*/
/*	This function needs to be extended to include free-instructions
	for the struct we've yet to implement. Shut down minishell if
	malloc fails.								*/

int	ft_error(int error, char *prompt, char **env)
{
	write (2, "Error\n", 6);
	if (error == 1)
		write (2, "Malloc failed.\n", 15);
	rl_clear_history();
	if (prompt)
		ft_free(&prompt);
	if (env[0])
		ft_free_array(env);
	return (ft_return(1, 0));
}
