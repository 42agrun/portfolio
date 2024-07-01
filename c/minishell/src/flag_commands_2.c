/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_commands_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	flag_commands_2.c: 1.	*/
/*	You need to convert the flags into whatever content they have within 
	the env array. Also make sure to hide unknown flags!
	e.g.: $TEST => (nothing), not even an error.

	Remember, if a known flag is being used on its own you need to display
	an error, for example: $USER => "Command 'root' not found"		*/

static void	convert_flag(char *buf, char **env, int i, int hide_e)
{
	int		x;
	int		j;

	j = 0;
	x = -1;
	while (env[i][j] != '=')
		j++;
	if (env[i][j + 1] == '"')
		j++;
	while (env[i][++j])
		buf[++x] = env[i][j];
	if (buf[x] == '"')
		x--;
	buf[x + 1] = 0;
	if (hide_e == 0)
		e_print(buf, 0, 0, 2);
	else if (hide_e == 1 && buf[0])
	{
		check_printout(0, buf, 0, 0);
		check_printout(' ', NULL, 0, 0);
	}
	else if (hide_e == 2 && buf[0])
		check_printout(0, buf, 0, 0);
}

/*	flag_commands_2.c: 2.	*/
/*	Checking the env-array if the flag is in there. Displaying if yes.
	Hiding double quotation marks at the start and end of flag.		*/

int	display_found_flag(char *buf, char **env, int flag, int hide_e)
{
	int	i;
	int	j;

	i = -1;
	if (buf[0] == 0)
		return (ft_return(0, 0));
	while (env[++i] && flag == -1)
	{
		j = 0;
		while (env[i][j] && env[i][j] == buf[j])
			j++;
		if (!buf[j] && env[i][j] == '=')
			flag = i;
	}
	if (flag == -1)
		return (ft_return(0, 0));
	i = flag;
	convert_flag(buf, env, i, hide_e);
	return (ft_return(1, 0));
}

/*	flag_commands_3.c: 3.	*/
/*	If a flag has single quotation marks, it is imperative to keep the
	single quotes as well. They will be displayed in the error message
	later on main along with the unconverted (!) flagname.			*/

static void	write_into_byte(char *s, char *b, int *i, int *q)
{
	static int	flag;

	if (!q[1] && s[i[0]] == 39 && s[i[0] + 1] == '$' && flag != 4242)
	{
		(void)q;
		flag = 4242;
	}
	else if (s[i[0]] == 39 && flag == 4242)
		flag = 42;
	else if (!q[1] && s[i[0]] == 39 && !check_echo_prefix(s))
	{
		i[0]++;
		return ;
	}
	b[i[1]] = s[i[0]];
	i[1]++;
	i[0]++;
}

/*	flag_commands_3.c: 4.	*/

static void	forward_through_string(char *b, char *s, char **env, int *i)
{
	replace_found_flag(b, s, env, i);
	if (s[i[0]] == '$')
		i[0]++;
	while (s[i[0]] && s[i[0]] != ' ' && s[i[0]] != 9
		&& s[i[0]] != '$' && s[i[0]] != '"' && s[i[0]] != 39)
		i[0]++;
}

/*	flag_commands_3.c: 5.	*/
/*	This function is used during the initial conversion of the string to
	deal with (multiple) flags in the command line.

	Look up "flag_commands_3.c" for "check_flag_conditions".		*/

void	convert_all_flags(char *s, char *b, char **env)
{
	int	i[3];
	int	q[3];

	q[0] = 0;
	q[1] = 0;
	i[0] = 0;
	i[1] = 0;
	while (s[i[0]])
	{
		if (check_qm_prompt_flag(s, i[0], q))
			write_into_byte(s, b, i, q);
		else if (check_flag_conditions(s, i, q))
		{
			if (s[i[0] + 1] == '?')
				extract_last_return(b, i, 0);
			else
				forward_through_string(b, s, env, i);
		}
		else
			write_into_byte(s, b, i, q);
	}
	b[i[1]] = 0;
}
