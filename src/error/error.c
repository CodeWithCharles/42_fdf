/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:13:03 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 12:12:59 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_gen_error(
	const char *error
)
{
	fd_printf(STDERR_FILENO, error,
		TERM_RED,
		g_pname,
		TERM_RESET
		);
}

void	print_arged_error(
	const char *error,
	const char *arg
)
{
	fd_printf(STDERR_FILENO, error,
		TERM_RED,
		g_pname,
		arg,
		TERM_RESET
		);
}
