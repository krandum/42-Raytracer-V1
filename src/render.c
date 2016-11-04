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

void	*threaded_artist(void *tmp)
{
	int		y;
	int		x;
	float	global[4][4];
	t_ray	*ray;
	t_3dp	*cur_cam;
	t_split	*s;

	s = (t_split*)tmp;
	cur_cam = (t_3dp*)ft_memalloc(sizeof(t_3dp));
	ft_get_id_matrix(global);
	ft_mat_rotate(global, s->view->theta, s->view->phi, s->view->psi);
	ft_mat_translate(global, s->view->x_shift,
		s->view->y_shift, s->view->z_shift);
	ft_vector_scale(1, s->view->cam_pos, cur_cam);
	ft_vec_mat_mult(cur_cam, global, cur_cam);
	ray = ft_get_ray();
	y = s->y_start - 1;
	while (++y < s->y_end)
	{
		x = s->x_start - 1;
		while (++x < s->x_end)
		{
			ray->eye->x = x - WIN_WIDTH / 2;
			ray->eye->y = y - WIN_HEIGHT / 2;
			ray->eye->z = s->view->cam_dist;
			ft_vec_mat_mult(ray->eye, global, ray->eye);
			ft_vector_sub(cur_cam, ray->eye, ray->dir);
			ft_vector_normalize(ray->dir);
			s->exclude = 0;
			ft_put_pixel(s->view, x, y, trace_ray(s, ray, 0));
		}
	}
	free(ray);
	free(cur_cam);
	return (NULL);
}

void	del_splits(t_split *splits, int num)
{
	int		i;

	i = -1;
	while (++i < num)
	{
		free(splits[i].inter);
		free(splits[i].light_ray);
		free(splits[i].normal);
	}
	free(splits);
}

void	draw(t_view *view)
{
	t_split	*splits;
	int		i;

	splits = (t_split*)ft_memalloc(sizeof(t_split) * 16);
	i = -1;
	while (++i < 16)
	{
		splits[i].x_start = (WIN_WIDTH / 4) * (i % 4);
		splits[i].x_end = (WIN_WIDTH / 4) * (i % 4 + 1);
		splits[i].y_start = (WIN_HEIGHT / 4) * (i / 4);
		splits[i].y_end = (WIN_HEIGHT / 4) * (i / 4 + 1);
		splits[i].view = view;
		splits[i].inter = ft_get_3d_point(0, 0, 0);
		splits[i].normal = ft_get_ray();
		splits[i].light_ray = ft_get_ray();
		pthread_create(&(splits[i].thread), NULL, threaded_artist,
			(void*)&splits[i]);
	}
	i = -1;
	while (++i < 16)
		pthread_join(splits[i].thread, NULL);
	del_splits(splits, 16);
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
