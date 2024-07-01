/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_operators_2.c  	          	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	check_for_operators_2.c : 1.	*/

static void	convert_prompt_flag(char *buf, char **env, int flag, int *i)
{
	int		j;

	j = 0;
	while (env[flag][j] != '=')
		j++;
	j++;
	if (env[flag][j] == '"')
		j++;
	while (env[flag][j] && env[flag][j] != '"')
	{
		buf[i[1]] = env[flag][j];
		i[1]++;
		j++;
	}
}
/*	check_for_operators_2.c : 2.	*/

static int	search_prompt_flag(char *buf, char **env, int flag)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i] && flag == -1)
	{
		j = 0;
		while (env[i][j] && env[i][j] == buf[j])
			j++;
		if (!buf[j] && env[i][j] == '=')
			flag = i;
	}
	if (flag == -1)
		return (ft_return(flag, 0));
	i = flag;
	return (ft_return(i, 0));
}

/*	check_for_operators_2.c : 3.	*/

void	replace_found_flag(char *buff_1, char *buff_2, char **env, int *i)
{
	char	buff_3[5000];
	int		flag;
	int		x;
	int		y;

	if (buff_2[i[0]] == '$' && buff_2[i[0] + 1] == '?')
	{
		extract_last_return_value(buff_1, buff_2, i, 0);
		return ;
	}
	x = i[0] + 1;
	y = 0;
	while (buff_2[x] && buff_2[x] != ' ' && buff_2[x] != 9
		&& buff_2[x] != '"' && buff_2[x] != '$')
	{
		buff_3[y] = buff_2[x];
		y++;
		x++;
	}
	buff_3[y] = 0;
	flag = search_prompt_flag(buff_3, env, -1);
	if (flag != -1)
		convert_prompt_flag(buff_1, env, flag, i);
}

/*	check_for_operators_2.c : 4.	*/

static int	check_for_single_qms(char *buff_2, char *buff_1, int *i, int *qm)
{
	if (!qm[1] && buff_2[i[0]] == 39)
	{
		if (qm[0] == 0)
			qm[0] = 1;
		else
			qm[0] = 0;
		buff_1[i[1]] = buff_2[i[0]];
		i[1]++;
		return (ft_return(1, 0));
	}
	else if (!qm[0] && buff_2[i[0]] == '"')
	{
		if (qm[1] == 0)
			qm[1] = 1;
		else
			qm[1] = 0;
		return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/*	check_for_operators_2.c : 5.	*/
/*	Only single quotation marks can ignore flags, otherwise convert them.
	If they do not appear in the envp, erase them from the string.

	Double quotation marks get hidden if they're not within single quotes.
	Make sure to check if qm[0] => (') is enabled or not!

	Flags within double quotation marks still get displayed, the QMs
	themselves get erased if they embed solely the flag ($).

	There will be at least one additional space which should be ignored
	during the parsing process. Example: echo $UNKNOWN | grep ...		
						  => echo  | grep		*/

void	conv_prompt_string(char *str, char **env, char *bf_1, char *bf_2)
{
	int	qm[3];
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	qm[0] = 0;
	qm[1] = 0;
	while (bf_2[i[0]])
	{
		if (check_for_single_qms(bf_2, bf_1, i, qm))
			i[0]++;
		else if (!qm[0] && check_prompt_cmd(bf_1, bf_2, i, env))
			(void)env;
		else if (check_prompt_prefix(bf_2, i, qm))
		{
			replace_found_flag(bf_1, bf_2, env, i);
			i[0]++;
			while (bf_2[i[0]] && bf_2[i[0]] != ' '
				&& bf_2[i[0]] != 9 && bf_2[i[0]] != '$')
				i[0]++;
		}
		else 
			skip_through_string(bf_1, bf_2, i, qm);
	}
	final_conversion(str, bf_1, i);
}
