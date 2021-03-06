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


# define MAX_DEPTH 3

# define KEY_ESC 53

# define KEY_UP 126 //UP
# define KEY_DOWN 125 //DOWN
# define KEY_LEFT 123 //LEFT
# define KEY_RIGHT 124 //RIGHT

# define KEY_ROT_X_U 13 //W
# define KEY_ROT_X_D 1 //S
# define KEY_ROT_Y_U 0 //A
# define KEY_ROT_Y_D 2 //D
# define KEY_ROT_Z_U 12 //Q
# define KEY_ROT_Z_D 14 //E

void		normal_any(t_split *split);
float		intersect_any(t_ray *ray, t_object *obj);
t_color		trace_ray(t_split *split, t_ray *ray, int depth);
void		reload(t_view *view);
int			expose_hook(t_view *view);
int			key_pressed_hook(int keycode, t_view *view);
int			key_released_hook(int keycode, t_view *view);
int			move_loop_hook(t_view *view);
int			exit_hook(t_view *view);
int			meow(int kitten_id);

#endif
