/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:41:11 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/18 18:29:47 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_mouse_pressed_hook(
	int button,
	int x,
	int y,
	t_fdf *fdf
)
{
	if (button == MOUSE_RIGHT_CLICK || button == MOUSE_LEFT_CLICK)
	{
		fdf->mouse.x = x;
		fdf->mouse.y = y;
		if (button == MOUSE_LEFT_CLICK)
			fdf->mouse.left_pressed = 1;
		if (button == MOUSE_RIGHT_CLICK)
			fdf->mouse.right_pressed = 1;
		return (0);
	}
	else if (button == MOUSE_SCROLL_UP)
		fdf->camera.fov += .1;
	else if (button == MOUSE_SCROLL_DOWN)
		fdf->camera.fov -= .1;
	ft_project_and_draw(fdf, fdf->projection_mode);
	ft_refresh_image(fdf);
	return (0);
}

int	ft_mouse_moved_hook(
	int x,
	int y,
	t_fdf *fdf
)
{
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		fdf->mouse.prev_x = fdf->mouse.x;
		fdf->mouse.prev_y = fdf->mouse.y;
		fdf->mouse.x = x;
		fdf->mouse.y = y;
		if (fdf->mouse.left_pressed)
			ft_rotate_mouse(x, y, fdf);
		if (fdf->mouse.right_pressed)
			ft_translate_mouse(x, y, fdf);
		if (fdf->mouse.left_pressed || fdf->mouse.right_pressed)
		{
			ft_project_and_draw(fdf, fdf->projection_mode);
			ft_refresh_image(fdf);
		}
	}
	return (0);
}

int	ft_mouse_released_hook(
	int button,
	int x,
	int y,
	t_fdf *fdf
)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT_CLICK)
		fdf->mouse.left_pressed = 0;
	if (button == MOUSE_RIGHT_CLICK)
		fdf->mouse.right_pressed = 0;
	return (0);
}
