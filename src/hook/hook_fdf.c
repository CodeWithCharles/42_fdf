/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:01:03 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 15:16:28 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_hook(
	int keysym,
	t_fdf *fdf
)
{
	if (keysym == XK_Escape)
	{
		ft_printf("%s%s:\tThe %d key (ESC) has been pressed.\n%s",
			TERM_RED, g_pname, keysym, TERM_RESET);
		free_fdf(fdf);
		exit(0);
	}
	ft_printf("%s%s:\tThe %d key has been pressed.\n%s",
		TERM_GREEN, g_pname, keysym, TERM_RESET);
	return (0);
}
