/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:54:58 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 14:20:19 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "rt.h"
#include "object.h"

t_light	point_light_new(t_point location, t_color intensity)
{
	t_light	light;

	light.type = POINT;
	light.intensity = intensity;
	light.location = location;
	light.blocked = 0;
	return (light);
}

t_light	sun_light_new(t_point direction, t_color intensity)
{
	t_light	light;

	light.type = SUN;
	light.intensity = intensity;
	light.direction = direction;
	light.blocked = 0;
	return (light);
}

t_light	spotlight_new(
			t_point direction,
			t_point location,
			t_color intensity)
{
	t_light	light;

	light.type = POINT;
	light.direction = tuple_unit(direction);
	light.intensity = intensity;
	light.location = location;
	light.blocked = 0;
	return (light);
}
