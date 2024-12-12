/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:21:45 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/12 11:48:30 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_vector	ft_scale_3d_vector(
	t_3d_vector vector,
	double scale
)
{
	return ((t_3d_vector){
		vector.x * scale,
		vector.y * scale,
		vector.z * scale,
		vector.color
	});
}

double	ft_get_scale(
	t_map_borders	map_borders
)
{
	int	width;
	int	height;

	width = abs(map_borders.max.x - map_borders.min.x);
	height = abs(map_borders.max.y - map_borders.min.y);
	return (min(
			(WIDTH - WIDTH / 8.0) / width,
			(HEIGHT - HEIGHT / 8.0) / height)
	);
}
