/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:42:44 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 12:12:19 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_len_2d_array(
	const char **array
)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

size_t	ft_len_3d_array(
	const char ***array
)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_free_2d_array(
	char ***array
)
{
	size_t	i;

	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i++] = NULL;
	}
	free(*array);
	*array = NULL;
}

void	ft_free_3d_array(
	char ****array
)
{
	size_t	i;

	i = 0;
	while ((*array)[i])
	{
		ft_free_2d_array((*array)[i]);
		(*array)[i++] = NULL;
	}
	free(*array);
	*array = NULL;
}
