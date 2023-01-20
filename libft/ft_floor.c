/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:06:06 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 13:06:22 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_floor(double num)
{
	float	neg;

	neg = 1;
	if (num == 0)
		return (0.0);
	if (num < 0)
	{
		neg = -1;
		num *= -1;
		if (num > 0)
			num += 1.0;
	}
	num = (int)num;
	return (num * neg);
}
