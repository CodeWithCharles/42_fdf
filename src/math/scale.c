/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:21:45 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/20 12:11:06 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
