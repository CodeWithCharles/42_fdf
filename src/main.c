/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:11:19 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/18 17:48:19 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*g_pname;

int	main(
	int argc,
	char **argv
)
{
	t_fdf	fdf;

	fdf = (t_fdf){};
	fdf.projection_mode = PROJ_MODE_ISO;
	g_pname = argv[0];
	if (ft_init_fdf(argc, argv, &fdf) != RET_OK)
		return (free_fdf(&fdf), RET_ERR);
	fdf.mouse = (t_mouse){0, 0, 0, 0, 0, 0};
	fdf.scale = ft_get_scale(ft_get_map_borders(1, &fdf));
	fdf.camera.offset = ft_get_offset(ft_get_map_borders(fdf.scale, &fdf));
	ft_project_and_draw(&fdf, fdf.projection_mode);
	ft_refresh_image(&fdf);
	ft_start_hook(&fdf);
	mlx_loop(fdf.mlx_data.mlx);
	free_fdf(&fdf);
	return (RET_OK);
}
