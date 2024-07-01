/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-13 14:46:41 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-13 14:46:41 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* lexer.c: 1.   */
/* This function, set_token, is responsible for setting
 * the values of a t_token structure. It takes three parameters:
 * a pointer to a t_token node, a string token, and an integer code.
 * It assigns the token string to the node->token field by creating
 * a duplicate using the strdup function. It also sets the code value
 * to the node->token_code field. */

void	set_token(t_token *node, char *token, int code)
{
	node->token = strdup(token);
	node->token_code = code;
}

/* lexer.c: 2.   */
/* This function, check_symbols, examines the value field of a
 * t_token node and determines the appropriate token type. It
 * takes a pointer to a t_token node as a parameter. If the value
 * matches a specific symbol, it calls the set_token function to
 * set the corresponding token type and code. If no match is found,
 * it sets the token type to "Argument" with a code of 1. */

void	check_symbols(t_token *node)
{
	if (ft_strcmp("|", node->value) == 0)
		set_token(node, "Pipe", 2);
	else if (ft_strcmp(">", node->value) == 0)
		set_token(node, "Redirect_in", 2);
	else if (ft_strcmp("<", node->value) == 0)
		set_token(node, "Redirect_out", 2);
	else if (node->value[0] == '-')
		set_token(node, "Flag", 3);
	else if (ft_strcmp("<<", node->value) == 0)
		set_token(node, "Here_doc", 2);
	else if (ft_strcmp(">>", node->value) == 0)
		set_token(node, "Append_doc", 2);
	else
		set_token(node, "Argument", 1);
}

/* lexer.c: 3.   */
/* The is_keyword function checks if the value field
 * of a t_token node matches any keyword or built-in
 * command. It takes a pointer to a t_token node as a parameter.
 * It compares the value against a list of keywords and built-in
 * commands using the ft_strcmp function. If a match is found,
 * it sets the token type to "Command" or "Built_in" using the
 * set_token function with a code of 0. If no match is found,
 * it calls the check_symbols function to determine the token
 * type based on symbols. */

void	is_keyword(t_token *node)
{
	int			i;
	static char	*keywords[] = {
		"echo", "grep", "wc", "mkdir", "mv", "cp", "rm", "rmdir",
		"touch", "whoami", "find", "head", "tail", "diff", "cat",
		"ls", "date", "touch", "sort", "clear", "env",
		"pwd", "export", "make", "bash", "zsh", "minishell",
		"htop", "top", "awk", NULL};

	i = 0;
	while (keywords[i])
	{
		if (ft_strcmp(keywords[i], node->value) == 0)
		{
			set_token(node, "Command", 0);
			return ;
		}
		i++;
	}
	check_symbols(node);
}

/* lexer.c: 4.   */
/* auxiliary function created to norminette  create_token_list
 * that was bigger than 25 lines */

t_token	*add_token(t_token *head, t_token *new_node)
{
	t_token	*current;

	if (!head)
	{
		head = new_node;
	}
	else
	{
		current = head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (head);
}

/* lexer.c: 5.   */
/* The create_token_list function creates a linked
 * list of t_token nodes based on the input string.
 * It takes two parameters: a string input and a pointer
 * to a t_token node head. It splits the input string into
 * tokens using the ft_split3 function and iterates over the
 * resulting tokens. For each token, it creates a new t_token node,
 * assigns the token's value to the value field, sets the index,
 * and determines the token type using the is_keyword function.
 * If head is initially NULL, it assigns the first node to head
 * and updates the current pointer. Otherwise, it appends the new n
 * ode to the end of the list and updates the current pointer
 * accordingly. Finally, it frees the memory allocated by ft_split3
 * and returns the head of the token list. */

t_token	*create_token_list(char *input, t_token *head)
{
	t_data	v;
	t_token	*new_node;

	v.split = ft_split3(input);
	v.i = 0;
	while (v.split[v.i])
	{
		valid_remove(v.split[v.i]);
		new_node = (t_token *)malloc(sizeof(t_token));
		new_node->index = v.i;
		new_node->value = v.split[v.i];
		new_node->next = NULL;
		is_keyword(new_node);
		head = add_token(head, new_node);
		v.i++;
	}
	free(v.split);
	return (head);
}
