/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:09:55 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/18 15:25:01 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static t_vector	get_local_hit(t_ray *ray, double time)
{
	t_vector	hit;

	hit = vector_new(
			ray->orig.s_xyzw.x + time * ray->dir.s_xyzw.x,
			ray->orig.s_xyzw.y + time * ray->dir.s_xyzw.y,
			ray->orig.s_xyzw.z + time * ray->dir.s_xyzw.z);
	return (hit);
}

void	slice(t_ray *ray_save_hits, double t1, double t2, t_object *obj)
{
	t_vector	local_hit;
	double		dot;

	local_hit = get_local_hit(ray_save_hits, t1);
	dot = vector_dot(obj->slice_vector, local_hit);
	if (obj->slice_toggle == 0 || dot < 1.0)
		intersection_record(ray_save_hits, t1, obj);
	if (obj->type != PLANE)
	{
		local_hit = get_local_hit(ray_save_hits, t2);
		dot = vector_dot(obj->slice_vector, local_hit);
		if (obj->slice_toggle == 0 || dot < 1.0)
			intersection_record(ray_save_hits, t2, obj);
	}
}
