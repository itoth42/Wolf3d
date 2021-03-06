/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 21:11:15 by itoth             #+#    #+#             */
/*   Updated: 2017/07/03 21:13:03 by itoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "get_next_line.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

# define RADIANS_TO_DEGREES(RADIANS) (RADIANS * 180 / M_PI)
# define DEGREES_TO_RADIANS(RADIANS) (RADIANS * M_PI / 180)
# define WINDOW_WIDTH			1000
# define WINDOW_HEIGHT			1000
# define KEY_ESC            	53
# define KEY_UP_ARROW			126
# define KEY_LEFT_ARROW			123
# define KEY_DOWN_ARROW			125
# define KEY_RIGHT_ARROW		124
# define KEY_COMMA				43
# define KEY_PERIOD				47
# define KEY_Q					12
# define KEY_W					13
# define KEY_E					14
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define DEGREE					DEGREES_TO_RADIANS(1)
# define SCOPE					1
# define VIEW_WIDTH				DEGREES_TO_RADIANS(90)
# define VIEW_HEIGHT			(VIEW_WIDTH * (WINDOW_HEIGHT / WINDOW_WIDTH))
# define VELOCITY				.1
# define ANGULAR_VELOCITY		(DEGREE * 6)
# define WALL_DISTANCE			.1
# define RGB_TO_COLOR(RED, GREEN, BLUE) (RED * 256 * 256 + GREEN * 256 + BLUE)
# define COLOR_RED				RGB_TO_COLOR(255, 0, 0)
# define COLOR_GREEN			RGB_TO_COLOR(0, 255, 0)
# define COLOR_BLUE				RGB_TO_COLOR(0, 0, 255)
# define COLOR_YELLOW			RGB_TO_COLOR(255, 255, 0)
# define COLOR_WHITE			RGB_TO_COLOR(255, 255, 255)
# define COLOR_BLACK			RGB_TO_COLOR(0, 0, 0)
# define POINTS_RIGHT(ANGLE)	((ANGLE) < M_PI_2 || (ANGLE) > M_PI + M_PI_2)
# define POINTS_DOWN(ANGLE)		((ANGLE) > M_PI)
# define DIST(X1, Y1, X2, Y2) (sqrt(pow((X2) - (X1), 2) + pow((Y2) - (Y1), 2)))
# define DISTANCE(X1, Y1, X2, Y2) (DIST((X1), (Y1), (X2), (Y2)))

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_ray
{
	double			distance;
	int				color;
}					t_ray;

typedef struct		s_map
{
	int				**data;
	int				height;
	int				width;
}					t_map;

typedef struct		s_camera
{
	t_point			location;
	double			direction;
}					t_camera;

typedef struct		s_image
{
	void			*mlx_image;
	int				*data;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
}					t_image;

typedef struct		s_environment
{
	void			*mlx;
	void			*window;
	int				window_height;
	int				window_width;
	t_map			*map;
	t_camera		camera;
	t_image			image;
}					t_environment;

void				read_map(t_map *map, char *filename);
void				let_the_fun_begin(t_map *map);
void				setup_camera(t_camera *camera, t_map *map);
int					expose_hook(t_environment *env);
int					key_hook(int keycode, t_environment *env);
void				move_camera(double angle, t_environment *env);
void				rotation(t_environment *env, double delta_angle);
void				draw(t_environment *env);
void				send_ray(t_ray *ray, t_map *map, t_point *location
							, double viewing_angle);
void				normalize_angle(double *angle);

#endif
