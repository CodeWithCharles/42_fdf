/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:29:11 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/17 17:08:32 by cpoulain         ###   ########.fr       */
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

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

void	ft_plot_line_low(
	t_3d_vector p0,
	t_3d_vector p1,
	t_img_data *img
)
{
	t_plotter	plt;
	t_3d_vector	coor;

	plt.dx = p1.x - p0.x;
	plt.dy = p1.y - p0.y;
	plt.yi = 1;
	if (plt.dy < 0)
	{
		plt.yi = -1;
		plt.dy *= -1;
	}
	plt.d = (2 * plt.dy) - plt.dx;
	coor.x = p0.x;
	coor.y = p0.y;
	while (coor.x <= p1.x)
	{
		ft_put_pixel(img, coor.x, coor.y, ft_get_grad(p0, p1, coor));
		if (plt.d > 0)
		{
			coor.y += plt.yi;
			plt.d += -2 * plt.dx;
		}
		plt.d += 2 * plt.dy;
		coor.x++;
	}
}

void	ft_plot_line_high(
	t_3d_vector p0,
	t_3d_vector p1,
	t_img_data *img
)
{
	t_plotter	plt;
	t_3d_vector	coor;

	plt.dx = p1.x - p0.x;
	plt.dy = p1.y - p0.y;
	plt.xi = 1;
	if (plt.dx < 0)
	{
		plt.xi = -1;
		plt.dx *= -1;
	}
	plt.d = (2 * plt.dx) - plt.dy;
	coor.x = p0.x;
	coor.y = p0.y;
	while (coor.y <= p1.y)
	{
		ft_put_pixel(img, coor.x, coor.y, ft_get_grad(p0, p1, coor));
		if (plt.d > 0)
		{
			coor.x += plt.xi;
			plt.d += -2 * plt.dy;
		}
		plt.d += 2 * plt.dx;
		coor.y++;
	}
}

void	ft_plot_line(
	t_3d_vector p0,
	t_3d_vector p1,
	t_img_data *img
)
{
	int	dx;
	int	dy;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	if (abs(dx) > abs(dy))
	{
		if (dx > 0)
			ft_plot_line_low(p0, p1, img);
		else
			ft_plot_line_low(p1, p0, img);
	}
	else
	{
		if (dy > 0)
			ft_plot_line_high(p0, p1, img);
		else
			ft_plot_line_high(p1, p0, img);
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
