/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:25 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 12:12:24 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_2d_map_elements(
	t_map_element ***map
)
{
	size_t	i;

	i = 0;
	while ((*map)[i])
	{
		free((*map)[i]);
		(*map)[i++] = NULL;
	}
	free(*map);
	*map = NULL;
}
