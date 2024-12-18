/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:28:47 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/18 18:14:03 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_start_hook(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_data.window, 2, (1L << 0), ft_hook, fdf);
	mlx_hook(fdf->mlx_data.window, 4, (1L << 2), ft_mouse_pressed_hook, fdf);
	mlx_hook(fdf->mlx_data.window, 5, (1L << 3), ft_mouse_released_hook, fdf);
	mlx_hook(fdf->mlx_data.window, 6, (1L << 6), ft_mouse_moved_hook, fdf);
}
