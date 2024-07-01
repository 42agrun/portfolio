/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_printout_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	check_printout_1.c: 1.	*/

void	apply_string(char *buffer, char *str, int i)
{
	int	j;

	j = 0;
	if (!str)
		return ;
	while (str[j])
	{
		buffer[i] = str[j];
		i++;
		j++;
	}
	buffer[i] = 0;
	return ;
}

/*	check_printout_1.c: 2.	*/
/*	Check the function below (*check_printout) for an explanation on the
	various modes. This function basically displays any potential format
	errors during the conversion of the main-prompt.

	Errors should always appear at the top before other printouts occur.	*/

char	*e_print(char *str, int mode, int i, int extra)
{
	static int	wipe_out;
	static int	init_array;
	static char	buf[1024];

	if (wipe_out == 1 || init_array != 4242)
		buf[0] = 0;
	wipe_out = 0;
	init_array = 4242;
	if (mode == 1 || mode == 2)
	{
		wipe_out = 1;
		if (mode == 2 && buf[0])
			printf("%s", buf);
		return (buf);
	}
	while (buf[i])
		i++;
	if (extra)
		complex_errors(buf, str, extra, i);
	else
		apply_string(buf, str, i);
	return (buf);
}

/*	check_printout_1.c: 3.	*/
/*	This function stores any printout feedback and displays it at the end.
	
	Mode 0: Simply saves the input within a static array.
	Mode 1: Will return the saved array and then wipe it.
	Mode 2: Will print out the entire string and then wipe it.		

	Since you cannot erase an array right after returning it this will be
	taken care of during the next visit of this function ("wipe_out" int).	*/

char	*check_printout(char c, char *str, int mode, int i)
{
	static int	wipe_out;
	static int	init_array;
	static char	buffer[5000];

	if (wipe_out == 1 || init_array != 4242)
		buffer[0] = 0;
	wipe_out = 0;
	init_array = 4242;
	e_print(NULL, mode, 0, 0);
	if (mode == 1 || mode == 2)
	{
		wipe_out = 1;
		if (mode == 2 && buffer[0])
			printf("%s", buffer);
		return (buffer);
	}
	while (buffer[i])
		i++;
	apply_string(buffer, str, i);
	if (!str)
	{
		buffer[i] = c;
		buffer[i + 1] = 0;
	}
	return (buffer);
}
