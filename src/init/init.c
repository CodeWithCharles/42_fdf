/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:22:08 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/09 15:52:53 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_init_fdf(int argc, char **argv, t_fdf *fdf)
{
	if (argc != 2)
		return (print_gen_error(ERROR_BAD_ARG_NUM), RET_ERR);
	if (ft_validate_file_name(argv[1]) != RET_OK)
		return (print_gen_error(ERROR_BAD_FILE_NAME), RET_ERR);
	(void)fdf;
	return (RET_OK);
}
