/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 17:46:35 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/26 17:46:35 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


#include <stdio.h>


static void		set_first_intersection(t_view *view, t_ray *ray)
{
	int		i;
	float	dist;
	float	closest_dist;

	i = -1;
	closest_dist = 2147483647;
	while (!view->objs[++i].is_null)
	{
		dist = intersect_any(ray, &(view->objs[i]));
		if (dist == 0.0)
			continue ;
		closest_dist = MIN(closest_dist, dist);
		if (closest_dist == dist)
			view->closest = &(view->objs[i]);
	}
	if (closest_dist == 2147483647)
		view->closest = 0;
	else
	{
		ft_vector_scale(closest_dist, ray->dir, view->inter);
		ft_vector_add(view->inter, ray->eye, view->inter);
	}
}

// static int		check_for_intersection(t_view *view, t_ray *ray)
// {
// 	int		i;
// 	float	dist;
// 	t_3dp	temp;

// 	i = -1;
// 	ft_vector_scale(0.1, ray->dir, &temp);
// 	ft_vector_add(ray->eye, &temp, ray->eye);
// 	while (!view->objs[++i].is_null)
// 	{
// 		dist = intersect_any(ray, &(view->objs[i]));
// 		if (dist > 0.0)
// 			return (1);
// 	}
// 	return (0);
// }

static t_color	get_color(t_view *view)
{
	float	total_shade;
	float	shade;
	int		i;

	i = -1;
	normal_any(view);
	ft_vector_normalize(view->normal->dir);
	total_shade = -2147483648;
	while (!view->objs[++i].is_null)
	{
		if (!view->objs[i].is_light)
			continue ;
		ft_vector_scale(1, view->inter, view->light_ray->eye);
		ft_vector_sub(view->objs[i].center, view->inter, view->light_ray->dir);
		ft_vector_normalize(view->light_ray->dir);
		shade = MAX(0.0, DOT_PRODUCT(view->normal->dir, view->light_ray->dir));
		if (shade >= 0.99)
			return (ft_color_combine(view->closest->color, 0xFFFFFF));
		total_shade = MAX(shade, total_shade);
	}
	return (ft_color_mult(view->closest->color, view->ambient + view->diffuse *
		total_shade));
}

static t_ray	*get_reflected_ray(t_view *view, t_ray *ray)
{
	t_ray	*out;
	float	ratio;

	out = ft_get_ray();
	ratio = -DOT_PRODUCT(ray->dir, view->normal->dir);
	out->eye = view->normal->eye;
	out->dir = ft_get_3d_point(0, 0, 0);
	out->dir->x = ray->dir->x + (2.0 * view->normal->dir->x * ratio);
	out->dir->y = ray->dir->y + (2.0 * view->normal->dir->y * ratio);
	out->dir->z = ray->dir->z + (2.0 * view->normal->dir->z * ratio);
	ft_vector_normalize(out->dir);
	return (out);
}

t_color			trace_ray(t_view *view, t_ray *ray)
{
	t_ray	*reflected;
	t_color	color;

	set_first_intersection(view, ray);
	if (!view->inter || !view->closest)
		return (0);
	color = get_color(view);
	if (view->closest->reflect > 0.0 && view->closest->reflect <= 1.0)
	{
		reflected = get_reflected_ray(view, ray);
		color = ft_color_combine(color, trace_ray(view, reflected));
		free(reflected);
	}
	return (color);
}
