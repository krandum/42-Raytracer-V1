/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:01:31 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/30 14:01:32 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_sphere(t_view *view)
{
	ft_vector_scale(1, view->inter, view->normal->eye);
	ft_vector_sub(view->inter, view->closest->center, view->normal->dir);
}

void	normal_any(t_view *view)
{
	if (view->closest->is_sphere)
		normal_sphere(view);
	/*else if (obj.is_cube)
		normal_cube(view);
	else if (obj.is_cylinder)
		normal_cylinder(view);
	else if (obj.is_cone)
		normal_cone(view);
	else if (obj.is_torus)
		normal_torus(view);
	else if (obj.is_plane)
		normal_plane(view);*/
}

/*
**	Variable names based off a diagram at
**	http://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
*/

float	intersect_sphere(t_ray *ray, t_object *obj)
{
	double	disc;
	float	v;
	float	r;
	t_3dp	*eo;

	eo = ft_get_3d_point(0.0, 0.0, 0.0);
	ft_vector_sub(obj->center, ray->eye, eo);
	v = DOT_PRODUCT(eo, ray->dir);
	r = ((t_sphere*)obj->shape)->rad;
	disc = r * r - (DOT_PRODUCT(eo, eo) - v * v);
	free(eo);
	if (disc < 0)
		return (0.0);
	return (v - sqrt(disc));
}

float	intersect_any(t_ray *ray, t_object *obj)
{
	if (obj->is_sphere)
		return (intersect_sphere(ray, obj));
	/*if (obj.is_cube)
		return (intersect_cube(ray, obj));
	if (obj.is_cylinder)
		return (intersect_cylinder(ray, obj));
	if (obj.is_cone)
		return (intersect_cone(ray, obj));
	if (obj.is_torus)
		return (intersect_torus(ray, obj));
	if (obj.is_plane)
		return (intersect_plane(ray, obj));*/
	return (0.0);
}
