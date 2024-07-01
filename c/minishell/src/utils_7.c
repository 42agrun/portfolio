/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-28 22:05:07 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-28 22:05:07 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_7.c.: 1.	*/

size_t	ft_strcspn(const char *str, const char *reject)
{
	const char	*p;
	const char	*q;

	p = str;
	while (*p)
	{
		q = reject;
		while (*q)
		{
			if (*p == *q)
			{
				return ((size_t)(p - str));
			}
			++q;
		}
		++p;
	}
	return ((size_t)(p - str));
}

/*	utils_7.c.: 2.	*/

char	*ft_strcpy(char *dest, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

/*	utils_7.c.: 3.	*/

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	ft_memcpy(dest + dest_len, src, src_len + 1);
	return (dest);
}

/*	utils_7.c.: 4.	*/

void	handle_command(t_valid *v, char *str)
{
	v->com_len = ft_strcspn(v->com_s, " \t\n");
	v->com = malloc((v->com_len + 1) * sizeof(char));
	ft_strncpy(v->com, v->com_s, v->com_len);
	v->com[v->com_len] = '\0';
	v->path = malloc((v->com_s - str + 1) * sizeof(char));
	ft_strncpy(v->path, str, v->com_s - str);
	v->path[v->com_s - str] = '\0';
	v->full = malloc((v->com_s - str + strlen(v->com) + 1) * sizeof(char));
	ft_strcpy(v->full, v->path);
	ft_strcat(v->full, v->com);
	v->result = access(v->full, X_OK);
	free(v->com);
	free(v->path);
	free(v->full);
}

/*	utils_7.c.: 5.	*/

int	is_valid_command(char *str)
{
	t_valid		v;
	static char	*keywords[] = {
		"cd", "echo", "grep", "wc", "mkdir", "mv", "cp", "rm", "rmdir",
		"touch", "whoami", "find", "head", "tail", "diff", "cat",
		"ls", "date", "touch", "sort", "clear", "env",
		"pwd", "export", "make", "bash", "zsh", "minishell", "htop",
		"top", "awk", NULL};

	v.i = 0;
	while (keywords[v.i])
	{
		v.com_s = ft_strstr(str, keywords[v.i]);
		if (v.com_s && (v.com_s == str || *(v.com_s - 1) == '/'))
		{
			handle_command(&v, str);
			if (v.result == 0)
				return (0);
			break ;
		}
		v.i++;
	}
	return (ft_return(1, 0));
}
