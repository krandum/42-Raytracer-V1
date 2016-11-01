/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 12:38:09 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/30 12:38:10 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

void	ft_vector_scale(float c, t_3dp *vec, t_3dp *dest)
{
	dest->x = vec->x * c;
	dest->y = vec->y * c;
	dest->z = vec->z * c;
}

/*
**	Turns a vector into a unit vector, therefore maintaining its direction but
**	making it more usable.
*/

void	ft_vector_normalize(t_3dp *vec)
{
	float	d;

	d = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x /= d;
	vec->y /= d;
	vec->z /= d;
}

void	ft_vector_add(t_3dp *v1, t_3dp *v2, t_3dp *dest)
{
	dest->x = v1->x + v2->x;
	dest->y = v1->y + v2->y;
	dest->z = v1->z + v2->z;
}

void	ft_vector_sub(t_3dp *v1, t_3dp *v2, t_3dp *dest)
{
	dest->x = v1->x - v2->x;
	dest->y = v1->y - v2->y;
	dest->z = v1->z - v2->z;
}
