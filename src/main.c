/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:11:19 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/06 16:19:48 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*g_pname;

int	main(int argc, char **argv)
{
	g_pname = argv[0];
	if (argc != 2)
		return (print_gen_error(ERROR_BAD_ARG_NUM), RET_ERR);
	return (RET_OK);
}
