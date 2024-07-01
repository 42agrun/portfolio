/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:13:13 by agrun             #+#    #+#             */
/*   Updated: 2023/03/18 10:13:18 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

char	*create_new(char *new, char **argv, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (argv[j])
	{
		while (argv[j][i])
		{
			new[k] = argv[j][i];
			k++;
			i++;
		}
		i = 0;
		new[k] = ' ';
		k++;
		j++;
	}
	new[k] = 0;
	return (new);
}

char	*combine_args(char **argv)
{
	int		j;
	int		total;
	int		i;
	char	*new;

	j = 1;
	total = 0;
	i = 0;
	while (argv[j])
	{
		while (argv[j][i])
			i++;
		total += i + 1;
		i = 0;
		j++;
	}
	total++;
	new = malloc(sizeof(char) * (total + 1));
	if (!new)
		return (NULL);
	total = 0;
	create_new(new, argv, total);
	return (new);
}
