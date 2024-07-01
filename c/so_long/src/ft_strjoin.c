/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 10:33:36 by agrun             #+#    #+#             */
/*   Updated: 2023/01/02 10:33:39 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

static char	*ft_strjoin_ex(char *archive, char *buff)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * ((ft_strlen(archive) + ft_strlen(buff)) + 1));
	if (!str)
	{
		ft_free(&archive);
		return (NULL);
	}
	if (archive)
	{
		while (archive[i] && archive[i] != '\n')
		{
			str[i] = archive[i];
			i++;
		}
	}
	if (buff[0] && buff[0] != '\n')
		str[i++] = buff[0];
	if (str[i])
		str[i] = 0;
	ft_free(&archive);
	return (str);
}

char	*ft_strjoin(char *archive, char *buff)
{
	if (buff[0] == 10)
		return (archive);
	if (!archive)
	{
		archive = (char *)malloc((ft_strlen(buff) + 1) * sizeof(char));
		if (!archive)
			return (NULL);
		archive[0] = 0;
	}
	if (!archive || !buff)
		return (NULL);
	archive = ft_strjoin_ex(archive, buff);
	if (!archive)
		return (NULL);
	return (archive);
}
