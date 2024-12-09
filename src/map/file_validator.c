/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:23:52 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/09 15:53:22 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_validate_file_name(char *file_name)
{
	size_t	file_name_len;

	file_name_len = ft_strlen(file_name);
	if (file_name_len < 4)
		return (RET_ERR);
	if (ft_strncmp(&file_name[file_name_len - 4], FILE_EXT, sizeof(FILE_EXT)))
		return (RET_ERR);
	return (RET_OK);
}
