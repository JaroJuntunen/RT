/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:44:22 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 12:14:53 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

double	calc_a(t_ray ray)
{
	return (
		(ray.dir.s_xyzw.x * ray.dir.s_xyzw.x)
		+ (ray.dir.s_xyzw.z * ray.dir.s_xyzw.z));
}

double	calc_b(t_ray ray)
{
	return (
		(2 * ray.orig.s_xyzw.x * ray.dir.s_xyzw.x)
		+ (2 * ray.orig.s_xyzw.z * ray.dir.s_xyzw.z));
}

double	calc_c(t_ray ray)
{
	return (
		(ray.orig.s_xyzw.x * ray.orig.s_xyzw.x)
		+ (ray.orig.s_xyzw.z * ray.orig.s_xyzw.z) - 1);
}

int	intersect_cylinder(t_ray *inc_ray, t_object *obj)
{
	t_abcd		abcd;
	double		t1;
	double		t2;
	t_ray		ray;

	ray = ray_new_no_malloc(inc_ray->orig, inc_ray->dir);
	ray = ray_transform(inc_ray, &obj->inverse_transform);
	abcd.a = calc_a(ray);
	if (nearly_equal(abcd.a, 0))
		return (0);
	abcd.b = calc_b(ray);
	abcd.c = calc_c(ray);
	abcd.d = calc_discriminant(abcd.a, abcd.b, abcd.c);
	if (abcd.d < 0)
		return (0);
	t1 = (-(abcd.b) - sqrt(abcd.d)) / (2 * abcd.a);
	t2 = (-(abcd.b) + sqrt(abcd.d)) / (2 * abcd.a);
	slice(ray, t1, t2, obj);
	return (1);
}
