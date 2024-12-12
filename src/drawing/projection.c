/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:36:23 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/12 13:30:23 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_vector	ft_to_iso(t_3d_vector vector, t_fdf *fdf)
{
	double	x_deg;
	double	z_deg;

	fdf->camera.fov = 1;
	vector.z *= fdf->camera.fov;
	z_deg = 45;
	x_deg = atan(sqrt(2));
	vector = ft_multiply_vector_by_matrix(vector,
			ft_get_rot_matrix(z_deg, 'z'));
	vector = ft_multiply_vector_by_matrix(vector,
			ft_get_rot_matrix(x_deg, 'x'));
	fdf->camera.z_deg = z_deg;
	fdf->camera.x_deg = x_deg;
	fdf->camera.y_deg = 0;
	return (vector);
}

t_3d_vector	ft_to_parallel(t_3d_vector vector, t_fdf *fdf)
{
	vector.z *= fdf->camera.fov;
	fdf->camera.z_deg = 0;
	fdf->camera.x_deg = 0;
	fdf->camera.y_deg = 0;
	return (vector);
}

t_3d_vector	ft_to_angular(t_3d_vector vector, t_fdf *fdf)
{
	vector.z *= fdf->camera.fov;
	vector = ft_multiply_vector_by_matrix(vector,
			ft_get_rot_matrix(fdf->camera.z_deg, 'z'));
	vector = ft_multiply_vector_by_matrix(vector,
			ft_get_rot_matrix(fdf->camera.x_deg, 'x'));
	vector = ft_multiply_vector_by_matrix(vector,
			ft_get_rot_matrix(fdf->camera.y_deg, 'y'));
	return (vector);
}

void	ft_project_and_draw(
	t_fdf *fdf,
	char proj_mode
)
{
	void	*t_ft_proj;

	if (proj_mode == PROJ_MODE_ISO)
	{
		t_ft_proj = ft_to_iso;
		ft_draw(fdf, t_ft_proj);
	}
	else if (proj_mode == PROJ_MODE_PARALLEL)
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
