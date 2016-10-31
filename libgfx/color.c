/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 17:16:49 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/30 17:16:50 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

t_color		ft_color_combine(t_color c1, t_color c2)
{
	unsigned char	rgb[3];
	t_color			out;

	if (!c1)
		return (c2);
	if (!c2)
		return (c1);
	rgb[0] = (unsigned char)((((c1 & 0xFF0000) + (c2 & 0xFF0000)) / 2) >> 16);
	rgb[1] = (unsigned char)((((c1 & 0xFF00) + (c2 & 0xFF00)) / 2) >> 8);
	rgb[2] = (unsigned char)(((c1 & 0xFF) + (c2 & 0xFF)) / 2);
	out = ((t_color)rgb[0]) << 16 | ((t_color)rgb[1]) << 8 | (t_color)rgb[2];
	return (out);
}

void		ft_put_pixel(t_view *view, int x, int y, t_color color)
{
	int				i;

	i = (x * 4) + (y * view->size_line);
	view->pixels[i] = color;
	view->pixels[++i] = color >> 8;
	view->pixels[++i] = color >> 16;
}
