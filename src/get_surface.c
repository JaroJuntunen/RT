/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:56:08 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 19:40:52 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_tuple	normalize(t_tuple tuple)
{
	double mag;
	double inv_mag;

	mag = tuple_mag(tuple);
	if (mag > 0)
	{
		inv_mag = 1 / mag;
		tuple.s_xyzw.x *= inv_mag;
		tuple.s_xyzw.y *= inv_mag;
		tuple.s_xyzw.z *= inv_mag;
	}
	return (tuple);
}

static t_tuple	get_spherical(t_tuple obj_space)
{
	t_tuple	map;
	obj_space = normalize(obj_space);
	
	map.s_xyzw.x = (atan2(obj_space.s_xyzw.x, obj_space.s_xyzw.z) / (2 * M_PI) + 0.5);
	map.s_xyzw.y = (acos((obj_space.s_xyzw.y) / 1) / M_PI);
	return (map);
}

static t_tuple	get_planar(t_tuple obj_space)
{
	t_tuple	map;

	map = point_new(fmod(obj_space.s_xyzw.x, 100.0), fmod(obj_space.s_xyzw.z, 100.0), 0.0);
	return (map);
}

static t_tuple	get_cylindrical(t_tuple obj_space)
{
	t_tuple	polar;

	polar = point_new(0.0, 0.0, 0.0);
	polar.s_xyzw.x = 1 - (atan2(obj_space.s_xyzw.x, obj_space.s_xyzw.z)
			/ (2 * M_PI) + 0.5);
	polar.s_xyzw.y = obj_space.s_xyzw.y - ft_floor(obj_space.s_xyzw.y);
	return (polar);
}

t_tuple	get_surface_coordinate(t_hit_record *hit)
{
	if (hit->object->type == SPHERE)
		return (get_spherical(hit->surf3_coord));
	if (hit->object->type == PLANE)
		return (get_planar(hit->surf3_coord));
	if (hit->object->type == CYLINDER)
		return (get_cylindrical(hit->surf3_coord));
	return (point_new(0.0, 0.0, 0.0));
}