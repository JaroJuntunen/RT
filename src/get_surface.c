/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:56:08 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/19 13:42:41 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"
#include <stdio.h>

static t_tuple	get_spherical(t_tuple obj_space)
{
	t_tuple	map;

	obj_space = tuple_unit(obj_space);
	map.s_xyzw.x = (1 + (atan2(obj_space.s_xyzw.x, obj_space.s_xyzw.z)
			/ M_PI)) * 0.5;
	map.s_xyzw.y = (acos(obj_space.s_xyzw.y) / M_PI);
	return (map);
}

static t_tuple	get_planar(t_tuple obj_space)
{
	t_tuple	map;

	map = point_new((fmod(obj_space.s_xyzw.x, 1.0) * 0.5 + 0.5),
			((fmod(obj_space.s_xyzw.z, 1.0) * 0.5 + 0.5)), 0.0);
	return (map);
}

static t_tuple	get_cylinderic(t_tuple obj_space)
{
	t_tuple	map;

	obj_space = tuple_unit(obj_space);
	map = vector_new(0, 0, 0);
	map.s_xyzw.y = acos(obj_space.s_xyzw.y / obj_space.s_xyzw.x);
	map.s_xyzw.x = obj_space.s_xyzw.z;
	return (map);
}

static t_tuple	get_conic(t_tuple obj_space)
{
	t_tuple	map;

	obj_space = tuple_unit(obj_space);
	map = vector_new(0, 0, 0);
	map.s_xyzw.y = acos(obj_space.s_xyzw.y / obj_space.s_xyzw.x);
	map.s_xyzw.x = obj_space.s_xyzw.z * 2 + 1;
	return (map);
}

t_tuple	get_surface_coordinate(t_hit_record *hit)
{
//	t_tuple temp = hit->surf3_coord;
//	temp.s_xyzw.x *= hit->object->scale.s_xyzw.x;
//	temp.s_xyzw.y *= hit->object->scale.s_xyzw.y;
//	temp.s_xyzw.z *= hit->object->scale.s_xyzw.z;
	if (hit->object->type == SPHERE)
	{
/*		printf("s3c.x : %f s3c.y : %f s3c.z : %f \n loc.x : %f loc.y : %f loc.z : %f\n", \
		temp.a[0], temp.a[1], temp.a[2], hit->local.a[0], hit->local.a[1], hit->local.a[2]);
		exit(1);
*/		return (get_spherical(hit->local));
	}
	if (hit->object->type == PLANE)
		return (get_planar(hit->local));
	if (hit->object->type == CYLINDER)
		return (get_cylinderic(hit->surf3_coord));
	if (hit->object->type == CONE)
		return (get_conic(hit->surf3_coord));
	return (point_new(0.0, 0.0, 0.0));
}
