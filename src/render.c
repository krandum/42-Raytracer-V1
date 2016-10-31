/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 15:34:42 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/30 15:34:46 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw(t_view *view)
{
	int		i;
	float	global[4][4];
	t_ray	*ray;

	ft_get_id_matrix(global);
	ft_mat_rotate(global, view->theta, view->phi, view->psi);
	ft_mat_translate(global, view->x_shift, view->y_shift, view->z_shift);
	ray = ft_get_ray();
	i = -1;
	while (++i < WIN_WIDTH * WIN_HEIGHT)
	{
		view->color = 0;
		ray->eye->x = (i % WIN_WIDTH) - WIN_WIDTH / 2;
		ray->eye->y = (i / WIN_WIDTH) - WIN_HEIGHT / 2;
		ray->eye->z = view->cam_dist;
		ft_vec_mat_mult(ray->eye, global, ray->eye);
		ft_vector_sub(ray->eye, view->cam_pos, ray->dir);
		ft_vector_normalize(ray->dir);
		ft_put_pixel(view, i % WIN_WIDTH, i / WIN_WIDTH, trace_ray(view, ray));
	}
	free(ray);
}

void	reload(t_view *view)
{
	view->img = mlx_new_image(view->id, WIN_WIDTH + 100, WIN_HEIGHT + 100);
	view->pixels = mlx_get_data_addr(view->img, &(view->bits_per_pixel),
		&(view->size_line), &(view->endian));
	draw(view);
	mlx_put_image_to_window(view->id, view->win, view->img, 0, 0);
	mlx_destroy_image(view->id, view->img);
}

int		expose_hook(t_view *view)
{
	reload(view);
	return (0);
}
