/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:39:19 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 12:11:50 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**ft_read_map_to_strs(
	const int map_fd
)
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

char	***ft_map_strs_to_split(
	char **map_strs
)
{
	size_t	i;
	char	***map_strs_elements;

	if (!map_strs)
		return (NULL);
	map_strs_elements = ft_calloc((ft_len_2d_array(map_strs) + 1),
			sizeof (char **));
	if (!map_strs_elements)
		return (ft_free_2d_array(&map_strs), NULL);
	i = 0;
	while (map_strs[i])
	{
		map_strs_elements[i] = ft_split(map_strs[i], ' ');
		if (!map_strs_elements)
			return (ft_free_3d_array(&map_strs_elements),
				ft_free_2d_array(&map_strs), NULL);
		i++;
	}
	return (ft_free_2d_array(&map_strs), map_strs_elements);
}

t_map_element	**ft_alloc_map_elems_from_3d_array(
	char ***map_strs_elements
)
{
	size_t			i;
	t_map_element	**map_elements;

	if (!map_strs_elements)
		return (NULL);
	map_elements = ft_calloc(ft_len_3d_array(map_strs_elements) + 1,
			sizeof(t_map_element *));
	if (!map_elements)
		return (ft_free_3d_array(&map_strs_elements), NULL);
	i = 0;
	while (map_strs_elements[i])
	{
		map_elements[i] = ft_calloc(ft_len_2d_array(map_strs_elements[i]) + 1,
				sizeof(t_map_element));
		if (!map_elements[i++])
			return (ft_free_3d_array(&map_strs_elements),
				ft_free_2d_map_elements(&map_elements), NULL);
	}
	return ();
}

t_map_element	**ft_parse_2d_map_element_from_strs(
	char ***map_strs_elements,
	t_map_element **map_elements
)
{

}

t_map_element	**ft_get_map(
	char	*file_path
)
{
	int	map_fd;

	map_fd = open(file_path, O_RDONLY, 0400);
	if (map_fd < 0)
		return (print_arged_error(ERROR_OPEN_FILE, file_path), NULL);
	return (NULL);
}
