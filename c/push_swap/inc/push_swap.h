/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h 	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:32:59 by agrun             #+#    #+#             */
/*   Updated: 2023/03/18 10:33:02 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

void	push_swap(int *a);
void	rearrange_stack(int *s);
void	assign_buffer(char *buff, char *str);
char	*combine_args(char **argv);

int		*fill_stack(int *stack, char **args);
int		array_size(int *s);
int		check_dupes(int *stack);
int		check_order(int *a);
int		check_input(char **args);
int		ft_error(int error);

void	sa(int *a);
void	sb(int *b);
void	ss(int *a, int *b);
void	pa(int *a, int *b);
void	pb(int *a, int *b);
void	ra(int *a);
void	rb(int *b);
void	rr(int *a, int *b);
void	rra(int *a);
void	rrb(int *b);
void	rrr(int *a, int *b);

void	complex_sorting(int *a, int *b, int *head_a);
void	simple_sorting(int *a, int *b);
void	sort_5(int *a, int *b);

void	define_head(int *head, int *stack);
void	overwrite_head(int *head, int *stack);
int		get_max_bits(int *head);
int		get_min(int *stack, int val);
int		get_distance(int *stack, int index);

int		ft_atoi(const char *nptr);
void	ft_free(int **s);
void	ft_free_arr(char **array);
char	**ft_split(char *s, char c);

#endif
