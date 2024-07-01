/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_4.c	                	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	export_unset_4.c : 1.	*/

static void	restore_array(char **str, int i, int j)
{
	while (str[j])
		j++;
	while (str[j])
	{
		i++;
		while (str[j][i])
			i++;
		while (str[j][i] && i > -1)
		{
			str[j][i] = 'a';
			i--;
		}
		i = 0;
		j--;
	}
}

/*	export_unset_4.c : 2.	*/

void	sort_by_alpha(char **buf, char **buf2, int *x, char **ref)
{
	while (ref[0][x[3]])
	{
		while (buf2[x[0]])
		{
			x[1] = 0;
			if (buf2[x[0]][x[1]] == ref[0][x[3]]
				|| buf2[x[0]][x[1]] == ref[1][x[3]])
			{
				while (buf2[x[0]][x[1]])
				{
					buf[x[2]][x[1]] = buf2[x[0]][x[1]];
					x[1]++;
				}
				buf[x[2]][x[1]] = 0;
				buf2[x[0]][0] = 0;
				x[2]++;
			}
			x[0]++;
		}
		x[0] = 0;
		x[3]++;
	}
	buf[x[2]][0] = 0;
	restore_array(buf2, 0, 0);
}

/*	export_unset_4.c : 3.	*/

char	*add_new_export_str(char *ref, int i, int j, int flag)
{
	char	*str;

	while (ref[i])
		i++;
	str = malloc(sizeof(char) * (i + 3));
	if (!str)
		return (NULL);
	i = 0;
	while (ref[j])
	{
		if (!flag && i > 0 && ref[j - 1] == '=')
		{
			str[i] = '"';
			i++;
			flag = 1;
		}
		str[i] = ref[j];
		i++;
		j++;
	}
	str[i] = '"';
	str[i + 1] = 0;
	return (str);
}

/*	export_unset_4.c : 4.	*/

static char	**sort_by_alphabetic_order(char **env, char **ref)
{
	char	**buf;
	char	**buf2;
	int		i;
	int		x[5];

	x[0] = 0;
	x[1] = 0;
	x[2] = 0;
	x[3] = 0;
	buf2 = copy_env(env, 0, 1);
	buf = malloc(sizeof(char *) * (ft_array_len(buf2) + 1));
	i = 0;
	while (i < ft_array_len(buf2))
	{
		buf[i] = malloc(sizeof(char) * (3000));
		i++;
	}
	buf[i] = 0;
	sort_by_alpha(buf, buf2, x, ref);
	ft_free_array(buf2);
	return (buf);
}

/*	export_unset_4.c : 5.	*/
/*	The n-variable is there to determine if a newline should be printed
	at the end or not. Context relies on usage, for instance during echo.	

	This function behaves like "print_env" with the sole difference that
	it adds "declare -x" to the front of each entry.			*/

void	print_export_list(char **env, int n)
{
	static char	*ref[] = {"abcdefghijklmnopqrstuvwxyz",
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ", NULL};
	char		**buf;
	int			i;

	buf = sort_by_alphabetic_order(env, ref);
	i = 0;
	while (buf[i][0])
	{
		check_printout(0, "declare -x ", 0, 0);
		check_printout(0, buf[i], 0, 0);
		if (n == 0)
			check_printout(0, "\n", 0, 0);
		i++;
	}
	ft_free_array(buf);
}
