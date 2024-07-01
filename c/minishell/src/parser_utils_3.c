/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:50:46 by lbaron            #+#    #+#             */
/*   Updated: 2023/06/26 12:50:50 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	parser_utils_3.c: 1.	*/

void	execute_built_in(char **cmd, char **envp, int in_fd, int out_fd)
{
	pid_t	pid;
	char	**env;

	env = envp;
	pid = fork();
	if (pid == -1)
		exit_with_error("fork");
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO && dup2(in_fd, STDIN_FILENO) == -1)
			exit_with_error("dup2_fd_in");
		if (out_fd != STDOUT_FILENO && dup2(out_fd, STDOUT_FILENO) == -1)
			exit_with_error("dup2_fd_out");
		env = run_built_in(cmd, env);
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
}

/*	parser_utils_3.c: 2.	*/

void	execute_command(char **cmd, char **envp, int in_fd, int out_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_with_error("fork");
	if (pid == 0)
	{
		if (ft_strstr(cmd[0], "cat") && (!store_fd_flag(0, 2)
				|| (store_fd_flag(0, 4))) && !cmd[1])
		{
			if (store_fd_flag(0, 4))
				store_fd_flag(0, 3);
			printf("%c", '\0');
			exit(42);
		}
		if (in_fd != STDIN_FILENO && dup2(in_fd, STDIN_FILENO) == -1)
			exit_with_error("dup2_fd_in");
		if (out_fd != STDOUT_FILENO && dup2(out_fd, STDOUT_FILENO) == -1)
			exit_with_error("dup2_fd_out");
		if (execve(cmd[0], cmd, envp) == -1)
			exit_with_error("Execve Fail");
	}
	else
		waitpid(pid, NULL, 0);
}

/*	parser_utils_3.c: 3.	*/

void	select_built_or_exe(char **cmd, char **envp, int in_fd, int out_fd)
{
	if (ft_strstr(cmd[0], "echo") || ft_strstr(cmd[0], "pwd")
		|| ft_strstr(cmd[0], "env") || ft_strstr(cmd[0], "export"))
	{
		store_fd_flag(1, 1);
		execute_built_in(cmd, envp, in_fd, out_fd);
		return ;
	}
	else
	{
		if (check_flaggable_commands(cmd[0], 0, 0))
			store_fd_flag(1, 1);
		else
			store_fd_flag(0, 0);
		execute_command(cmd, envp, in_fd, out_fd);
		return ;
	}
}

/*	parser_utils_3.c: 4.	*/
/*	Mode (0): sets the static int to 0, ready for work.
	Mode (1): receives the forwarded value and stores it.
	Mode (2): returns the stored value.
	Mode (3): stores information about a redirector coming up.
	Mode (4): returns the stored redirector flag value.		*/

int	store_fd_flag(int i, int m)
{
	static int	flag;
	static int	flag_2;

	if (m == 0)
		flag = 0;
	else if (m == 1)
		flag = i;
	else if (m == 2)
		return (ft_return(flag, 0));
	else if (m == 3)
		flag_2 = i;
	else if (m == 4)
		return (ft_return(flag_2, 0));
	return (ft_return(0, 0));
}

/*	parser_utils_3.c: 5.	*/
/*	Only the first 3 keywords (0-2) are potentionally problematic since
	aren't guaranteed to create any output if used on their own!		*/

int	check_flaggable_commands(const char *cmd, int i, int success)
{
	static char	*keywords[] = {"grep", "wc", "cat", "ls", "date", "sort",
		"make", "htop", "top", "whoami", "find", "head", "tail", "diff", NULL};

	while (keywords[i] && success == 0)
	{
		if (ft_strstr(cmd, keywords[i]))
		{
			success = 1;
			break ;
		}
		i++;
	}
	if (success > 0 && i <= 2)
		if (store_fd_flag(0, 2))
			return (ft_return(1, 0));
	if (success > 0 && i > 2)
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}
