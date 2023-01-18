/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:09:55 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/18 12:21:01 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	slice(t_ray *ray, double t1, double t2, t_object *obj)
{
	double y1;
	double x1;
	double y2;
	double x2;
	
	y1 = ray->orig.s_xyzw.y + t1 * ray->dir.s_xyzw.y;
	x1 = ray->orig.s_xyzw.x + t1 * ray->dir.s_xyzw.x;
	y1 = ray->orig.s_xyzw.y + t1 * ray->dir.s_xyzw.y;
	x1 = ray->orig.s_xyzw.x + t1 * ray->dir.s_xyzw.x;
	
	y2 = ray->orig.s_xyzw.y + t1 * ray->dir.s_xyzw.y;
	x2 = ray->orig.s_xyzw.x + t1 * ray->dir.s_xyzw.x;
	y2 = ray->orig.s_xyzw.y + t1 * ray->dir.s_xyzw.y;
	x2 = ray->orig.s_xyzw.x + t1 * ray->dir.s_xyzw.x;
	intersection_record(ray, t1, obj);
	intersection_record(ray, t2, obj);
}