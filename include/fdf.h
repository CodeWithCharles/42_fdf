/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:10:53 by cpoulain          #+#    #+#             */
/*   Updated: 2024/12/20 13:13:44 by cpoulain         ###   ########.fr       */
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

// Informations color

# define INF_COLOR					0x00FFFFFF

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

/**
 * @struct s_2d_vector
 * @brief Represents a 2D vector
 *
 * @example
 * 	t_2d_vector point = {10, 2};
 * 	// Point represent a vector at (10, 2);
 */
typedef struct s_2d_vector
{
	/**
	 * @brief x coordinate of the vector
	 */
	int	x;
	/**
	 * @brief y coordinate of the vector
	 */
	int	y;
}	t_2d_vector;

/**
 * @struct s_3d_vector
 * @brief Represents a 3D vector with optional color
 *
 * @example
 * 	t_3d_vector point = {10, 2, 5, 0x00FF00FF}
 * 	// point represents a vector at (10, 2, 5) with green color.
 */

typedef struct s_3d_vector
{
	/**
	 * @brief x coordinate of the vector
	 */
	double		x;
	/**
	 * @brief y coordinate of the vector
	 */
	double		y;
	/**
	 * @brief z coordinate of the vector
	 */
	double		z;
	/**
	 * @brief (Optional) color of the vector
	 */
	uint32_t	color;
}	t_3d_vector;

/**
 * @struct s_color
 * @brief Represents a color
 *
 * @example
 * 	t_color color = {0, 255, 0, 255}
 * 	// color represents a green color.
 */
typedef struct s_color
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
}	t_color;

/**
 * @struct s_3d_matrix
 * @brief Represents a 3D matrix
 *
 * @example
 * 	t_3d_vector i = {10, 20, 30, 0}
 * 	t_3d_vector j = {2, 6, 8, 0}
 * 	t_3d_vector k = {9, 2, 7, 0}
 * 	t_3d_matrix matrix = {i, j, k}
 * 	// Matrix represent this matrix :
 * 	//	{10, 20, 30}
 * 	//	{2 , 6 , 8 }
 * 	//	{9 , 2 , 7 }
 */
typedef struct s_3d_matrix
{
	/**
	 * @brief Matrix's first vector
	 */
	t_3d_vector	i;
	/**
	 * @brief Matrix's second vector
	 */
	t_3d_vector	j;
	/**
	 * @brief Matrix's third vector
	 */
	t_3d_vector	k;
}	t_3d_matrix;

/**
 * @struct s_mouse
 * @brief Represents the state of the mouse
 */
typedef struct s_mouse
{
	/**
	 * @brief Previous mouse x position
	 */
	double	prev_x;
	/**
	 * @brief Previous mouse y position
	 */
	double	prev_y;
	/**
	 * @brief Current mouse x position
	 */
	double	x;
	/**
	 * @brief Current mouse y position
	 */
	double	y;
	/**
	 * @brief Is left button pressed
	 */
	int		left_pressed;
	/**
	 * @brief Is right button pressed
	 */
	int		right_pressed;
}	t_mouse;

/**
 * @struct s_plotter
 * @brief Plotter's state for line drawing using Bresenham's algorithm.
 *
 * This structure holds the necessary information for plotting a line between
 * two points using Bresenham's line algorithm, including the step increments
 * for both axes and the decision coefficient for the algorithm.
 */
typedef struct s_plotter
{
	/**
	 * @brief The difference in the X direction between the two points (Δx).
	 */
	int	dx;
	/**
	 * @brief The difference in the Y direction between the two points (Δy).
	 */
	int	dy;
	/**
	 * @brief The initial value of Y at the starting point.
	 */
	int	yi;
	/**
	 * @brief The initial value of X at the starting point.
	 */
	int	xi;
	/**
	 * @brief The Bresenham decision coefficient.
	 */
	int	d;
}	t_plotter;

/**
 * @struct s_map_borders
 * @brief Represents max borders using 2d_vectors
 */
typedef struct s_map_borders
{
	/**
	 * @brief Top left boundaries
	 */
	t_2d_vector	min;
	/**
	 * @brief Bottom right boundaries
	 */
	t_2d_vector	max;
}	t_map_borders;

