/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:19:57 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/11 16:26:32 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_rad(
	double deg
)
{
	return (deg * M_PI / 180);
}