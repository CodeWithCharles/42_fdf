/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:28:47 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/12 14:14:25 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_start_hook(t_fdf *fdf)
{
	mlx_mouse_hook(fdf->mlx_data.window, ft_mouse_hook, fdf);
	mlx_key_hook(fdf->mlx_data.window, ft_hook, fdf);
}