/**
 * @struct s_map_element
 * @brief Represents an element in a map with its position, depth, color,
 * and a flag for the end point.
 */
typedef struct s_map_element
{
	/**
	 * @brief x coordinate of the map element
	 */
	int			x;
	/**
	 * @brief y coordinate of the map element
	 */
	int			y;
	/**
	 * @brief z coordinate of the map element
	 */
	int			z;
	/**
	 * @brief Depth of the map element
	 */
	int			original_depth;
	/**
	 * @brief Color of the map element
	 */
	uint32_t	color;
	/**
	 * @brief Is it the final element of the row
	 */
	int			is_end;
}	t_map_element;

/**
 * @struct s_offset
 * @brief Represents an x, y offset
 */
typedef struct s_offset
{
	/**
	 * @brief x offset
	 */
	int	x;
	/**
	 * @brief y offset
	 */
	int	y;
}	t_offset;

/**
 * @struct s_camera
 * @brief Represents a camera with position, orientation, and field of view.
 */
typedef struct s_camera
{
	/**
	 * @brief The camera's offset from the reference point (0, 0)
	 */
	t_offset	offset;
	/**
	 * @brief The X-axis rotation angle of the camera in rad
	 */
	double		x_deg;
	/**
	 * @brief The Y-axis rotation angle of the camera in rad
	 */
	double		y_deg;
	/**
	 * @brief The Z-axis rotation angle of the camera in degrees
	 */
	double		z_deg;
	/**
	 * @brief The field of view of the camera.
	 *
	 * In our case, fov is not a good term, because it represents the depth.
	 */
	double		fov;
}	t_camera;

/**
 * @struct s_img_data
 * @brief Represents image data of the minilibx
 */
typedef struct s_img_data
{
	void	*img;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endianess;
	int		line_len;
}	t_img_data;

/**
 * @struct s_mlx_data
 * @brief Hold the mlx, window and img_data from the minilibx
 */
typedef struct s_mlx_data
{
	void		*mlx;
	void		*window;
	t_img_data	img_data;
}	t_mlx_data;

/**
 * @struct s_fdf
 * @brief Represents the data structure for the FdF project (Fil de Fer)
 * including map, transformations, and rendering details.
 */
typedef struct s_fdf
{
	/**
	 * @brief A 2D array of map element representing the map.
	 */
	t_map_element	**map;
	/**
	 * @brief The scale of the model to output
	 */
	double			scale;
	/**
	 * @brief The mouse state and position used for interation
	 */
	t_mouse			mouse;
	/**
	 * @brief The camera settings and state, position and orientation
	 */
	t_camera		camera;
	/**
	 * @brief The minilibx data used to render the map
	 */
	t_mlx_data		mlx_data;
	/**
	 * @brief The projection mode :
	 * 'I' : Isometric
	 * 'P' : Parallel
	 * 'A' : Angular
	 */
	char			projection_mode;
}	t_fdf;

/**
 * @brief Typedef for Isometric, Parallel and Angular functions
 */
typedef t_3d_vector	(*t_ft_proj)(t_3d_vector vector, t_fdf *fdf);

// Functions

/**
 * @brief Prints a generic error in red
 *
 * @param error The error to print
 */
void			print_gen_error(
					const char *error
					);

/**
 * @brief Prints an error in red with a parameter
 *
 * @param error The error to print
 * @param arg The parameter to print
 */
void			print_arged_error(
					const char *error,
					const char *arg
					);

/**
 * @brief My mlx_string_put (see mlx_string_put from minilibx)
 *
 * @param fdf The fdf structure
 * @param coor The coordinates of the string
 * @param color Color of the string
 * @param str String to print
 */
void			ft_mlx_string_put(
					t_fdf *fdf,
					t_2d_vector coor,
					uint32_t color,
					char *str
					);

/**
 * @brief Prints camera informations
 *
 * @param fdf The fdf structure
 */
void			ft_info_cam(
					t_fdf *fdf
					);

/**
 * @brief Prints the informations of the camera using ft_info_cam
 * as well as the scale and projection_mode
 *
 * @param fdf The fdf structure
 */
void			ft_info(
					t_fdf *fdf
					);

