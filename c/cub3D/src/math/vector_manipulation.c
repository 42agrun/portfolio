/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:08:05 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/05 11:19:19 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/math_framework.h"

/**
 * assign a vectors x an y value in a single function call
*/
void	assign_vec(t_vector *vec, float x, float y)
{
	vec->x = x;
	vec->y = y;
}

/**
 * assign a vectors x an y value in a single function call
*/
void	assign_vec_int(t_vec_int *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}

t_vector	create_vec(float x, float y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}
