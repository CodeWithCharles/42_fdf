/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:08:15 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/12 13:11:55 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map_borders	ft_get_map_borders(
	double s,
	t_fdf *fdf
)
{
	int				i;
	int				j;
	t_3d_vector		p;
	t_map_borders	map_borders;

	map_borders.min = (t_2d_vector){0, 0};
	map_borders.max = (t_2d_vector){0, 0};
	i = -1;
	while (fdf->map[++i])
	{
		j = -1;
		while (!fdf->map[i][++j].is_end)
		{
			p = ft_to_iso(ft_scale(ft_get_3d_vector(fdf->map[i][j]), s), fdf);
			if (floor(p.x) < map_borders.min.x)
				map_borders.min.x = floor(p.x);
			else if (ceil(p.x) > map_borders.max.x)
				map_borders.max.x = ceil(p.x);
			if (floor(p.y) < map_borders.min.y)
				map_borders.min.y = floor(p.y);
			else if (ceil(p.y) > map_borders.max.y)
				map_borders.max.y = ceil(p.y);
		}
	}
	return (map_borders);
}
