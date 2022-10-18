/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:45:46 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/17 20:34:26 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_abc static	calc_abc_cylinder(t_ray ray,
									t_vec3 cyldir,
									t_vec3 raycyl,
									double radius)
{
	t_abc	abc;

	abc.a = 1 - vec3_dot(ray.dir, cyldir) * vec3_dot(ray.dir, cyldir);
	abc.b = 2 * (vec3_dot(ray.dir, raycyl) - vec3_dot(ray.dir, cyldir)
			* vec3_dot(raycyl, cyldir));
	abc.c = vec3_dot(raycyl, raycyl) - vec3_dot(raycyl, cyldir)
		* vec3_dot(raycyl, cyldir) - radius * radius;
	return (abc);
}

t_vec3	get_cylinder_normal(t_main *main, t_hit_record *hit)
{
	t_vec3	result;
	t_vec3	hypotenuse;
	t_vec3	hit_along_cyldir;

	hypotenuse = vec3_sub(hit->hit_loc, main->obj[hit->clo_obj_id].loc);
	hit_along_cyldir = vec3_ray_at((t_ray){main->obj[hit->clo_obj_id].loc, main->obj[hit->clo_obj_id].rot, *hit},
			vec3_dot(hypotenuse, main->obj[hit->clo_obj_id].rot));
	result = vec3_sub(hit->hit_loc, hit_along_cyldir);
	return (result);
}

double	intersects_cylinder(t_ray *ray, t_object *cylinder)
{
	t_vec3	ray_cyl;
	t_abc	abc;
	double	b2_4ac;

	ray_cyl = vec3_sub(ray->orig, cylinder->loc);
	cylinder->rot = vec3_unit(cylinder->rot);
	abc = calc_abc_cylinder(*ray, cylinder->rot, ray_cyl, cylinder->size);
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac > 0)
		return (quadratic(abc, b2_4ac));
	return (-1);
}