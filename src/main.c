/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:11:19 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/09 17:10:26 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*g_pname;

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf = (t_fdf){};
	g_pname = argv[0];
	if (ft_init_fdf(argc, argv, &fdf) != RET_OK)
		return (RET_ERR);
	return (RET_OK);
}
