/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:43:11 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 14:59:33 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(
	t_fdf	*fdf
)
{
	if (fdf->map)
		ft_free_2d_map_elements(&(fdf->map));
	if (fdf->mlx_data.mlx)
	{
		if (fdf->mlx_data.window)
			mlx_destroy_window(fdf->mlx_data.mlx, fdf->mlx_data.window);
		mlx_destroy_display(fdf->mlx_data.mlx);
		free(fdf->mlx_data.mlx);
	}
}
