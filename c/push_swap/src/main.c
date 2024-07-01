/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                             	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/18/03 12:00:36 by agrun             #+#    #+#             */
/*   Updated: 2023/18/03 12:00:39 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

//FIX THIS INPUT!! "2147483647 3 -1 0 1 2 5 7 -2147483648"

/*	Used for calculating the necessary size of the array.			*/

static int	stack_size(char	**args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/*	Make sure only numbers are among the arguments! Beware of empty inputs!	
	Check if there's no number/digit right before a plus/minus-sign!	*/

static int	check_args(char *argv)
{
	int	i;
	int	n_found;

	i = 0;
	n_found = 0;
	while (argv[i])
	{
		if (argv[i] >= '0' && argv[i] <= '9')
			n_found = 1;
		if ((argv[i] == '-' || argv[i] == '+')
			&& (argv[i - 1] < '0' || argv[i - 1] > '9')
			&& (argv[i + 1] >= '0' && argv[i + 1] <= '9'))
			i++;
		else if (argv[i] == ' ')
			i++;
		else if (argv[i] && (!(argv[i] >= '0' && argv[i] <= '9')))
			return (1);
		else
			i++;
	}
	if (n_found == 0)
		return (1);
	return (0);
}

/*	Function for printing out "Error" followed by a new line on STDERROR.	*/

int	ft_error(int error)
{
	write(2, "Error\n", 6);
	return (error);
}

/*	Setting up the stack for sorting and checking for invalid inputs.
	Anything but a unique number has to be considered an invalid input.	*/

static int	main_setup(char *argument)
{
	int		*a;
	char	**args;

	args = ft_split(argument, ' ');
	if (!args)
		return (ft_error(1));
	a = malloc(sizeof(int) * (stack_size(args) + 1));
	if (!a || !check_input(args))
	{
		ft_free(&a);
		ft_free_arr(args);
		return (ft_error(1));
	}
	if (!fill_stack(a, args))
	{
		ft_free(&a);
		ft_free_arr(args);
		return (ft_error(1));
	}
	ft_free_arr(args);
	if (!check_dupes(a))
		push_swap(a);
	ft_free(&a);
	return (0);
}

int	main(int argc, char **argv)
{
	int		r;
	int		i;
	char	*comb;

	i = 1;
	if (argc < 2)
		return (0);
	while (argv[i])
	{
		if (check_args(argv[i]) == 1)
			return (ft_error(1));
		i++;
	}
	if (argc > 2)
	{
		comb = combine_args(argv);
		if (!comb)
			return (ft_error(1));
		r = main_setup(comb);
		free(comb);
		comb = NULL;
	}
	else
		r = main_setup(argv[1]);
	return (r);
}
/*	Tester function to check the sorted values at the end.
						
void	print_array(int *a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		printf("[%d]", a[i]);
		i++;
	}
	printf("\n");
}										*/