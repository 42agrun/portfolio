/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-24 09:55:19 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-24 09:55:19 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	parser.c: 1.	*/
/*	this function is responsible to
 * redirect the fd to its respective end function	*/

void	handle_redirection(t_command *c, int *in_fd, int *out_fd)
{
	if (c->nx && c->nx->sep)
	{
		store_fd_flag(1, 3);
		store_fd_flag(1, 1);
		if (strcmp(c->nx->sep, ">") == 0 && c->nx->nx && c->nx->nx->arg)
			redirect_stdout_to_file(c->nx->nx->arg, out_fd);
		else if (strcmp(c->nx->sep, "<") == 0 && c->nx->nx && c->nx->nx->arg)
			redirect_stdin_from_file(c->nx->nx->arg, in_fd);
		else if (strcmp(c->nx->sep, ">>") == 0 && c->nx->nx && c->nx->nx->arg)
			append_stdout_to_file(c->nx->nx->arg, out_fd);
		else if (strcmp(c->nx->sep, "<<") == 0 && c->nx->nx && c->nx->nx->arg)
		{
			store_fd_flag(0, 3);
			read_stdin_from_string(c->nx->nx->arg, in_fd);
		}
	}
}

/*	the function tree is responsible for redirect the commands to
 * its respective
 * execution function, it iterates over the linked lists of t_commands
 * structs and
 * detect if the sep is '|' it executes the next command on next
 * node if not
 * it send the output of the last command to the handle redirection
 * function that
 * use the other seps to determine which function will be used
 * depending on
 * the which token it will find, it is also responsible to open/parse
 * and close the
 * fd properly
 * */

/*	parser.c: 2.	*/

void	close_and_update_fds(int *in_fd, int *out_fd, int *pipefd)
{
	close(*out_fd);
	*in_fd = pipefd[0];
}

/*	parser.c: 3.	*/

void	pipe_and_update_out_fd(int *out_fd, int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("Pipe fail");
		exit(EXIT_FAILURE);
	}
	*out_fd = pipefd[1];
}

/*	parser.c: 4.	*/

void	tree(t_command *commands, char **envp)
{
	t_data		v;

	v.cur = commands;
	v.in_fd = STDIN_FILENO;
	while (v.cur != NULL)
	{
		if (v.cur->com)
		{
			v.out_fd = STDOUT_FILENO;
			if (v.cur->nx && v.cur->nx->sep && strcmp(v.cur->nx->sep, "|") == 0)
				pipe_and_update_out_fd(&v.out_fd, v.pipefd);
			else if (v.cur->nx && v.cur->nx->sep)
			{
				handle_redirection(v.cur, &v.in_fd, &v.out_fd);
			}
			select_built_or_exe(v.cur->com, envp, v.in_fd, v.out_fd);
			if (v.out_fd != STDOUT_FILENO)
				close_and_update_fds(&v.in_fd, &v.out_fd, v.pipefd);
		}
		v.cur = v.cur->nx;
	}
}

/*	parser.c: 5.	*/
/*	used only to create the commands list using
 * the path on env variable than parse it to the tree function
 * that will take care of the rest*/

void	parser(char **envp, t_token *head)
{
	t_command	*commands;
	char		**path;

	store_fd_flag(0, 0);
	store_fd_flag(0, 3);
	path = find_path(envp);
	commands = build_command_list(head, path);
	tree(commands, envp);
	ft_free2(path);
	free_t_token(head);
	free_t_command(commands);
}
