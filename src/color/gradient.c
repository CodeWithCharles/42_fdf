/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:23:33 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/12 12:52:59 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	ft_grad_pt_color(
	uint32_t a,
	uint32_t b,
	double position
)
{
	t_color	a_rgba;
	t_color	b_rgba;
	t_color	color;

	a_rgba = ft_rgba_to_color(a);
	b_rgba = ft_rgba_to_color(b);
	color.r = round(a_rgba.r * (1 - position) + b_rgba.r * position);
	color.g = round(a_rgba.g * (1 - position) + b_rgba.g * position);
	color.b = round(a_rgba.b * (1 - position) + b_rgba.b * position);
	color.a = round(a_rgba.a * (1 - position) + b_rgba.a * position);
	return (ft_rgba_to_uint32_t(color.r, color.g, color.b, color.a));
}

uint32_t	ft_get_grad(
	t_3d_vector start,
	t_3d_vector end,
	t_3d_vector current
)
{
	double	position;

	position = ft_calculate_relative_position(start, end, current);
	return (ft_grad_pt_color(start.color, end.color, position));
}
