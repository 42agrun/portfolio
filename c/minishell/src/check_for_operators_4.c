/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_operators_4.c  	          	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	check_for_operators_4.c : 1.	*/
/*	Mainly used to save lines on "conv_prompt_string" (check_for_op_2).
	Lets the superior function know that it needs to convert something.	*/

int	check_prompt_prefix(char *str, int *i, int *qm)
{
	int	x;

	x = i[0];
	if (str[x] == '$' && !qm[0] && str[x + 1]
		&& str[x + 1] != ' ' && str[x + 1] != 9
		&& str[x + 1] != '"' && str[x + 1] != 39)
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}

/*	check_for_operators_4.c : 2.	*/

static void	add_declare_x_prefix(char *dst, char *ref, int *i)
{
	int	x;

	x = 0;
	while (ref[x])
	{
		dst[i[1]] = ref[x];
		i[1]++;
		x++;
	}
}

/*	check_for_operators_4.c : 3.	*/

static void	extract_prompt_env(char *dst, char **env, int *i, int mode)
{
	int	x;
	int	j;

	x = 0;
	while (env[x])
	{
		j = 0;
		if (mode == 1)
			add_declare_x_prefix(dst, "declare -x ", i);
		while (env[x][j])
		{
			dst[i[1]] = env[x][j];
			i[1]++;
			j++;
		}
		dst[i[1]] = ' ';
		i[1]++;
		x++;
	}
}

/*	check_for_operators_4.c : 4.	*/

static int	insert_prompt_cmd(char *dst, char *src, int *i, char **env)
{
	char	buffer[5000];
	int		x;

	x = i[0];
	buffer[0] = 0;
	while (src[x] && src[x] != ')')
		x++;
	if (src[x - 1] == 'd')
	{
		getcwd(buffer, sizeof(buffer));
		x = -1;
		while (buffer[++x])
		{
			dst[i[1]] = buffer[x];
			i[1]++;
		}
	}
	else if (src[x - 1] == 'v')
		extract_prompt_env(dst, env, i, 0);
	else if (src[x - 1] == 't')
		extract_prompt_env(dst, env, i, 1);
	while (src[i[0]] && src[i[0] - 1] != ')')
		i[0]++;
	return (ft_return(1, 0));
}

/*	check_for_operators_4.c : 5.	*/
/*	This function checks for three particular commands,
	PWD, ENV & EXPORT. They must be embedded like this: $(CMD).

	In that case this token needs to be converted into their
	respective contents while omitting newline-bytes.			*/

int	check_prompt_cmd(char *dst, char *str, int *i, char **env)
{
	int	x;

	x = i[0];
	if (str[x] != '$' && str[x + 1] != '(')
		return (ft_return(0, 0));
	if (str[x + 2] == 'p' && str[x + 3] == 'w'
		&& str[x + 4] == 'd' && str[x + 5] == ')')
		x = 4242;
	else if (str[x + 2] == 'e' && str[x + 3] == 'n'
		&& str[x + 4] == 'v' && str[x + 5] == ')')
		x = 4242;
	else if (str[x + 2] == 'e' && str[x + 3] == 'x'
		&& str[x + 4] == 'p' && str[x + 5] == 'o'
		&& str[x + 6] == 'r' && str[x + 7] == 't'
		&& str[x + 8] == ')')
		x = 4242;
	if (x != 4242)
		return (ft_return(0, 0));
	return (insert_prompt_cmd(dst, str, i, env));
}
