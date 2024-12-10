/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:10:53 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/10 12:41:11 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// Includes

# include "libft.h"
# include <fcntl.h>

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

extern char	*g_pname;

// Errors

# define ERROR_BAD_ARG_NUM			"%s%s:\tBad number of argument.\n%s"
# define ERROR_BAD_FILE_NAME		"%s%s:\tIncorrect file name.\n%s"
# define ERROR_OPEN_FILE			"%s%s:\tCould not open %s.\n%s"

// Utils define

# define RET_ERR					1
# define RET_OK						0

# define WIDTH						1024
# define HEIGHT						1024

# ifndef ENDIANESS
#  define ENDIANESS					0
# endif

# ifndef FILE_EXT
#  define FILE_EXT					".fdf"
# endif

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

// Fdf

typedef struct s_fdf
{
	t_map_element	**map;
	double			scale;
	t_camera		camera;
}	t_fdf;

// Functions

// Error handling

void			print_gen_error(
					const char *error
					);

void			print_arged_error(
					const char *error,
					const char *arg
					);

// Color functions

uint32_t		get_color_from_str(
					char *str
					);

uint32_t		rgba_to_uint32_t(
					int r,
					int g,
					int b,
					int a
					);

t_color			rgba_to_color(
					uint32_t rgba
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

// Map elements utils

void			ft_free_2d_map_elements(
					t_map_element ***map
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

t_map_element	**ft_alloc_map_elems_from_3d_array(
					char ***map_strs_elements
					);

t_map_element	**ft_parse_2d_map_element_from_strs(
					char ***map_strs_elements,
					t_map_element **map_elements
					);

t_map_element	**ft_get_map(
					char *file_path
					);

#endif
