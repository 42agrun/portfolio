/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-24 09:45:56 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-24 09:45:56 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	parser_utils_1.c: 1.	*/

void	add_command_node(t_command **c, t_token **tmp, char **path)
{
	int	i;

	i = 0;
	(*c)->com = (char **)malloc(sizeof(char *));
	(*c)->com[i] = valid_cmd(path, (*tmp)->value);
	*tmp = (*tmp)->next;
	while (*tmp && (*tmp)->token_code != 2)
	{
		i++;
		(*c)->com = realloc((*c)->com, (i + 2) * sizeof(char *));
		(*c)->com[i] = strdup((*tmp)->value);
		*tmp = (*tmp)->next;
	}
	if (i == 0)
	{
		(*c)->com = realloc((*c)->com, (i + 2) * sizeof(char *));
	}
	(*c)->com[i + 1] = NULL;
	(*c)->sep = NULL;
	(*c)->arg = NULL;
}

/*	parser_utils_1.c: 2.	*/

void	add_separator_node(t_command **current, t_token *tmp)
{
	(*current)->sep = tmp->value;
	(*current)->com = NULL;
	(*current)->arg = NULL;
}

/*	parser_utils_1.c: 3.	*/

void	add_argument_node(t_command **current, t_token *tmp)
{
	(*current)->arg = tmp->value;
	(*current)->com = NULL;
	(*current)->sep = NULL;
}

/*	parser_utils_1.c: 4.	*/

void	exit_with_error(const char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}
