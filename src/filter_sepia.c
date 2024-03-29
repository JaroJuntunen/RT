/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_sepia.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:06:50 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/07 13:51:57 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static void	sepian_color_ower_flow(t_color *rgb)
{
	if (rgb->s_rgb.r > 255)
		rgb->s_rgb.r = 255;
	if (rgb->s_rgb.g > 255)
		rgb->s_rgb.g = 255;
	if (rgb->s_rgb.b > 255)
		rgb->s_rgb.b = 255;
}

static double	calc_r(t_color rgb)
{
	return ((((0.393 * rgb.s_rgb.r)
				+ (0.769 * rgb.s_rgb.g)
				+ (0.189 * rgb.s_rgb.b))));
}

static double	calc_g(t_color rgb)
{
	return ((((0.349 * rgb.s_rgb.r)
				+ (0.686 * rgb.s_rgb.g)
				+ (0.168 * rgb.s_rgb.b))));
}

static double	calc_b(t_color rgb)
{
	return ((((0.272 * rgb.s_rgb.r)
				+ (0.534 * rgb.s_rgb.g)
				+ (0.131 * rgb.s_rgb.b))));
}

void	create_sepia(t_frame_buffer *fb)
{
	t_color	rgb;
	t_color	sepia_rgb;
	int		color;
	int		i;
	int		j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			int_to_rgb(fb->data[((j * WIN_W) + i)], &rgb);
			sepia_rgb.s_rgb.r = calc_r(rgb);
			sepia_rgb.s_rgb.g = calc_g(rgb);
			sepia_rgb.s_rgb.b = calc_b(rgb);
			sepian_color_ower_flow(&sepia_rgb);
			color = rgb_to_int(sepia_rgb.s_rgb.r,
					sepia_rgb.s_rgb.g, sepia_rgb.s_rgb.b);
			fb->filter[((j * WIN_W) + i)] = color;
			i++;
		}
		j++;
	}
}
