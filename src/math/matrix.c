/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:52:25 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/11 16:40:14 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_matrix	ft_get_matrix_x(
	double deg
)
{
	return ((t_3d_matrix){
		(t_3d_vector){1, 0, 0, 0},
		(t_3d_vector){0, cos(deg), -sin(deg), 0},
		(t_3d_vector){0, sin(deg), cos(deg), 0}
	});
}

t_3d_matrix	ft_get_matrix_y(
	double deg
)
{
	return ((t_3d_matrix){
		(t_3d_vector){cos(deg), 0, -sin(deg), 0},
		(t_3d_vector){0, 1, 0, 0},
		(t_3d_vector){sin(deg), 0, cos(deg), 0}
	});
}

t_3d_matrix	ft_get_matrix_z(
	double deg
)
{
	return ((t_3d_matrix){
		(t_3d_vector){cos(ft_rad(deg)), -sin(ft_rad(deg)), 0, 0},
		(t_3d_vector){sin(ft_rad(deg)), cos(ft_rad(deg)), 0, 0},
		(t_3d_vector){0, 0, 1, 0}
	});
}

t_3d_matrix	ft_get_matrix_i(void)
{
	return ((t_3d_matrix){
		(t_3d_vector){1, 0, 0, 0},
		(t_3d_vector){0, 1, 0, 0},
		(t_3d_vector){0, 0, 1, 0}
	});
}

t_3d_matrix	ft_get_rot_matrix(
	double deg,
	char axis
)
{
	if (axis == 'x')
		return (ft_get_matrix_x(deg));
	else if (axis == 'y')
		return (ft_get_matrix_y(deg));
	else if (axis == 'z')
		return (ft_get_matrix_z(deg));
	else
		return (ft_get_matrix_i());
}
