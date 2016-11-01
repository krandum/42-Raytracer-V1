/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 16:12:30 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/22 16:12:31 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// Remember to make the object array null-terminated (is_null)
// Diffuse goes up with more lights?

/*
**	Temporary function to initialize the different shapes used
*/

static void	set_shapes(t_view *view)
{
	view->objs = (t_object*)ft_memalloc(sizeof(t_object) * 4);
	view->objs[0].center = ft_get_3d_point(-100.0, 0.0, 50.0);
	view->objs[0].is_sphere = 1;
	view->objs[0].shape = ft_memalloc(sizeof(t_sphere));
	((t_sphere*)view->objs[0].shape)->rad = 70.0;
	view->objs[0].color = 0xFF;
	view->objs[1].center = ft_get_3d_point(100.0, 0.0, 50.0);
	view->objs[1].is_sphere = 1;
	view->objs[1].shape = ft_memalloc(sizeof(t_sphere));
	((t_sphere*)view->objs[1].shape)->rad = 70.0;
	view->objs[1].color = 0xFF0000;
	view->objs[2].center = ft_get_3d_point(50.0, 50.0, -200.0);
	view->objs[2].is_light = 1;
	view->objs[3].is_null = 1;
}

int			exit_hook(t_view *view)
{
	mlx_destroy_window(view->id, view->win);
	exit(0);
}

int			main(void)
{
	t_view *view;

	view = (t_view*)ft_memalloc(sizeof(t_view));
	set_shapes(view);
	view->id = mlx_init();
	view->win = mlx_new_window(view->id, WIN_WIDTH, WIN_HEIGHT,
		"42-Raytracer v1");
	view->cam_pos = ft_get_3d_point(0.0, 0.0, -50.0);
	view->cam_dist = 50.0;
	view->diffuse = 0.95;
	view->ambient = 0.05;
	view->closest = (t_object*)ft_memalloc(sizeof(t_object));
	view->inter = ft_get_3d_point(0, 0, 0);
	view->normal = ft_get_ray();
	view->light_ray = ft_get_ray();
	view->pressed = (t_keys*)ft_memalloc(sizeof(t_keys));
	mlx_expose_hook(view->win, expose_hook, view);
	mlx_hook(view->win, 2, 0, key_pressed_hook, view);
	mlx_hook(view->win, 3, 0, key_released_hook, view);
	mlx_hook(view->win, 17, 0, exit_hook, view);
	mlx_loop_hook(view->id, move_loop_hook, view);
	mlx_loop(view->id);
}