// Math utils

/**
 * @brief Converts degrees to radiant
 *
 * @param deg The angle to convert
 * @return double The angle converted to radiants
 */
double			ft_rad(
					double deg
					);

/**
 * @brief Calculate the relative distance between a start vector, an end vector
 * and our current vector
 *
 * @param start_point The starting point
 * @param end_point The end point
 * @param current_point Our current point
 * @return double The relative distance
 */
double			ft_calculate_relative_position(
					t_3d_vector start_point,
					t_3d_vector end_point,
					t_3d_vector current_point
					);

// Color functions

/**
 * @brief Convert a string holding a color like "0xABD2C4" to an uint32_t
 *
 * @param str The string to convert
 * @return uint32_t The color value in RGBA
 */
uint32_t		ft_get_color_from_str(
					char *str
					);

/**
 * @brief Merge RGBA values to a single uint32_t color
 *
 * @param r The red value
 * @param g The green value
 * @param b The blue value
 * @param a The alpha value (opacity)
 * @return uint32_t The color
 */
uint32_t		ft_rgba_to_uint32_t(
					int r,
					int g,
					int b,
					int a
					);

/**
 * @brief Converts a uint32_t value holding a color to a t_color object.
 *
 * @param rgba The color
 * @return t_color The structure holding RGBA color
 */
t_color			ft_rgba_to_color(
					uint32_t rgba
					);

// Gradients

/**
 * @brief Given two uint32_t and a position, computes the current color
 *
 * @param a The starting color
 * @param b The end color
 * @param position The current position of our point
 * @return uint32_t The color for the current position
 */
uint32_t		ft_grad_pt_color(
					uint32_t a,
					uint32_t b,
					double position
					);

/**
 * @brief Given a starting vector, an end vector and our current vector
 * computes the color of the current vector using its relative position
 * to start and end and their respective colors
 *
 * @param start The starting vector
 * @param end The end vector
 * @param current Our current vector / position
 * @return uint32_t The computed color
 */
uint32_t		ft_get_grad(
					t_3d_vector start,
					t_3d_vector end,
					t_3d_vector current
					);

/**
 * @brief Inits the fdf structure, parsing the map, and setting up the minilibx
 *
 * @param argc Arg count
 * @param argv Arguments
 * @param fdf The fdf structure
 * @return int Return status
 */
int				ft_init_fdf(
					int argc,
					char **argv,
					t_fdf *fdf
					);

// Array utils

/**
 * @brief Gets the size of a 2d array
 *
 * @param array The array
 * @return size_t The size of the 2d array
 */
size_t			ft_len_2d_array(
					char **array
					);

/**
 * @brief Gets the size of a 3d array
 *
 * @param array The array
 * @return size_t The size of the 3d array
 */
size_t			ft_len_3d_array(
					char ***array
					);

/**
 * @brief Frees a 2d array
 *
 * @param array The array to free
 */
void			ft_free_2d_array(
					char ***array
					);

/**
 * @brief Frees a 3d array
 *
 * @param array The array to free
 */
void			ft_free_3d_array(
					char ****array
					);

// Map borders

/**
 * @brief Retrieve the map borders from the fdf's structure map
 *
 * @param s The current scale
 * @param fdf The fdf structure
 * @return t_map_borders The map borders
 */
t_map_borders	ft_get_map_borders(
					double s,
					t_fdf *fdf
					);

// Map elements utils

/**
 * @brief Frees a 2d array of map_element by reference
 *
 * @param map The map by reference
 */
void			ft_free_2d_map_elements(
					t_map_element ***map
					);

// Structure utils

/**
 * @brief Frees the fdf structure
 *
 * @param fdf The fdf structure
 */
void			free_fdf(
					t_fdf	*fdf
					);

// Vector

/**
 * @brief Gets a 3d_vector from the map element
 *
 * @param element The map_element
 * @return t_3d_vector The 3d vector associated to the map element
 */
t_3d_vector		ft_get_3d_vector(
					t_map_element element
					);

/**
 * @brief Multiplies a 3d vector by a matrix
 *
 * @param v The 3d vector
 * @param m The 3d matrix
 * @return t_3d_vector The resulting 3d vector
 */
