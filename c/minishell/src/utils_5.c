/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_5.c: 1.	*/

static void	set_reference_3(char *ref, int i)
{
	if (i == 5)
	{
		ref[0] = 'u';
		ref[1] = 'n';
		ref[2] = 's';
		ref[3] = 'e';
		ref[4] = 't';
		ref[5] = 0;
	}
	if (i == 6)
	{
		ref[0] = 'h';
		ref[1] = 'i';
		ref[2] = 's';
		ref[3] = 't';
		ref[4] = 'o';
		ref[5] = 'r';
		ref[6] = 'y';
		ref[7] = 0;
	}
}

/*	utils_5.c: 2.	*/

static void	set_reference_2(char *ref, int i)
{
	if (i == 3)
	{
		ref[0] = 'e';
		ref[1] = 'c';
		ref[2] = 'h';
		ref[3] = 'o';
		ref[4] = 0;
	}
	else if (i == 4)
	{
		ref[0] = 'e';
		ref[1] = 'x';
		ref[2] = 'p';
		ref[3] = 'o';
		ref[4] = 'r';
		ref[5] = 't';
		ref[6] = 0;
	}
	else if (i > 4)
		set_reference_3(ref, i);
}

/*	utils_5.c: 3.	*/

static void	set_reference(char *ref, int i)
{
	if (i == 0)
	{
		ref[0] = 'p';
		ref[1] = 'w';
		ref[2] = 'd';
		ref[3] = 0;
	}
	else if (i == 1)
	{
		ref[0] = 'e';
		ref[1] = 'n';
		ref[2] = 'v';
		ref[3] = 0;
	}
	else if (i == 2)
	{
		ref[0] = 'c';
		ref[1] = 'd';
		ref[2] = 0;
	}
	else if (i > 2)
		set_reference_2(ref, i);
}

/*	utils_5.c: 4.	*/
/*	This function will check if the command at the start of the string
	is a prebuilt one and only if there's no operator/separator.

	The "exit"-command isn't included here since it already gets tested
	on main before going into this function.				*/

int	check_command_access(char *str, char **env, int i, int j)
{
	char	buff[1024];
	char	ref[1024];
	char	*buffer;
	char	**b_path;
	int		x;

	i = skip_spaces_and_paths(str);
	x = i + 1;
	while (str[++i] && str[i] && str[i] != ' ' && str[i] != 9)
		buff[++j] = str[i];
	buff[j + 1] = 0;
	i = -1;
	while (++i < 7)
	{
		set_reference(ref, i);
		if (ft_find_word(buff, ref, x, 0))
			return (ft_return (0, 0));
	}
	b_path = find_path(env);
	buffer = valid_cmd(b_path, buff);
	if (b_path)
		ft_free_array(b_path);
	if (buffer)
		return (ft_free(&buffer));
	return (ft_return(0, 0));
}

/*	utils_5.c: 5.	*/
/*	Support function for managing the exchange between the user-prompt 
	and the buffer which will store and convert the input for later 
	processing.

	Flags ($EXAMPLE) get replaced at the end and everything written
	into the buf-string originally declared on main.			*/

void	manage_main(char *buf, char *prompt, char **env, int i)
{
	char	buf_2[5000];
	int		j;

	j = -1;
	buf[0] = 0;
	buf_2[0] = 0;
	add_history(prompt);
	i = skip_spaces(prompt, 0);
	while (prompt[i])
	{
		buf_2[++j] = prompt[i];
		i++;
	}
	buf_2[j + 1] = 0;
	convert_all_flags(buf_2, buf, env);
}
