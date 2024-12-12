/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:19:57 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/12 13:13:38 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_rad(
	double deg
)
{
	return (deg * M_PI / 180);
}

double	ft_calculate_relative_position(
	t_3d_vector start_point,
	t_3d_vector end_point,
	t_3d_vector current_point
)
{
	double	total_distance;
	double	current_distance;

	total_distance = sqrt(pow(end_point.x - start_point.x, 2)
			+ pow(end_point.y - start_point.y, 2));
	current_distance = sqrt(pow(current_point.x - start_point.x, 2)
			+ pow(current_point.y - start_point.y, 2));
	if (total_distance != 0)
		return (current_distance / total_distance);
	return (1);
}
