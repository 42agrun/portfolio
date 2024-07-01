/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-05 23:00:52 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-05 23:00:52 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* access.c: 1.*/

char	**find_path(char **envp)
{
	int		i;
	char	*path;
	char	**path_buf;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path = ft_strstr(envp[i], "/");
	path_buf = ft_split(path, ':');
	return (path_buf);
}

/* access.c: 2.*/

static int	check_built_in_cmd(char *cmd)
{
	static char	ref[] = {"export"};
	int			i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ref[i])
			i++;
		else
			break ;
		if (!ref[i])
			return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/* access.c: 3.*/

char	*valid_cmd(char **path, char *cmd)
{
	int		i;
	char	*correct_path;

	i = 0;
	if (check_built_in_cmd(cmd))
		return ("/usr/bin/export");
	if (path == NULL)
	{
		return (NULL);
	}
	while (path[i])
	{
		correct_path = join_strings(path[i], "/", cmd);
		if (access(correct_path, X_OK) == 0)
		{
			return (correct_path);
		}
		else
		{
			free(correct_path);
		}
		i++;
	}
	return (NULL);
}

/* access.c: 4.*/

void	valid_for_lexing(char *buf)
{
	int	i;

	i = skip_spaces(buf, 0);
	if (buf[i] == '/')
	{
		if (is_valid_command(buf) == 1)
		{
			return ;
		}
	}
	remove_path(buf);
}

/* access.c: 5.*/

void	lexer_parcer(char *buf, char **env, t_token *head)
{
	valid_for_lexing(buf);
	head = create_token_list(buf, head);
	parser(env, head);
	head = NULL;
}
