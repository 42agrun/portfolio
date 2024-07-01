/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_operators_1.c  	          	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	check_for_operators_1.c : 1.	*/

static int	possible_operators_2(char *buff_1, int i)
{
	if ((buff_1[i - 1] == '<' && buff_1[i]) && (buff_1[i] != '<'
			&& buff_1[i] != ' ' && buff_1[i] != 9))
	{
		return (ft_return(1, 0));
	}
	else if ((buff_1[i - 1] == '>' && buff_1[i]) && (buff_1[i] != '>'
			&& buff_1[i] != ' ' && buff_1[i] != 9))
	{
		return (ft_return(1, 0));
	}
	else if (buff_1[i - 1] == '|' && buff_1[i] && buff_1[i] != ' '
		&& buff_1[i] != 9)
	{
		return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/*	check_for_operators_1.c : 2.	*/

static int	possible_operators_1(char *buff_1, int i)
{
	if ((buff_1[i] == '<' && buff_1[i - 1]) && (buff_1[i - 1] != '<'
			&& buff_1[i - 1] != ' ' && buff_1[i - 1] != 9))
	{
		return (ft_return(1, 0));
	}
	else if ((buff_1[i] == '>' && buff_1[i - 1]) && (buff_1[i - 1] != '>'
			&& buff_1[i - 1] != ' ' && buff_1[i - 1] != 9))
	{
		return (ft_return(1, 0));
	}
	else if (buff_1[i] == '|' && buff_1[i - 1] && buff_1[i - 1] != ' '
		&& buff_1[i - 1] != 9)
	{
		return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/*	check_for_operators_1.c : 3.	*/

static void	check_spacing_2(char *buff_1, char *buff_2, int i, int j)
{
	int	qm[2];

	buff_1[j] = 0;
	qm[0] = 0;
	qm[1] = 0;
	j = 0;
	while (buff_1[i])
	{
		if (!qm[0] && !qm[1] && possible_operators_2(buff_1, i))
		{
			buff_2[j] = ' ';
			j++;
		}
		else if (check_qm_prompt_flag(buff_1, i, qm))
		{
			buff_2[j] = buff_1[i];
			j++;
			i++;
		}
		buff_2[j] = buff_1[i];
		j++;
		i++;
	}
	buff_2[j] = 0;
}

/*	check_for_operators_1.c : 4.	*/

static void	check_spacing(char *buff_1, char *buff_2, char *str, int i)
{
	int	qm[2];
	int	j;

	j = 0;
	qm[0] = 0;
	qm[1] = 0;
	while (str[i])
	{
		if (check_qm_prompt_flag(str, i, qm))
		{
			buff_1[j] = str[i];
			j++;
			i++;
		}
		if (!qm[0] && !qm[1] && possible_operators_1(str, i))
		{
			buff_1[j] = ' ';
			j++;
		}
		buff_1[j] = str[i];
		j++;
		i++;
	}
	check_spacing_2(buff_1, buff_2, 0, j);
}

/*	check_for_operators_1.c : 5.	*/
/*	Checking if there are any unquoted operators in the prompt, inserting spaces
	in case they're missing between the arguments and commands. This is something
	which bash does, so this behavior is being replicated.

	Changes to the string are saved in both buffers before updating prompt.
	This function will also return (1) if there's an unrecognized command, in that
	case it might be supported by execve. It's important to still print out an
	error if it shouldn't show up.

	Check "utils_5" for "check_command_access".
	Check "check_for_operators_3" for "check_potential_filenames".			*/

int	check_for_operators(char *prompt, char **env, int i, int flag)
{
	int		qm[2];
	char	buff_1[5000];
	char	buff_2[5000];

	i = 0;
	qm[0] = 0;
	qm[1] = 0;
	flag = check_potential_filenames(prompt, flag, 0);
	while (prompt[i] && flag == 0)
	{
		check_qm_prompt_flag(prompt, i, qm);
		if (qm[0] == 0 && qm[1] == 0)
			if (prompt[i] == '>' || prompt[i] == '<' || prompt[i] == '|')
				flag = 1;
		i++;
	}
	if (!flag)
		if (!check_command_access(prompt, env, 0, -1))
			return (ft_return(0, 0));
	buff_1[0] = 0;
	buff_2[0] = 0;
	check_spacing(buff_1, buff_2, prompt, 0);
	conv_prompt_string(prompt, env, buff_1, buff_2);
	return (ft_return(1, 0));
}
