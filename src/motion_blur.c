/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_blur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:03:36 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/12 14:44:01 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static void	normalise_color(t_frame_buffer *fb, int count)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			fb->motion_calc[y * WIN_W + x].s_rgb.r /= count;
			fb->motion_calc[y * WIN_W + x].s_rgb.g /= count;
			fb->motion_calc[y * WIN_W + x].s_rgb.b /= count;
			x++;
		}
		y++;
	}
}

static void	color_to_data(t_frame_buffer *fb)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			fb->data[y * WIN_W + x]
				= color_to_int(fb->motion_calc[y * WIN_W + x]);
			x++;
		}
		y++;
	}
}

static void	add_to_color_buffer(t_frame_buffer *fb)
{
	t_color	color;
	int		y;
	int		x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			color = int_to_color(fb->data[y * WIN_W + x]);
			fb->motion_calc[y * WIN_W + x].s_rgb.r += (color.s_rgb.r / 255);
			fb->motion_calc[y * WIN_W + x].s_rgb.g += (color.s_rgb.g / 255);
			fb->motion_calc[y * WIN_W + x].s_rgb.b += (color.s_rgb.b / 255);
			x++;
		}
		y++;
	}
}

void	create_motion_blur(t_main *main)
{
	int		frame_count;

	frame_count = 1;
	add_to_color_buffer(&main->sdl.frame_buffer);
	while (motion_set_all(main) > 0)
	{
		main->cam.coi_transform
			= coi_transform(&main->cam, main->cam.transform);
		main->ant_al = 1;
		draw_frame(main);
		edge_detection(&main->sdl.frame_buffer);
		main->ant_al = A_A_DIV;
		draw_frame(main);
		add_to_color_buffer(&main->sdl.frame_buffer);
		frame_count++;
	}
	if (frame_count > 1)
	{
		normalise_color(&main->sdl.frame_buffer, frame_count);
		color_to_data(&main->sdl.frame_buffer);
		edge_detection(&main->sdl.frame_buffer);
	}
}
