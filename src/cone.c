/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:36:35 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 13:04:01 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static double	calc_a(t_ray ray)
{
	return (
		(ray.dir.s_xyzw.x * ray.dir.s_xyzw.x)
		- (ray.dir.s_xyzw.y * ray.dir.s_xyzw.y)
		+ (ray.dir.s_xyzw.z * ray.dir.s_xyzw.z));
}

static double	calc_b(t_ray ray)
{
	return (
		(2 * ray.orig.s_xyzw.x * ray.dir.s_xyzw.x)
		- (2 * ray.orig.s_xyzw.y * ray.dir.s_xyzw.y)
		+ (2 * ray.orig.s_xyzw.z * ray.dir.s_xyzw.z));
}

static double	calc_c(t_ray ray)
{
	return (
		(ray.orig.s_xyzw.x * ray.orig.s_xyzw.x)
		- (ray.orig.s_xyzw.y * ray.orig.s_xyzw.y)
		+ (ray.orig.s_xyzw.z * ray.orig.s_xyzw.z));
}

int	intersect_cone(t_ray *inc_ray, t_object *obj)
{
	t_abcd		abcd;
	double		t1;
	double		t2;
	t_ray		ray;

	ray = ray_new_no_malloc(inc_ray->orig, inc_ray->dir);
	ray = ray_transform(inc_ray, &obj->inverse_transform);
	abcd.a = calc_a(ray);
	abcd.b = calc_b(ray);
	abcd.c = calc_c(ray);
	abcd.d = calc_discriminant(abcd.a, abcd.b, abcd.c);
	if (abcd.d < 0)
		return (0);
	t1 = (-(abcd.b) - sqrt(abcd.d)) / (2 * abcd.a);
	t2 = (-(abcd.b) + sqrt(abcd.d)) / (2 * abcd.a);
	slice(inc_ray, t1, t2, obj);
	return (1);
}
