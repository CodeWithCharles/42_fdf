/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:43:11 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 14:48:45 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(
	t_fdf	*fdf
)
{
	if (fdf->map)
		ft_free_2d_map_elements(&(fdf->map));
	if (fdf->mlx)
	{
		if (fdf->window)
			mlx_destroy_window(fdf->mlx, fdf->window);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
}
