/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:56:58 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/14 14:45:44 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	fill_hit_record(t_main *main, t_ray *ray)
{
	t_intersection	closest_t;

	closest_t = find_closest_intersection(&ray->xs);
	if (closest_t.t == INFINITY)
		return (1);
	if (main->obj[closest_t.i].negative == TRUE)
	{
		closest_t = find_negative_object_intersect(ray, closest_t.i, main->obj);
		if (closest_t.t == INFINITY)
			return (1);
	}
	else
	{
		ray->hit.hit_dist = closest_t.t;
		ray->hit.clo_obj_id = (int)closest_t.i;
		ray->hit.hit_loc = ray_position(*ray, ray->hit.hit_dist);
		ray->hit.normal = normal_at(&main->obj[ray->hit.clo_obj_id],
				ray->hit.hit_loc);
	}
	ray->hit.object = &main->obj[ray->hit.clo_obj_id];
	return (0);
}

int	ray_shooter(t_ray *ray, t_main *main)
{
	t_color	hit_color;
	int		count;
	int		hit;

	count = 0;
	hit = 0;
	while (count < main->obj_count)
	{
		if (get_shape_intersections(ray, &main->obj[count]) == 1)
			hit++;
		count++;
	}
	if (hit > 0)
	{
		if (fill_hit_record(main, ray) == 1)
			return (0);
		hit_color = main->obj[ray->hit.clo_obj_id].material.color;
		if (ray->hit.inside == TRUE)
			printf("hello\n");
		/* hit_color = lighting(main->obj[ray->hit.clo_obj_id].material,
				main->light, ray->hit.hit_loc, tuple_neg(ray->dir),
				ray->hit.normal); */
		if (main->obj[ray->hit.clo_obj_id].material.pattern.pattern_id != NONE)
			pattern_at(ray->hit, ray->hit.hit_loc, &hit_color, &main->perlin);
		main->ray.hit.color = tuple_add(main->ray.hit.color, hit_color);
	}
	vec_free(&main->ray.xs.vec);
	return (0);
}

int	anti_aliasing(t_main *main, int pixel_x, int pixel_y, int ant_al)
{
	double	x;
	double	y;
	double	offset;
	int		i;
	int		j;
	int		sup_pixels;

	j = 0;
	offset = (1.0 / ant_al);
	sup_pixels = 0;
	while (j < ant_al)
	{
		i = 0;
		y = ((float)pixel_y + (offset / 2) + (offset * j));
		while (i < ant_al)
		{
			if (ant_al == 1 || (((j % 2 == 0) && (i % 2 == 1))
					|| ((j % 2 == 1) && (i % 2 == 0))))
			{
				x = ((float)pixel_x + (offset / 2) + (offset * i));
				initialize_ray(&main->ray, x, y, &main->cam);
				ray_shooter(&main->ray, main);
				sup_pixels++;
			}
			i++;
		}
		j++;
	}
	fix_aliasing_color(main, sup_pixels);
	return (color_to_int(main->ray.hit.color));
}

void	render_image(t_main	*main, int task, int ant_al)
{
	t_main	copy;
	int		y;
	int		x;
	int		color;

	y = task;
	copy = (t_main) *main;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			copy.ray.hit.color = color_new(0, 0, 0);
			while (ant_al != 1 && x < WIN_W
				&& main->sdl.frame_buffer.mask[((y * WIN_W) + x)] == 0)
				x++;
			if (x == WIN_W)
				break ;
			color = anti_aliasing(&copy, x, y, ant_al);
			main->sdl.frame_buffer.data[((y * WIN_W) + x++)] = color;
		}
		y += NUM_TASKS;
	}
}
