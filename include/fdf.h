/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:10:53 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/18 18:33:32 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// Includes

# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>

# define BUFFER_SIZE				10

// Terminal colors

# define TERM_RESET					"\033[0m"
# define TERM_BLACK					"\033[30m"
# define TERM_RED					"\033[31m"
# define TERM_GREEN					"\033[32m"
# define TERM_YELLOW				"\033[33m"
# define TERM_BLUE					"\033[34m"
# define TERM_MAGENTA				"\033[35m"
# define TERM_CYAN					"\033[36m"
# define TERM_WHITE					"\033[37m"

# define TERM_UP					"\033[1A"
# define TERM_CLEAR_LINE			"\033[2K\r"

// Global vars

extern char			*g_pname;

// Errors

# define ERROR_BAD_ARG_NUM			"%s%s:\tBad number of argument.\n%s"
# define ERROR_BAD_FILE_NAME		"%s%s:\tIncorrect file name.\n%s"
# define ERROR_OPEN_FILE			"%s%s:\tCould not open %s.\n%s"
# define ERROR_PARSING_MAP			"%s%s:\tError while parsing map.\n%s"
# define ERROR_INIT_MLX				"%s%s:\tError initializing mlx.\n%s"
# define ERROR_CREATING_WINDOW		"%s%s:\tError creating new mlx window.\n%s"
# define ERROR_CREATING_IMAGE		"%s%s:\tError creating mlx image.\n%s"
// Utils define

# ifndef DEBUG_MODE
#  define DEBUG_MODE				0
# endif

# define RET_ERR					1
# define RET_OK						0

# define WIDTH						1024
# define HEIGHT						1024

# define FDF_MIN_SCALE				2
# define FDF_MAX_SCALE				1000
# define FDF_SCALE_INCREMENT		1
# define CAM_DEG_INCREMENT			.01

// Mouse control

# define MOUSE_OFFSET_DIVISION		32
# define MOUSE_ROT_DIVISION			2

# ifndef ENDIANESS
#  define ENDIANESS					0
# endif

# ifndef FILE_EXT
#  define FILE_EXT					".fdf"
# endif

# define PROJ_MODE_ISO				'I'
# define PROJ_MODE_PARALLEL			'P'
# define PROJ_MODE_ANGULAR			'A'

// Mouse control for hooks

# define MOUSE_LEFT_CLICK			1
# define MOUSE_RIGHT_CLICK			3
# define MOUSE_SCROLL_UP			4
# define MOUSE_SCROLL_DOWN			5

// Structures

// 2D Vector

typedef struct s_2d_vector
{
	int	x;
	int	y;
}	t_2d_vector;

// 3D Vector

typedef struct s_3d_vector
{
	double		x;
	double		y;
	double		z;
	uint32_t	color;
}	t_3d_vector;

// Color

typedef struct s_color
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
}	t_color;

// Matrix

typedef struct s_3d_matrix
{
	t_3d_vector	i;
	t_3d_vector	j;
	t_3d_vector	k;
}	t_3d_matrix;

// Mouse

typedef struct s_mouse
{
	double	prev_x;
	double	prev_y;
	double	x;
	double	y;
	int		left_pressed;
	int		right_pressed;
}	t_mouse;

// Plotter (for plot_line readability)

typedef struct s_plotter
{
	int	dx;
	int	dy;
	int	yi;
	int	xi;
	int	d;
}	t_plotter;

// Map Borders

typedef struct s_map_borders
{
	t_2d_vector	min;
	t_2d_vector	max;
}	t_map_borders;

// Map element

typedef struct s_map_element
{
	int			x;
	int			y;
	int			z;
	int			original_depth;
	uint32_t	color;
	int			is_end;
}	t_map_element;

// Offset

typedef struct s_offset
{
	int	x;
	int	y;
}	t_offset;

// Camera

typedef struct s_camera
{
	t_offset	offset;
	double		x_deg;
	double		y_deg;
	double		z_deg;
	double		fov;
}	t_camera;

// Image data

typedef struct s_img_data
{
	void	*img;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endianess;
	int		line_len;
}	t_img_data;

// Mlx data

typedef struct s_mlx_data
{
	void		*mlx;
	void		*window;
	t_img_data	img_data;
}	t_mlx_data;

// Fdf

typedef struct s_fdf
{
	t_map_element	**map;
	double			scale;
	t_mouse			mouse;
	t_camera		camera;
	t_mlx_data		mlx_data;
	char			projection_mode;
}	t_fdf;

// Projections

typedef t_3d_vector	(*t_ft_proj)(t_3d_vector vector, t_fdf *fdf);

// Functions

// Error handling

void			print_gen_error(
					const char *error
					);

void			print_arged_error(
					const char *error,
					const char *arg
					);

void			print_mlx_error(void);

// Math utils

double			ft_rad(
					double deg
					);

double			ft_calculate_relative_position(
					t_3d_vector start_point,
					t_3d_vector end_point,
					t_3d_vector current_point
					);

// Color functions

uint32_t		ft_get_color_from_str(
					char *str
					);

