/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:29:11 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/12 12:59:06 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_pixel(
	t_img_data *img,
	int x,
	int y,
	int color
)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

void	ft_prepare_points_for_plot(
	t_3d_vector *p0,
	t_3d_vector *p1,
	int			*is_steep
)
{
	t_3d_vector	temp;

	*is_steep = fabs(p1->y - p0->y) > fabs (p1->x - p0->x);
	if (*is_steep)
	{
		temp.x = p0->x;
		temp.y = p0->y;
		p0->x = temp.y;
		p0->y = temp.x;
		temp.x = p1->x;
		temp.y = p1->y;
		p1->x = temp.y;
		p1->y = temp.x;
	}
	if (p0->x > p1->x)
	{
		temp = *p0;
		*p0 = *p1;
		*p1 = temp;
	}
}

void	ft_plot_line(
	t_3d_vector p0,
	t_3d_vector p1,
	t_img_data	*img_data
)
{
	t_plotter	plt;
	t_3d_vector	coor;
	int			is_steep;

	ft_prepare_points_for_plot(&p0, &p1, &is_steep);
	plt = (t_plotter){p1.x - p0.x, fabs(p1.y - p0.y), 1, 0};
	if (p1.y < p0.y)
		plt.yi = -1;
	plt.d = (2 * plt.dy) - plt.dx;
	coor = p0;
	while (coor.x <= p1.x)
	{
		if (is_steep)
			ft_put_pixel(img_data, coor.y, coor.x, ft_get_grad(p0, p1, coor));
		else
			ft_put_pixel(img_data, coor.x, coor.y, ft_get_grad(p0, p1, coor));
		if (plt.d)
		{
			coor.y += plt.yi;
			plt.d -= 2 * plt.dx;
		}
		plt.d += 2 * plt.dy;
		coor.x++;
	}
}

void	ft_draw(
	t_fdf *fdf,
	t_3d_vector (*t_ft_proj)(t_3d_vector vector, t_fdf *fdf)
)
{
	size_t		i;
	size_t		j;
	t_3d_vector	point1;

	i = -1;
	while (fdf->map[++i])
	{
		j = -1;
		while (!fdf->map[i][++j].is_end)
		{
			point1 = ft_scale_and_offset(
					ft_get_3d_vector(fdf->map[i][j]), fdf, t_ft_proj);
			if (!fdf->map[i][j + 1].is_end)
				ft_plot_line(point1,
					ft_scale_and_offset(ft_get_3d_vector(fdf->map[i][j + 1]),
						fdf, t_ft_proj), &fdf->mlx_data.img_data);
			if (fdf->map[i + 1])
				ft_plot_line(point1,
					ft_scale_and_offset(ft_get_3d_vector(fdf->map[i + 1][j]),
						fdf, t_ft_proj), &fdf->mlx_data.img_data);
		}
	}
}
