/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:11:19 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 17:04:28 by cpoulain         ###   ########.fr       */
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
	g_pname = argv[0];
	if (ft_init_fdf(argc, argv, &fdf) != RET_OK)
		return (free_fdf(&fdf), RET_ERR);
	ft_start_hook(&fdf);
	mlx_loop(fdf.mlx_data.mlx);
	free_fdf(&fdf);
	return (RET_OK);
}
