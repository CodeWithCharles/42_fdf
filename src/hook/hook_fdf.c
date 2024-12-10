/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:01:03 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 17:48:59 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_hook(
	int keysym,
	t_fdf *fdf
)
{
	if (keysym == XK_Escape)
	{
		ft_printf("%s%s:\tThe %d key (ESC) has been pressed.\n%s",
			TERM_RED, g_pname, keysym, TERM_RESET);
		free_fdf(fdf);
		exit(0);
	}
	ft_hook_update_camera(keysym, fdf);
	ft_refresh_image(fdf);
	return (0);
}

void	ft_hook_update_camera(
	int keysym,
	t_fdf *fdf
)
{
	if (keysym == XK_W || keysym == XK_w)
		fdf->camera.offset.y -= fdf->scale;
	else if (keysym == XK_S || keysym == XK_s)
		fdf->camera.offset.x += fdf->scale;
	else if (keysym == XK_A || keysym == XK_a)
		fdf->camera.offset.x -= fdf->scale;
	else if (keysym == XK_D || keysym == XK_d)
		fdf->camera.offset.y += fdf->scale;
	else if (keysym == XK_Right)
		fdf->camera.y_deg += CAM_DEG_INCREMENT;
	else if (keysym == XK_Left)
		fdf->camera.y_deg -= CAM_DEG_INCREMENT;
	else if (keysym == XK_Up)
		fdf->camera.x_deg += CAM_DEG_INCREMENT;
	else if (keysym == XK_Down)
		fdf->camera.x_deg -= CAM_DEG_INCREMENT;
	else if (keysym == XK_minus || keysym == XK_underscore)
	{
		if (fdf->scale > FDF_MIN_SCALE)
			fdf->scale -= FDF_SCALE_INCREMENT;
	}
	else if (keysym == XK_plus || keysym == XK_equal)
		if (fdf->scale < FDF_MAX_SCALE)
			fdf->scale += FDF_SCALE_INCREMENT;
}

void	ft_refresh_image(t_fdf *fdf)
{
	for (int y = 0; y < HEIGHT; ++y)
		for (int x = 0; x < WIDTH; ++x)
			ft_put_pixel(&fdf->mlx_data.img_data, x, y, 0xff);
	mlx_put_image_to_window(fdf->mlx_data.mlx, fdf->mlx_data.window,
		fdf->mlx_data.img_data.img, 0, 0);
}

int	ft_mouse_hook(
	int keysym,
	int x,
	int y,
	t_fdf *fdf
)
{
	(void)x;
	(void)y;
	if (keysym == MOUSE_SCROLL_UP)
		fdf->camera.fov += .1;
	else if (keysym == MOUSE_SCROLL_DOWN)
		fdf->camera.fov -= .1;
	return (0);
}
