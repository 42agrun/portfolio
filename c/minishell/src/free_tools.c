/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-24 09:27:16 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-24 09:27:16 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	free_tools.c: 1.	*/
/* used specifically to verify if the array exists before free */

void	ft_free2(char **split)
{
	int	i;

	if (split == NULL)
	{
		return ;
	}
	i = 0;
	if (ft_strstr(split[0], "export"))
	{
		free(split);
		split = NULL;
		return ;
	}
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

/*	free_tools.c: 2.	*/
/* used specifically to free t_token structs */

void	free_t_token(t_token *head)
{
	t_token	*temp;

	if (head == NULL)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->token);
		temp->token = NULL;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
	head = NULL;
}

/*	free_tools.c: 3.	*/
/* used specifically to free t_command structs */

void	free_t_command(t_command *head)
{
	t_command	*temp;

	if (head == NULL)
		return ;
	while (head)
	{
		temp = head;
		head = head->nx;
		ft_free2(temp->com);
		free(temp);
		temp = NULL;
	}
	head = NULL;
}

/*	free_tools.c: 4.	*/
/* used only for debuggin */

/*

void print_list(t_token *head)
{
    t_token *temp;

    temp = head;
    while (temp)
    {
        printf("Token: %s\n", temp->token);
        printf("Value: %s\n", temp->value);
        printf("Token code: %d\n", temp->token_code);
        printf("Index: %d\n", temp->index);
        printf("\n");
        temp = temp->next;
    }
}

*/

/*	free_tools.c: 5.	*/
/* used only for debuggin */

/*

void	print_command_list(t_command *head)
{
	t_command	*temp;

	temp = head;
	while (temp)
	{
		if(temp->command)
		{
			printf("Command: ");
			for(int i = 0; temp->command[i]; i++)
			{
				printf("%s ", temp->command[i]);
			}
			printf("\n");
		}
		if (temp->separator)
		{
			printf("Separator: %s\n", temp->separator);
		}
		if (temp->arguments)
		{
			printf("Arguments: %s\n", temp->arguments);
		}
		printf("\n");
		temp = temp->next;
	}
}

*/
