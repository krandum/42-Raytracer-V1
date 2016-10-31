/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 16:12:22 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/22 16:12:24 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "libgfx.h"
# include "mlx.h"

void		normal_any(t_view *view);
float		intersect_any(t_ray *ray, t_object *obj);
t_color		trace_ray(t_view *view, t_ray *ray);
void		reload(t_view *view);
int			expose_hook(t_view *view);

#endif
