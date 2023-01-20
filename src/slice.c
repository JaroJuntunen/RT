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
			ray->orig.s_xyzw.x + ray->dir.s_xyzw.x * time,
			ray->orig.s_xyzw.y + ray->dir.s_xyzw.y * time,
			ray->orig.s_xyzw.z + ray->dir.s_xyzw.z * time);
	return (hit);
}

int	in_bounds(t_vector hit, t_vector p_bounds, t_vector n_bounds, t_object *obj)
{
	if (obj->slice_toggle == 1)
	{
		if ((p_bounds.s_xyzw.x == 0 || hit.s_xyzw.x < p_bounds.s_xyzw.x) && \
			(n_bounds.s_xyzw.x == 0 || hit.s_xyzw.x > n_bounds.s_xyzw.x) && \
			(p_bounds.s_xyzw.z == 0 || hit.s_xyzw.z < p_bounds.s_xyzw.z) && \
			(n_bounds.s_xyzw.z == 0 || hit.s_xyzw.z > n_bounds.s_xyzw.z))
		{
			if (obj->type == PLANE)
				return (TRUE);
			else if ((p_bounds.s_xyzw.y == 0 || \
				hit.s_xyzw.y < p_bounds.s_xyzw.y) && (n_bounds.s_xyzw.y == 0 \
				|| hit.s_xyzw.y > n_bounds.s_xyzw.y))
				return (TRUE);
		}
	}
	else
		return (TRUE);
	return (FALSE);
}

int	in_disc(t_vector hit, t_object *obj)
{
	if (obj->type == PLANE && obj->disc_toggle == 1 && \
		tuple_mag(hit) > obj->size * M_PI)
		return (FALSE);
	return (TRUE);
}

int	slice(t_ray *ray_save_hits, double t[2], t_object *obj, t_ray *ray)
{
	t_vector	local_hit;

	local_hit = get_local_hit(ray, t[0]);
	ray_save_hits->hit.local = local_hit;
	if ((in_disc(local_hit, obj)) && (in_bounds(local_hit, obj->slice_pos, \
	obj->slice_neg, obj)))
	{
		intersection_record(ray_save_hits, t[0], obj);
		if (obj->type != PLANE)
			intersection_record(ray_save_hits, t[1], obj);
		return (TRUE);
	}
	local_hit = get_local_hit(ray, t[1]);
	if (obj->type != PLANE && in_bounds(local_hit, obj->slice_pos, \
	obj->slice_neg, obj))
	{
		intersection_record(ray_save_hits, t[1], obj);
		return (TRUE);
	}
	return (FALSE);
}
