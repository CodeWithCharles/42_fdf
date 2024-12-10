/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:22:08 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 14:30:34 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_init_fdf(
	int argc,
	char **argv,
	t_fdf *fdf
)
{
	if (argc != 2)
		return (print_gen_error(ERROR_BAD_ARG_NUM), RET_ERR);
	if (ft_validate_file_name(argv[1]) != RET_OK)
		return (print_gen_error(ERROR_BAD_FILE_NAME), RET_ERR);
	fdf->map = ft_get_map(argv[1]);
	if (!fdf->map)
		return (print_gen_error(ERROR_PARSING_MAP), RET_ERR);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (print_gen_error(ERROR_INIT_MLX), RET_ERR);
	fdf->window = mlx_new_window(fdf->mlx, HEIGHT, WIDTH, "Fil de Fer");
	if (!fdf->window)
		return (print_gen_error(ERROR_CREATING_WINDOW), RET_ERR);
	return (RET_OK);
}
