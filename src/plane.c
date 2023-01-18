/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:23:05 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 13:04:15 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	intersect_plane(t_ray *inc_ray, t_object *obj)
{
	double			t;
	t_ray			ray;

	ray = ray_new_no_malloc(inc_ray->orig, inc_ray->dir);
	ray = ray_transform(inc_ray, &obj->inverse_transform);
	if (fabs(ray.dir.s_xyzw.y) < EPSILON)
		return (0);
	t = ((-ray.orig.s_xyzw.y) / ray.dir.s_xyzw.y);
	if (t < 0)
		return (0);
	slice(inc_ray, t, 0.0, obj);
	return (1);
}
