/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:00:30 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/20 13:00:23 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_string_put(
	t_fdf *fdf,
	t_2d_vector coor,
	uint32_t color,
	char *str
)
{
	mlx_string_put(
		fdf->mlx_data.mlx,
		fdf->mlx_data.window,
		coor.x,
		coor.y,
		color,
		str);
}

void	ft_info_cam(
	t_fdf *fdf
)
{
	char	*str;

	ft_mlx_string_put(fdf, (t_2d_vector){10, 58}, INF_COLOR, "---- CAM ----");
	ft_mlx_string_put(fdf, (t_2d_vector){10, 70}, INF_COLOR, "Depth :");
	str = ft_dtoa(fdf->camera.fov, 1);
	ft_mlx_string_put(fdf, (t_2d_vector){90, 70}, INF_COLOR, str);
	ft_mlx_string_put(fdf, (t_2d_vector){10, 82}, INF_COLOR, "Offset :");
	ft_mlx_string_put(fdf, (t_2d_vector){10, 94}, INF_COLOR, "  X :");
	(free(str), str = ft_dtoa(fdf->camera.offset.x, 2));
	ft_mlx_string_put(fdf, (t_2d_vector){90, 94}, INF_COLOR, str);
	ft_mlx_string_put(fdf, (t_2d_vector){10, 106}, INF_COLOR, "  Y :");
	(free(str), str = ft_dtoa(fdf->camera.offset.y, 2));
	ft_mlx_string_put(fdf, (t_2d_vector){90, 106}, INF_COLOR, str);
	ft_mlx_string_put(fdf, (t_2d_vector){10, 118}, INF_COLOR, "rX :");
	(free(str), str = ft_dtoa(fdf->camera.x_deg * 57.2958, 5));
	ft_mlx_string_put(fdf, (t_2d_vector){90, 118}, INF_COLOR, str);
	ft_mlx_string_put(fdf, (t_2d_vector){10, 130}, INF_COLOR, "rY :");
	(free(str), str = ft_dtoa(fdf->camera.y_deg * 57.2958, 5));
	ft_mlx_string_put(fdf, (t_2d_vector){90, 130}, INF_COLOR, str);
	ft_mlx_string_put(fdf, (t_2d_vector){10, 142}, INF_COLOR, "rZ :");
	(free(str), str = ft_dtoa(fdf->camera.z_deg * 57.2958, 5));
	ft_mlx_string_put(fdf, (t_2d_vector){90, 142}, INF_COLOR, str);
	free(str);
}

void	ft_info(
	t_fdf *fdf
)
{
	char	proj_mode[2];
	char	*str;

	ft_mlx_string_put(fdf, (t_2d_vector){10, 10}, INF_COLOR, "---- FDF ----");
	ft_mlx_string_put(fdf, (t_2d_vector){10, 22}, INF_COLOR, "Projection :");
	proj_mode[1] = '\0';
	proj_mode[0] = fdf->projection_mode;
	ft_mlx_string_put(fdf, (t_2d_vector){90, 22}, INF_COLOR, proj_mode);
	ft_mlx_string_put(fdf, (t_2d_vector){10, 34}, INF_COLOR, "Scale :");
	str = ft_itoa((int)fdf->scale);
	ft_mlx_string_put(fdf, (t_2d_vector){90, 34}, INF_COLOR, str);
	free(str);
	ft_info_cam(fdf);
}
