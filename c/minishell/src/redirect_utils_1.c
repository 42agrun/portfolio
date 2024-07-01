/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-24 09:58:27 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-24 09:58:27 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	redirect_utils_1.c: 1.	*/
/* redirect std out to the fd of a file using the open function, std out
 * is parsed by reference so the output don`t get stuck inside the file*/

void	redirect_stdout_to_file(char *file_name, int *out_fd)
{
	*out_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (*out_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

/*	redirect_utils_1.c: 2.	*/
/* redirect std int to the fd of a file using the open function, std out
 * is parsed by reference so the output don`t get stuck inside the file*/

void	redirect_stdin_from_file(char *file_name, int *in_fd)
{
	*in_fd = open(file_name, O_RDONLY);
	if (*in_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

/*	redirect_utils_1.c: 3.	*/
/* append std out to the fd of a file using the open function, std out
 * is parsed by reference so the output don`t get stuck inside the file*/

void	append_stdout_to_file(char *file_name, int *out_fd)
{
	*out_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (*out_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

/*	redirect_utils_1.c: 4.	*/
/* here doc*/

static void	readline_in_loop(t_hrdoc *v)
{
	v->new_len = v->str_len + strlen(v->line) + 1;
	v->new_str = realloc(v->str, v->new_len + 1);
	if (!v->new_str)
	{
		free(v->str);
		free(v->line);
		exit_with_error("realloc");
	}
	v->str = v->new_str;
	strcpy(v->str + v->str_len, v->line);
	v->str[v->new_len - 1] = '\n';
	v->str[v->new_len] = '\0';
	v->str_len = v->new_len;
	free(v->line);
}

void	read_stdin_from_string(const char *delimiter, int *in_fd)
{
	t_hrdoc	v;

	v.str = NULL;
	v.str_len = 0;
	pipe(v.pfd);
	while (1)
	{
		v.line = readline("> ");
		if (!v.line || strcmp(v.line, delimiter) == 0)
		{
			free(v.line);
			break ;
		}
		readline_in_loop(&v);
	}
	v.bytes_written = write(v.pfd[1], v.str, v.str_len);
	if (v.bytes_written != (ssize_t)v.str_len)
		exit_with_error("write");
	close(v.pfd[1]);
	*in_fd = v.pfd[0];
	free(v.str);
}
