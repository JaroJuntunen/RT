/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:41:16 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/18 13:20:09 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "object.h"
#include "tuple.h"
#include <math.h>
#include "../include/rt.h"

int	intersect_sphere(t_ray *inc_ray, t_object *obj)
{
	t_abcd			abcd;
	t_vector		sphere_to_ray;
	double			t[2];
	t_ray			ray;

	ray = ray_new_no_malloc(inc_ray->orig, inc_ray->dir);
	ray = ray_transform(inc_ray, &obj->inverse_transform);
	sphere_to_ray = tuple_sub(ray.orig, point_new(0, 0, 0));
	abcd.a = vector_dot(ray.dir, ray.dir);
	abcd.b = 2 * vector_dot(ray.dir, sphere_to_ray);
	abcd.c = vector_dot(sphere_to_ray, sphere_to_ray) - 1;
	abcd.d = calc_discriminant(abcd.a, abcd.b, abcd.c);
	if (abcd.d < 0)
		return (0);
	t[0] = (-(abcd.b) - sqrt(abcd.d)) / (2 * abcd.a);
	t[1] = (-(abcd.b) + sqrt(abcd.d)) / (2 * abcd.a);
	slice(inc_ray, t[0], t[1], obj);
	return (1);
}
