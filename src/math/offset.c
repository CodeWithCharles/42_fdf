/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:15:37 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/12 13:55:59 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_offset	ft_get_offset(
	t_map_borders map_borders
)
{
	int	width;
	int	height;
	int	offset_x;
	int	offset_y;

	width = abs(map_borders.max.x - map_borders.min.x);
	height = abs(map_borders.max.y - map_borders.min.y);
	offset_x = round((WIDTH - width) / 2.0);
	offset_y = round((HEIGHT - height) / 2.0);
	if (map_borders.min.x < 0)
		offset_x += abs((int)(round(map_borders.min.x)));
	if (map_borders.min.y < 0)
		offset_y += abs((int)(round(map_borders.min.y)));
	return ((t_offset){offset_x, offset_y});
}
