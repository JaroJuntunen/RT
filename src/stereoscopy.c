/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:32:13 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/20 15:27:37 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	create_red_blue_stereoscopy(t_frame_buffer *fb)
{
	int		i;
	int		j;
	int		color;
	t_color	left_rgb;
	t_color	right_rgb;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			left_rgb = int_to_color(fb->stereocopy[(j * WIN_W) + i]);
			right_rgb = int_to_color(fb->data[(j * WIN_W) + i]);
			right_rgb.s_rgb.r = left_rgb.s_rgb.r / 255;
			right_rgb.s_rgb.g /= 255;
			right_rgb.s_rgb.b /= 255;
			color = color_to_int(right_rgb);
			fb->stereocopy[(j * WIN_W) + i] = color;
			i++;
		}
		j++;
	}
}

void	create_stereoscope(t_main *main, t_matrix cam_transform)
{
	t_matrix	cam_scale;

	main->sdl.frame_buffer.stereocopy
		= ft_memcpy(main->sdl.frame_buffer.stereocopy,
			main->sdl.frame_buffer.data,
			main->sdl.frame_buffer.data_len * sizeof(int));
	cam_scale = matrix_translate((-main->sdl.stereocopy * 1.5), 0, 0.0);
	cam_transform = matrix_multiply(&cam_transform, &cam_scale);
	initialize_camera(&main->scene.cam, cam_transform);
	main->ant_al = 1;
	draw_frame(main);
	edge_detection(&main->sdl.frame_buffer);
	main->ant_al = A_A_DIV;
	draw_frame(main);
	create_red_blue_stereoscopy(&main->sdl.frame_buffer);
}
