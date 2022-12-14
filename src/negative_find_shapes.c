/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_find_shapes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:21:47 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/14 15:07:06 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static size_t	loop_move_comparison(t_ray *ray, t_negative *n, size_t neg)
{
	n->j = 0;
	while (n->j < ray->xs.vec.len)
	{
		if (n->j != n->i)
		{
			n->t2 = *(t_intersection *) vec_get(&ray->xs.vec, n->j);
			if (n->t2.object->id == n->t1.object->id && n->t2.t > n->t1.t
				&& n->t2.t > n->t[1])
			{
				n->t[1] = n->t2.t;
				n->i = -1;
				return (n->t2.object->id);
			}
		}
		n->j++;
	}
	return (neg);
}

size_t	move_negative(t_ray *ray, size_t neg_obj_id, t_negative *n,
					t_object *obj)
{
	n->i = 0;
	while (n->i < ray->xs.vec.len)
	{
		n->t1 = *(t_intersection *) vec_get(&ray->xs.vec, n->i);
		if (obj[n->t1.object->id].negative == TRUE && n->t1.t > n->t[0]
			&& n->t1.t < n->t[1])
		neg_obj_id = loop_move_comparison(ray, n, neg_obj_id);
		n->i++;
	}
	return (neg_obj_id);
}

static void	loop_positive_comparison(t_ray *ray, t_negative *n,
									t_intersection *closest_t)
{
	n->j = 0;
	while (n->j < ray->xs.vec.len)
	{
		if (n->j != n->i)
		{
			n->t2 = *(t_intersection *) vec_get(&ray->xs.vec, n->j);
			if (n->t2.object->id == n->t1.object->id && n->t2.t > n->t1.t
				&& n->t2.t > n->t[1] && n->t1.t > closest_t->t)
			{
				closest_t->t = n->t1.t;
				closest_t->i = n->t1.object->id;
			}
		}
		n->j++;
	}
}

int	first_positive_object(t_ray *ray, t_intersection *closest_t,
							t_negative *n, t_object *obj)
{
	n->i = 0;
	while (n->i < ray->xs.vec.len)
	{
		n->t1 = *(t_intersection *) vec_get(&ray->xs.vec, n->i);
		if (obj[n->t1.object->id].negative != TRUE && n->t1.t > n->t[0]
			&& n->t1.t < n->t[1])
			loop_positive_comparison(ray, n, closest_t);
		n->i++;
	}
	if (closest_t->t != -1.0)
		return (1);
	return (0);
}
