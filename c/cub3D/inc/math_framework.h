/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_framework.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:04:57 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/06 15:03:03 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_FRAMEWORK_H
# define MATH_FRAMEWORK_H

# include <math.h>

typedef struct s_vector
{
	float	x;
	float	y;
}t_vector;

typedef struct s_vec_int
{
	int		x;
	int		y;
}t_vec_int;

t_vector	rotate_vec(t_vector vec, float theta);
void		assign_vec(t_vector *vec, float x, float y);
void		assign_vec_int(t_vec_int *vec, int x, int y);
t_vector	scale_vec(t_vector vec, float lambda);
t_vector	add_vec(t_vector vec1, t_vector vec2);
t_vector	sub_vec(t_vector vec1, t_vector vec2);
t_vector	create_vec(float x, float y);

#endif
