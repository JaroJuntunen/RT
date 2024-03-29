/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearly_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/23 12:31:47 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	nearly_equal(double a, double b)
{
	if (fabs((a - b)) < EPSILON)
		return (1);
	return (0);
}