t_3d_vector		ft_multiply_vector_by_matrix(
					t_3d_vector v,
					t_3d_matrix m
					);

/**
 * @brief Scale and offset a 3d_vector
 *
 * @param vector The 3d_vector
 * @param fdf The fdf structure
 * @param t_ft_proj The function corresponding to the current projection mode
 * @return t_3d_vector The resulting 3d vector
 */
t_3d_vector		ft_scale_and_offset(
					t_3d_vector vector,
					t_fdf *fdf,
					t_3d_vector (*t_ft_proj)(t_3d_vector vector, t_fdf *fdf)
					);

/**
 * @brief Scales a 3d vector
 *
 * @param vector The 3d vector
 * @param scale The scale
 * @return t_3d_vector The resulting 3d vector
 */
t_3d_vector		ft_scale(
					t_3d_vector vector,
					double scale
					);

/**
 * @brief Offsets a 3d vector using the function matching the projection_mode
 *
 * @param vector The 3d vector to offset
 * @param fdf The fdf structure
 * @param t_ft_proj The projection function
 * @return t_3d_vector The resulting 3d vector
 */
t_3d_vector		ft_offset(
					t_3d_vector vector,
					t_fdf *fdf,
					t_3d_vector (*t_ft_proj)(t_3d_vector vector, t_fdf *fdf)
					);

// Scaling

/**
 * @brief Computes the scale of the project given the map borders
 *
 * @param map_borders The map borders
 * @return double The resulting scale
 */
double			ft_get_scale(
					t_map_borders	map_borders
					);

// Offset

/**
 * @brief Computes the original camera's offset using map borders
 *
 * @param map_borders The map borders
 * @return t_offset The resulting offset
 */
t_offset		ft_get_offset(
					t_map_borders map_borders
					);

// Matrix

/**
 * @brief Gets the rotation X-axis rotation matrix for a specific angle
 *
 * @param deg The angle
 * @return t_3d_matrix The resulting matrix
 */
t_3d_matrix		ft_get_matrix_x(
					double deg
					);

/**
 * @brief Gets the rotation Y-axis rotation matrix for a specific angle
 *
 * @param deg The angle
 * @return t_3d_matrix The resulting matrix
 */
t_3d_matrix		ft_get_matrix_y(
					double deg
					);

/**
 * @brief Gets the rotation Z-axis rotation matrix for a specific angle
 *
 * @param deg The angle
 * @return t_3d_matrix The resulting matrix
 */
t_3d_matrix		ft_get_matrix_z(
					double deg
					);

/**
 * @brief Gets the 3d identity matrix
 *
 * @return t_3d_matrix The identity matrix
 */
t_3d_matrix		ft_get_matrix_i(void);

/**
 * @brief Gets a rotation matrix for a specific angle and axis
 * if axis is different than x, y or z, then returns 3d identity matrix
 *
 * @param deg The angle
 * @param axis The axis (x, y, z, or null for identity matrix)
 * @return t_3d_matrix The 3d matrix
 */
t_3d_matrix		ft_get_rot_matrix(
					double deg,
					char axis
					);

// File handling

/**
 * @brief Validate the file name using the defined extension
 *
 * @param file_name The filename
 * @return int 0 if invalid, 1 if valid
 */
int				ft_validate_file_name(
					char *file_name
					);

// Map parsing

/**
 * @brief Reads a .fdf map using its file descriptor
 *
 * @param map_fd The file descriptor
 * @return char** The map in a 2d array
 */
char			**ft_read_map_to_strs(
					const int map_fd
					);

/**
 * @brief Splits a 2d map char ** to a 2d map containing arrays representing
 * the elevation at index 0 and the color if there's on at index 1
 *
 * @param map_strs The 2d map
 * @return char*** The resulting 2d map
 */
char			***ft_map_strs_to_split(
					char **map_strs
					);

/**
 * @brief This function is in charge of allocating the 2d array of t_map_element
 * using a 3d array, likely returned by ft_map_strs_to_split
 *
 * @param map_strs_elements The map in string format
 * @return t_map_element** The allocated 2d array
 */
t_map_element	**ft_map_elems_from_3d_array(
					char ***map_strs_elements
					);

