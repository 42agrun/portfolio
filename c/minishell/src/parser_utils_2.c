/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-25 02:02:17 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-25 02:02:17 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	parser_utils_2.c: 1.	*/

t_command	*add_command_node_to_list(t_token **tmp, t_command *n, char **path)
{
	add_command_node(&n, tmp, path);
	return (n);
}

/*	parser_utils_2.c: 2.	*/

t_command	*add_separator_node_to_list(t_token **tmp, t_command *new_node)
{
	add_separator_node(&new_node, *tmp);
	*tmp = (*tmp)->next;
	return (new_node);
}

/*	parser_utils_2.c: 3.	*/

t_command	*add_argument_node_to_list(t_token **tmp, t_command *new_node)
{
	add_argument_node(&new_node, *tmp);
	*tmp = (*tmp)->next;
	return (new_node);
}

/*	parser_utils_2.c: 4.	*/

t_command	*add_to_list(t_command *list_head, t_command *new_node)
{
	t_command	*current;

	if (!list_head)
	{
		list_head = new_node;
		current = list_head;
	}
	else
	{
		current = list_head;
		while (current->nx)
			current = current->nx;
		current->nx = new_node;
	}
	return (list_head);
}

/*	parser_utils_2.c: 5.	*/
/*note that all these functions are connected, they are meant to
 * create a linked list of commands that will be used later
 * to set up the correct syntax in order to be parsed in to the tree
 * function, it iterates through the lists of t_tokes and if
 * it finds a command (t_token->token.code = 0) it will keep iterating
 * until it finds a separator add to an array of strings plus the path
 * to the first element and store it in the (**command), it worth also
 * to mention is that each node of the command list will contain only
 * the value applied to it and all others will be null
 **/

t_command	*build_command_list(t_token *head, char **path)
{
	t_token		*tmp;
	t_command	*list_head;
	t_command	*new_node;

	tmp = head;
	list_head = NULL;
	while (tmp)
	{
		new_node = (t_command *)malloc(sizeof(t_command));
		new_node->nx = NULL;
		if (tmp->token_code == 0)
			new_node = add_command_node_to_list(&tmp, new_node, path);
		else if (tmp->token_code == 2)
			new_node = add_separator_node_to_list(&tmp, new_node);
		else
			new_node = add_argument_node_to_list(&tmp, new_node);
		list_head = add_to_list(list_head, new_node);
	}
	return (list_head);
}
