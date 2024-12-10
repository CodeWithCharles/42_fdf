/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:11:19 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 14:48:53 by cpoulain         ###   ########.fr       */
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
	free_fdf(&fdf);
	return (RET_OK);
}
