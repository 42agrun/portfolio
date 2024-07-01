/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-24 09:14:42 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-24 09:14:42 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	lexer_utils_1.c: 1.	*/

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	ret;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	ret = s1[i] - s2[i];
	return (ft_return(ret, 0));
}

/*	lexer_utils_1.c: 2.	*/

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*	lexer_utils_1.c: 3.	*/

int	ft_word_count2(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			count++;
		while (str[i] && !(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
	}
	return (ft_return(count, 0));
}

/*	lexer_utils_1.c: 4.	*/

void	ft_copy_words(char **out, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		j = i;
		while (str[i] && !(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(((i - j) + 1) * sizeof(char));
			out[k] = ft_strncpy(out[k], &str[j], i - j);
			k++;
		}
	}
	out[k] = NULL;
}

/*	lexer_utils_1.c: 5.	*/

char	**ft_split3(char *str)
{
	char	**out;
	int		word_count;

	word_count = ft_word_count2(str);
	out = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	ft_copy_words(out, str);
	return (out);
}
