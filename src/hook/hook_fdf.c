/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:01:03 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/20 13:13:31 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_hook(
	int keysym,
	t_fdf *fdf
)
{
	if (keysym == XK_1)
		fdf->projection_mode = PROJ_MODE_ISO;
	else if (keysym == XK_2)
		fdf->projection_mode = PROJ_MODE_PARALLEL;
	else if (keysym == XK_3)
		fdf->projection_mode = PROJ_MODE_ANGULAR;
	else if (keysym == XK_Escape)
	{
		free_fdf(fdf);
		exit(0);
	}
	else
		ft_hook_update_camera(keysym, fdf);
	ft_project_and_draw(fdf, fdf->projection_mode);
	ft_refresh_image(fdf);
	return (0);
}

void	ft_hook_update_camera(
	int keysym,
	t_fdf *fdf
)
{
	if (keysym == XK_W || keysym == XK_s)
		fdf->camera.offset.y -= fdf->scale;
	else if (keysym == XK_S || keysym == XK_a)
		fdf->camera.offset.x += fdf->scale;
	else if (keysym == XK_A || keysym == XK_d)
		fdf->camera.offset.x -= fdf->scale;
	else if (keysym == XK_D || keysym == XK_w)
		fdf->camera.offset.y += fdf->scale;
	else if (keysym == XK_minus || keysym == XK_underscore)
		fdf->camera.fov += .1;
	else if (keysym == XK_plus || keysym == XK_equal)
		fdf->camera.fov -= .1;
	else
		ft_rotate_camera_hook(keysym, fdf);
}

void	ft_rotate_camera_hook(
	int keysym,
	t_fdf *fdf
)
{
	if (keysym == XK_Right)
		fdf->camera.y_deg += CAM_DEG_INCREMENT;
	else if (keysym == XK_Left)
		fdf->camera.y_deg -= CAM_DEG_INCREMENT;
	else if (keysym == XK_Up)
		fdf->camera.x_deg += CAM_DEG_INCREMENT;
	else if (keysym == XK_Down)
		fdf->camera.x_deg -= CAM_DEG_INCREMENT;
	else if (keysym == XK_e)
		fdf->camera.z_deg += CAM_DEG_INCREMENT * 57.2958;
	else if (keysym == XK_q)
		fdf->camera.z_deg -= CAM_DEG_INCREMENT * 57.2958;
}

void	ft_refresh_image(t_fdf *fdf)
{
	ft_info(fdf);
	mlx_put_image_to_window(fdf->mlx_data.mlx, fdf->mlx_data.window,
		fdf->mlx_data.img_data.img, 0, 0);
	ft_info(fdf);
}

int	ft_close_window_hook(t_fdf *fdf)
{
	free_fdf(fdf);
	exit(0);
}
