/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:18:05 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/05 11:19:23 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/math_framework.h"

/**
 * rotates vector clockwise by the angle (in radian) theta using the
 * rotation matrix:
 *  [ cos(a) -sin(a) ]
 *  [ sin(a)  cos(a) ]
*/
t_vector	rotate_vec(t_vector vec, float theta)
{
	t_vector	old;

	old.x = vec.x;
	old.y = vec.y;
	vec.x = old.x * cos(theta) - old.y * sin(theta);
	vec.y = old.x * sin(theta) + old.y * cos(theta);
	return (vec);
}

/**
 * multiply a vector by the scaling factor lambda
*/
t_vector	scale_vec(t_vector vec, float lambda)
{
	vec.x = vec.x * lambda;
	vec.y = vec.y * lambda;
	return (vec);
}

/**
 * vector addition: add vec2 to vec1
*/
t_vector	add_vec(t_vector vec1, t_vector vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	return (vec1);
}

t_vector	sub_vec(t_vector vec1, t_vector vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	return (vec1);
}
