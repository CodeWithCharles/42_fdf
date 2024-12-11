/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:36:23 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/11 17:49:48 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_vector	ft_to_iso(t_3d_vector vector, t_fdf *fdf)
{
	(void)fdf;
	return (vector);
}

t_3d_vector	ft_to_parallel(t_3d_vector vector, t_fdf *fdf)
{
	(void)fdf;
	return (vector);
}

t_3d_vector	ft_to_angular(t_3d_vector vector, t_fdf *fdf)
{
	(void)fdf;
	return (vector);
}

void	ft_project_and_draw(
	t_fdf *fdf
)
{
	void	*t_ft_proj;

	if (fdf->projection_mode == 'I')
	{
		t_ft_proj = ft_to_iso;
		ft_draw(fdf, t_ft_proj);
	}
	else if (fdf->projection_mode == 'P')
	{
		t_ft_proj = ft_to_parallel;
		ft_draw(fdf, t_ft_proj);
	}
	else
	{
		t_ft_proj = ft_to_angular;
		ft_draw(fdf, t_ft_proj);
	}
}

void	ft_draw(
	t_fdf *fdf,
	t_3d_vector (*t_ft_proj)(t_3d_vector vector, t_fdf *fdf)
)
{
	(void)fdf;
	(void)t_ft_proj;
}
