/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:23:12 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/11 16:42:05 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_vector	ft_get_3d_vector(
	t_map_element element
)
{
	return ((t_3d_vector){
		element.x,
		element.y,
		element.z,
		element.color
	});
}

t_3d_vector	ft_multiply_vector_by_matrix(
	t_3d_vector v,
	t_3d_matrix m
)
{
	double	*lv;

	lv = (double [3]){v.x, v.y, v.z};
	v.x = lv[0] * m.i.x + lv[1] * m.i.y + lv[2] * m.i.z;
	v.y = lv[0] * m.j.x + lv[1] * m.j.x + lv[2] * m.j.z;
	v.z = lv[0] * m.k.x + lv[1] * m.k.x + lv[2] * m.k.z;
	return (v);
}
