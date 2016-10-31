/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgfx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 17:01:40 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/10 17:01:41 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGFX_H
# define LIBGFX_H

# include "libft.h"
# include "mlx.h"
# include "math.h"

# define WIN_WIDTH 1600
# define WIN_HEIGHT 1200

# define DOT_PRODUCT(p0, p1) (p0->x * p1->x + p0->y * p1->y + p0->z * p1->z)
# define MAGNITUDE(p) (sqrt(p->x * p->x + p->y * p->y + p->z * p->z))

typedef int		t_color;

typedef struct	s_2dp
{
	float		x;
	float		y;
}				t_2dp;

typedef struct	s_3dp
{
	float		x;
	float		y;
	float		z;
}				t_3dp;

typedef struct	s_ray
{
	t_3dp		*eye;
	t_3dp		*dir;
}				t_ray;

typedef struct	s_vertex
{
	t_3dp		*local;
	t_3dp		*world;
	t_3dp		*aligned;
}				t_vertex;

typedef struct	s_object
{
	t_3dp		*center;
	t_color		color;
	float		reflect;
	float		refract;
	void		*shape;
	int			is_sphere:1;
	int			is_cube:1;
	int			is_cylinder:1;
	int			is_cone:1;
	int			is_torus:1;
	int			is_plane:1;
	int			is_light:1;
	int			is_null:1;
}				t_object;

typedef struct	s_sphere
{
	float		rad;
}				t_sphere;

/*
**	Everything after endian isn't used in this project
*/

typedef struct	s_view
{
	void		*id;
	void		*win;
	void		*img;
	char		*pixels;
	t_object	*objs;
	t_object	*closest;
	t_3dp		*light_ray;
	t_3dp		*inter;
	t_ray		*normal;
	float		diffuse;
	float		ambient;
	float		cam_dist;
	t_color		color;
	t_3dp		*cam_pos;
	float		theta;
	float		phi;
	float		psi;
	float		scale;
	float		x_shift;
	float		y_shift;
	float		z_shift;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	int			num_colors;
	t_vertex	***points;
	t_color		*colors;
	int			z_min;
	int			z_max;
}				t_view;

t_color		ft_get_color(t_view *view, float c);
void		ft_init_color_table(t_view *view, int colors);
t_color		ft_color_combine(t_color c1, t_color c2);
void		ft_mat_bzero(float mat[4][4]);
void		ft_get_id_matrix(float mat[4][4]);
void		ft_mat_mult(float m1[4][4], float m2[4][4], float d[4][4]);
void		ft_vec_mat_mult(t_3dp *src, float mat[4][4], t_3dp *dst);
void		ft_mat_translate(float mat[4][4], float x, float y, float z);
void		ft_mat_rotate(float mat[4][4], float theta, float phi, float psi);
void		ft_mat_scale(float mat[4][4], float x, float y, float z);
t_2dp		*ft_get_2d_point(float x, float y);
t_3dp		*ft_get_3d_point(float x, float y, float z);
t_vertex	*ft_get_vertex(float x, float y, float z);
t_ray		*ft_get_ray(void);
int			ft_draw_point(t_view *view, int x, int y, float z);
void		ft_drawline_3d(t_view *view, t_3dp p0, t_3dp p1);
void		ft_put_pixel(t_view *view, int x, int y, t_color color);
void		ft_vector_scale(float c, t_3dp *vec, t_3dp *dest);
void		ft_vector_normalize(t_3dp *vec);
void		ft_vector_add(t_3dp *v1, t_3dp *v2, t_3dp *dest);
void		ft_vector_sub(t_3dp *v1, t_3dp *v2, t_3dp *dest);

#endif
