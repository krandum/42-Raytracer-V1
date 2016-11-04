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

static void		set_first_intersection(t_split *s, t_ray *ray)
{
	int		i;
	float	dist;
	float	closest_dist;

	i = -1;
	closest_dist = -2147483648;
	while (!s->view->objs[++i].is_null)
	{
		if (s->exclude == &s->view->objs[i])
			continue ;
		dist = intersect_any(ray, &(s->view->objs[i]));
		if (dist == 0.0 || (s->exclude && dist >= 0.0))
			continue ;
		closest_dist = MAX(dist, closest_dist);
		if (closest_dist == dist)
			s->closest = &(s->view->objs[i]);
	}
	if (closest_dist == -2147483648)
		s->closest = 0;
	else
	{
		ft_vector_scale(closest_dist, ray->dir, s->inter);
		ft_vector_add(s->inter, ray->eye, s->inter);
		s->dist = dist;
	}
}

/*
** static int		check_for_intersection(t_split *s, t_object *light)
** {
** 	int		i;
** 	float	dist;
** 	t_ray	*ray;
**
** 	i = -1;
** 	ray = ft_get_ray();
** 	ray->eye = light->center;
** 	ft_vector_sub(s->inter, light->center, ray->dir);
** 	ft_vector_normalize(ray->dir);
** 	while (!s->view->objs[++i].is_null)
** 	{
** 		if (&(s->view->objs[i]) == s->closest)
** 			continue ;
** 		dist = intersect_any(ray, &(s->view->objs[i]));
** 		if (dist != 0.0 && dist < s->dist)
** 			return (1);
** 	}
** 	free(ray);
** 	return (0);
** }
*/

static t_color	get_color(t_split *s)
{
	float	total_shade;
	float	shade;
	int		i;

	i = -1;
	normal_any(s);
	total_shade = -2147483648;
	while (!s->view->objs[++i].is_null)
	{
		if (!s->view->objs[i].is_light)
			continue ;
		ft_vector_scale(1, s->inter, s->light_ray->eye);
		ft_vector_sub(s->view->objs[i].center, s->inter, s->light_ray->dir);
		ft_vector_normalize(s->light_ray->dir);
		shade = MAX(0.0, DOT_PRODUCT(s->normal->dir, s->light_ray->dir));
		if (shade >= 0.97)
			return (ft_color_partial_combine(0xFFFFFF, s->closest->color,
				(shade - .97) / (0.03)));
		else
			total_shade = MAX(shade, total_shade);
	}
	return (ft_color_mult(s->closest->color, s->view->ambient +
		s->view->diffuse * total_shade));
}

static t_ray	*get_reflected_ray(t_split *s, t_ray *ray)
{
	t_ray	*out;
	float	dot;

	out = ft_get_ray();
	ft_vector_normalize(ray->dir);
	dot = DOT_PRODUCT(ray->dir, s->normal->dir);
	ft_vector_scale(1.0, s->normal->eye, out->eye);
	out->dir->x = ray->dir->x - (2.0 * s->normal->dir->x * dot);
	out->dir->y = ray->dir->y - (2.0 * s->normal->dir->y * dot);
	out->dir->z = ray->dir->z - (2.0 * s->normal->dir->z * dot);
	ft_vector_normalize(out->dir);
	return (out);
}

t_color			trace_ray(t_split *s, t_ray *ray, int depth)
{
	t_ray	*reflected;
	t_color	color;
	t_color	rl;

	set_first_intersection(s, ray);
	if (!s->inter || !s->closest)
		return (0);
	color = get_color(s);
	rl = 0;
	if (s->closest->reflect > 0.0 && s->closest->reflect <= 1.0 &&
		depth < MAX_DEPTH)
	{
		s->exclude = s->closest;
		reflected = get_reflected_ray(s, ray);
		rl = trace_ray(s, reflected, depth + 1);
		free(reflected);
	}
	if (rl)
		return (rl);
	color = ft_color_partial_combine(rl, color, s->exclude ?
		s->exclude->reflect : s->closest->reflect);
	return (color);
}
