/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 16:47:24 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/22 16:47:25 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		move_loop_hook(t_view *v)
{
	if (v->pressed->w)
		v->theta -= 0.05;
	if (v->pressed->s)
		v->theta += 0.05;
	if (v->pressed->a)
		v->phi += 0.05;
	if (v->pressed->d)
		v->phi -= 0.05;
	if (v->pressed->q)
		v->psi -= 0.05;
	if (v->pressed->e)
		v->psi += 0.05;
	if (v->pressed->up)
		v->y_shift -= 5.0;
	if (v->pressed->down)
		v->y_shift += 5.0;
	if (v->pressed->left)
		v->x_shift -= 5.0;
	if (v->pressed->right)
		v->x_shift += 5.0;
	if (v->pressed->w || v->pressed->s || v->pressed->a || v->pressed->d ||
		v->pressed->q || v->pressed->e || v->pressed->up || v->pressed->down ||
		v->pressed->left || v->pressed->right)
		reload(v);
	return (0);
}

int		key_pressed_hook(int keycode, t_view *view)
{
	if (keycode == KEY_ESC)
		exit_hook(view);
	if (keycode == KEY_ROT_X_U)
		view->pressed->w = 1;
	else if (keycode == KEY_ROT_X_D)
		view->pressed->s = 1;
	else if (keycode == KEY_ROT_Y_U)
		view->pressed->a = 1;
	else if (keycode == KEY_ROT_Y_D)
		view->pressed->d = 1;
	else if (keycode == KEY_ROT_Z_U)
		view->pressed->e = 1;
	else if (keycode == KEY_ROT_Z_D)
		view->pressed->q = 1;
	else if (keycode == KEY_UP)
		view->pressed->up = 1;
	else if (keycode == KEY_DOWN)
		view->pressed->down = 1;
	else if (keycode == KEY_LEFT)
		view->pressed->left = 1;
	else if (keycode == KEY_RIGHT)
		view->pressed->right = 1;
	return (0);
}

int		key_released_hook(int keycode, t_view *view)
{
	if (keycode == KEY_ROT_X_U)
		view->pressed->w = 0;
	else if (keycode == KEY_ROT_X_D)
		view->pressed->s = 0;
	else if (keycode == KEY_ROT_Y_U)
		view->pressed->a = 0;
	else if (keycode == KEY_ROT_Y_D)
		view->pressed->d = 0;
	else if (keycode == KEY_ROT_Z_U)
		view->pressed->e = 0;
	else if (keycode == KEY_ROT_Z_D)
		view->pressed->q = 0;
	else if (keycode == KEY_UP)
		view->pressed->up = 0;
	else if (keycode == KEY_DOWN)
		view->pressed->down = 0;
	else if (keycode == KEY_LEFT)
		view->pressed->left = 0;
	else if (keycode == KEY_RIGHT)
		view->pressed->right = 0;
	return (0);
}