/**
 * @brief Parses 3d map array to a 2d array of map_element
 *
 * @param map_strs_elements The elements in string
 * @param map_elements The allocated 2d array
 * @return t_map_element** The 2d array
 */
t_map_element	**ft_parse_2d_map_element_from_strs(
					char ***map_strs_elements,
					t_map_element **map_elements
					);

/**
 * @brief Parse the map from the file path
 *
 * @param file_path The path to the file containing the map
 * @return t_map_element** The map
 */
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

int				ft_close_window_hook(
					t_fdf *fdf
					);

/**
 * @brief Handles projection depending on fdf->projection_mode
 *
 * @param fdf The fdf structure
 */
void			ft_proj(
					t_fdf *fdf
					);

void			ft_start_hook(
					t_fdf *fdf
					);

/**
 * @brief Refresh the minilibx image
 *
 * @param fdf The fdf structure
 */
void			ft_refresh_image(
					t_fdf *fdf
					);

void			ft_rotate_camera_hook(
					int keysym,
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

/**
 * @brief Puts a pixel using its x, y coordinates and color
 *
 * @param img The minilibx image data
 * @param x The x coordinate
 * @param y The y coordinate
 * @param color The color
 */
void			ft_put_pixel(
					t_img_data *img,
					int x,
					int y,
					int color
					);

/**
 * @brief Clears the screen with black pixels
 *
 * @param fdf The fdf structure
 */
void			ft_clear_screen(
					t_fdf *fdf
					);

/**
 * @brief Draws the map using the correct projecion function
 *
 * @param fdf The fdf structure holding the map
 * @param t_ft_proj The projection function
 */
void			ft_draw(
					t_fdf *fdf,
					t_3d_vector (*t_ft_proj)(t_3d_vector vector, t_fdf *fdf)
					);

/**
 * @brief Plots a descending line to the screen
 *
 * @param p0 The starting point
 * @param p1 The end point
 * @param img_data The minilibx image data
 */
void			ft_plot_line_low(
					t_3d_vector	p0,
					t_3d_vector	p1,
					t_img_data	*img_data
					);

/**
 * @brief Plots an ascending line to the screen
 *
 * @param p0 The starting point
 * @param p1 The end point
 * @param img_data The minilibx image data
 */
void			ft_plot_line_high(
					t_3d_vector p0,
					t_3d_vector p1,
					t_img_data	*img_data
					);

/**
 * @brief Plots a line to the screen.
 * Will decide which function to call between ft_plot_line_low or
 * ft_plot_line_high.
 *
 * @param p0 The starting point
 * @param p1 The end point
 * @param img_data The minilibx image data
 */
void			ft_plot_line(
					t_3d_vector p0,
					t_3d_vector p1,
					t_img_data	*img_data
					);

// Projection

/**
 * @brief Will call ft_draw, passing it the correct projection function
 * given the projection mode
 *
 * @param fdf The fdf structure
 * @param proj_mode The projection mode
 */
void			ft_project_and_draw(
					t_fdf *fdf,
					char proj_mode
					);

/**
 * @brief Returns a 3d vector to its isometric projection depending on the
 * camera state
 *
 * @param vector The 3d vector
 * @param fdf The fdf structure holding the camera state
 * @return t_3d_vector The resulting 3d vector to the isometric projection
 */
t_3d_vector		ft_to_iso(
					t_3d_vector vector,
					t_fdf *fdf
					);

/**
 * @brief Returns a 3d vector to its angular projection depending on the
 * camera state
 *
 * @param vector The 3d vector
 * @param fdf The fdf structure holding the camera state
 * @return t_3d_vector The resulting 3d vector to the angular projection
 */
t_3d_vector		ft_to_angular(
					t_3d_vector vector,
					t_fdf *fdf
					);

/**
 * @brief Returns a 3d vector to its parallel projection depending on the
 * camera state
 *
 * @param vector The 3d vector
 * @param fdf The fdf structure holding the camera state
 * @return t_3d_vector The resulting 3d vector to the parallel projection
 */
t_3d_vector		ft_to_parallel(
					t_3d_vector vector,
					t_fdf *fdf
					);

#endif
