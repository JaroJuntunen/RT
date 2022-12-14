/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:16:21 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/12 15:52:50 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_intersection	find_closest_intersection(t_intersections *xs)
{
	t_intersection	closest_t;
	size_t			i;
	t_intersection	t;

	i = 0;
	closest_t.t = INFINITY;
	while (i < xs->vec.len)
	{
		t = *(t_intersection *) vec_get(&xs->vec, i);
		if (t.t < closest_t.t)
		{
			closest_t = t;
			closest_t.i = (t.object->id);
		}
		i++;
	}
	return (closest_t);
}
