/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:39:19 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/09 16:14:18 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**ft_read_map_to_strs(const int map_fd)
{
	char	*line;
	char	*buffer;
	char	*temp;
	char	**map_strs;

	line = get_next_line(map_fd);
	if (!line)
		return (NULL);
	buffer = ft_strdup("");
	if (!buffer)
		return (free(line), NULL);
	while (line)
	{
		temp = buffer;
		buffer = ft_strjoin(buffer, line);
		free(temp);
		free(line);
		if (!buffer)
			return (NULL);
		line = get_next_line(map_fd);
	}
	map_strs = ft_split(buffer, '\n');
	free(buffer);
	return (map_strs);
}

t_map_element	**ft_get_map(char	*file_path)
{
	int	map_fd;

	map_fd = open(file_path, O_RDONLY, 0400);
	if (map_fd < 0)
		return (print_arged_error(ERROR_OPEN_FILE, file_path), NULL);
	return (NULL);
}
