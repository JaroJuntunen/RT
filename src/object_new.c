/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:35:17 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 15:24:19 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_object	object_new(int shape_type)
{
	static size_t	id;
	t_object		new_object;

	new_object.loc = point_new(0.0, 0.0, 0.0);
	new_object.up = point_new(0.0, 1.0, 0.0);
	new_object.rot = point_new(0.0, 0.0, 0.0);
	new_object.scale = point_new(1.0, 1.0, 1.0);
	new_object.negative = FALSE;
	new_object.transform = matrix_new_identity(4);
	new_object.id = id;
	id++;
	new_object.loc = point_new(0, 0, 0);
	new_object.type = shape_type;
	new_object.material = material_new();
	new_object.motion = motion_new(FALSE, 1.0, tuple_unit(vector_new(1, 0, 0)));
	new_object.slice_toggle = 0;
	new_object.slice_vector = vector_new(1.0, 0.0, 0.0);
	return (new_object);
}
