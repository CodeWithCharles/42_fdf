/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:03:09 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/18 18:34:08 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_mouse(
	int x,
	int y,
	t_fdf *fdf
)
{
	fdf->camera.y_deg -= (fdf->mouse.prev_x - x)
		* CAM_DEG_INCREMENT / MOUSE_ROT_DIVISION;
	fdf->camera.x_deg += (fdf->mouse.prev_y - y)
		* CAM_DEG_INCREMENT / MOUSE_ROT_DIVISION;
}

void	ft_translate_mouse(
	int x,
	int y,
	t_fdf *fdf
)
{
	fdf->camera.offset.x += (fdf->mouse.prev_x - x) * fdf->scale
		/ MOUSE_OFFSET_DIVISION;
	fdf->camera.offset.y += (fdf->mouse.prev_y - y) * fdf->scale
		/ MOUSE_OFFSET_DIVISION;
}
