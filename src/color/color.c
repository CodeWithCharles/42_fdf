/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:13:44 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 12:13:25 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

uint32_t	get_color_from_str(
	char *str
)
{
	t_color			color;
	const size_t	str_len = ft_strlen(str + 2);

	if (str && str + 2)
	{
		color = rgba_to_color(ft_atoi_base(str + 2, 16));
		if (str_len > 0 && str_len < 7)
			color.a = 0xFF;
		return (rgba_to_uint32_t(color.r, color.g, color.b, color.a));
	}
	return (rgba_to_uint32_t(0xFF, 0xFF, 0xFF, 0xFF));
}

uint32_t	rgba_to_uint32_t(
	int r,
	int g,
	int b,
	int a
)
{
	if (ENDIANESS == 0)
		return (a << 24 | b << 16 | g << 8 | r);
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	rgba_to_color(
	uint32_t rgba
)
{
	t_color	color;

	color = (t_color){0, 0, 0, 0};
	if (rgba > 0xFFFFFF)
		color.a = 8;
	color.r = (rgba >> (16 + color.a)) & 0xFF;
	color.g = (rgba >> (8 + color.a)) & 0xFF;
	color.b = (rgba >> color.a) & 0xFF;
	if (color.a)
		color.a = rgba & 0xFF;
	return (color);
}
