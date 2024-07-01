/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_6.c: 1.	*/
/*	Will either return (1) or (0) depending if the field is "empty".	*/

int	check_empty_field(char *str, int i)
{
	if (str[i] == 9 || str[i] == ' ' || !str[i])
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}

/*	utils_6.c 2.	*/
/*	Support function for "check_extended_shell" (see shell_commands.c: 3).
	Checks if the reference-string is properly appearing within str.	*/

int	check_correct_input(char *str, char *ref, int i, int j)
{
	i = skip_spaces(str, 0);
	while (str[i])
	{
		if (str[i] != ref[j])
			break ;
		j++;
		i++;
		if (!ref[j])
		{
			if (check_empty_field(str, i))
				return (ft_return(1, 0));
			return (ft_return(0, 0));
		}
	}
	return (ft_return(0, 0));
}

/*	utils_6.c 3.	*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!(dest || src))
		return (NULL);
	d = dest;
	s = src;
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
	{
		d += n -1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}

/*	utils_6.c 4.	*/

void	remove_path(char *str)
{
	int			i;
	char		*keyword_st;
	static char	*keywords[] = {
		"echo", "grep", "wc", "mkdir", "mv", "cp", "rm", "rmdir",
		"touch", "whoami", "find", "head", "tail", "diff", "cat",
		"ls", "date", "touch", "sort", "clear", "env",
		"pwd", "export", "make", "bash", "zsh", "minishell",
		"htop", "top", "awk", NULL};

	i = 0;
	while (keywords[i])
	{
		keyword_st = ft_strstr(str, keywords[i]);
		if (keyword_st && (keyword_st == str || *(keyword_st - 1) == '/'))
		{
			ft_memmove(str, keyword_st, ft_strlen(keyword_st) + 1);
			break ;
		}
		i++;
	}
}

/*	utils_6.c: 5.	*/
/*	Checking if the "export"-command is being used on its own which should
	print out an alternate env-list with "declare -x" at the front.
	
	Check out "run_built_in_2" for the respective function.			*/

int	check_standalone_export(char *str)
{
	int	i;

	if (!ft_find_word(str, "export", 0, 0))
		return (ft_return(0, 0));
	i = skip_spaces(str, 0);
	while (str[i] && str[i] != 't')
		i++;
	i++;
	if (empty_check(str, i))
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}