uint32_t		ft_rgba_to_uint32_t(
					int r,
					int g,
					int b,
					int a
					);

t_color			ft_rgba_to_color(
					uint32_t rgba
					);

// Gradients

uint32_t		ft_grad_pt_color(
					uint32_t a,
					uint32_t b,
					double position
					);

uint32_t		ft_get_grad(
					t_3d_vector start,
					t_3d_vector end,
					t_3d_vector current
					);

// Initializing

int				ft_init_fdf(
					int argc,
					char **argv,
					t_fdf *fdf
					);

// Array utils

size_t			ft_len_2d_array(
					char **array
					);

size_t			ft_len_3d_array(
					char ***array
					);

void			ft_free_2d_array(
					char ***array
					);

void			ft_free_3d_array(
					char ****array
					);

// Map borders

t_map_borders	ft_get_map_borders(
					double s,
					t_fdf *fdf
					);

// Map elements utils

void			ft_free_2d_map_elements(
					t_map_element ***map
					);

// Structure utils

void			free_fdf(
					t_fdf	*fdf
					);

// Vector

t_3d_vector		ft_get_3d_vector(
					t_map_element element
					);

t_3d_vector		ft_multiply_vector_by_matrix(
					t_3d_vector v,
					t_3d_matrix m
					);

t_3d_vector		ft_scale_and_offset(
					t_3d_vector vector,
					t_fdf *fdf,
					t_3d_vector (*t_ft_proj)(t_3d_vector vector, t_fdf *fdf)
					);

t_3d_vector		ft_scale(
					t_3d_vector vector,
					double scale
					);

t_3d_vector		ft_offset(
					t_3d_vector vector,
					t_fdf *fdf,
					t_3d_vector (*t_ft_proj)(t_3d_vector vector, t_fdf *fdf)
					);

// Scaling

t_3d_vector		ft_scale_3d_vector(
					t_3d_vector vector,
					double scale
					);

double			ft_get_scale(
					t_map_borders	map_borders
					);

// Offset

t_offset		ft_get_offset(
					t_map_borders map_borders
					);

// Matrix

t_3d_matrix		ft_get_matrix_x(
					double deg
					);

t_3d_matrix		ft_get_matrix_y(
					double deg
					);

t_3d_matrix		ft_get_matrix_y(
					double deg
					);

t_3d_matrix		ft_get_matrix_i(void);

t_3d_matrix		ft_get_rot_matrix(
					double deg,
					char axis
					);

// File handling

int				ft_validate_file_name(
					char *file_name
					);

// Map parsing

char			**ft_read_map_to_strs(
					const int map_fd
					);

char			***ft_map_strs_to_split(
					char **map_strs
					);

t_map_element	**ft_map_elems_from_3d_array(
					char ***map_strs_elements
					);

t_map_element	**ft_parse_2d_map_element_from_strs(
					char ***map_strs_elements,
					t_map_element **map_elements
					);

t_map_element	**ft_get_map(
					char *file_path
					);

// Hooking

int				ft_hook(
					int keysym,
					t_fdf *data
					);

void			ft_hook_update_camera(
					int keysym,
					t_fdf *fdf
					);

int				ft_mouse_pressed_hook(
					int button,
					int x,
					int y,
					t_fdf *fdf
					);

int				ft_mouse_released_hook(
					int button,
					int x,
					int y,
					t_fdf *fdf
					);

int				ft_mouse_moved_hook(
					int x,
					int y,
					t_fdf *fdf
					);

void			ft_proj(
					t_fdf *fdf
					);

void			ft_start_hook(
					t_fdf *fdf
					);

void			ft_refresh_image(
					t_fdf *fdf
					);

// Mouse utils

void			ft_rotate_mouse(
					int x,
					int y,
					t_fdf *fdf
					);

void			ft_rotate_mouse(
					int x,
					int y,
					t_fdf *fdf
					);

void			ft_translate_mouse(
					int x,
					int y,
					t_fdf *fdf
					);

// Drawing

void			ft_put_pixel(
					t_img_data *img,
					int x,
					int y,
					int color
					);

void			ft_clear_screen(
					t_fdf *fdf
					);

void			ft_draw(
					t_fdf *fdf,
					t_3d_vector (*t_ft_proj)(t_3d_vector vector, t_fdf *fdf)
					);

void			ft_plot_line_low(
					t_3d_vector	p0,
					t_3d_vector	p1,
					t_img_data	*img_data
					);

void			ft_plot_line_high(
					t_3d_vector p0,
					t_3d_vector p1,
					t_img_data	*img_data
					);

void			ft_plot_line(
					t_3d_vector p0,
					t_3d_vector p1,
					t_img_data	*img_data
					);

// Projection

void			ft_project_and_draw(
					t_fdf *fdf,
					char proj_mode
					);

// Orthographic

t_3d_vector		ft_to_iso(
					t_3d_vector vector,
					t_fdf *fdf
					);

// Angular

t_3d_vector		ft_to_angular(
					t_3d_vector vector,
					t_fdf *fdf
					);

// Parallel

t_3d_vector		ft_to_parallel(
					t_3d_vector vector,
					t_fdf *fdf
					);

#endif
