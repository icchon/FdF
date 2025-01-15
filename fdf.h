/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 09:08:14 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/15 10:50:50 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920
# define STEP 1

typedef struct s_obj
{
	t_vector3	iso;
	t_vector3	cur;
	int			color;
}				t_obj;

typedef struct s_map
{
	t_obj		**objs;
	t_vector2	map_size;
}				t_map;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		map;
	t_vector2	mouse_pos;
	int			on_mouse;
	char		*map_path;
}				t_vars;

typedef enum e_keycode
{
	VK_ESCAPE = 65307,
	VK_UP = 65362,
	VK_LEFT = 65361,
	VK_DOWN = 65364,
	VK_RIGHT = 65363,
	VK_SPACE = 32,
	VK_PLUS = 61,
	VK_MINUS = 45,
	VK_0 = 48,
	VK_1 = 49,
	VK_2 = 50,
	VK_3 = 51,
	VK_4 = 52,
	VK_5 = 53,
	VK_6 = 54,
	VK_7 = 55,
	VK_8 = 56,
	VK_9 = 57,
	VK_X = 120,
	VK_Y = 121,
	VK_Z = 122,
}				t_keycode;

typedef enum e_coordinate
{
	CAR,
	ISO,
}				t_coordinate;

void			translate(t_map map, t_vector3 offset, t_coordinate type);
void			upscale(t_map map, double a, t_coordinate type);
void			adjust_iso_scale(t_map map);
void			adjust_iso_position(t_map map);
void			adjust_map(t_map map);
void			fetch_coordinate(t_map map, t_coordinate to_fetch);
void			draw_iso(t_vars *vars);
void			draw_line(t_obj start, t_obj end, t_vars *vars);
void			put_pixel(t_vars *vars, int x, int y, int color);
t_vector3		isomax(t_map map);
t_vector3		isomin(t_map map);
t_vector3		isometoric_transform(t_vector3 pos);
t_vector3		isometoric_rev_transform(t_vector3 pos);
t_map			create_map(char *path);
t_vector2		get_map_size(char *path);
t_map			new_map(t_obj **objs, t_vector2 map_size);
t_map			get_invalid_map(void);
t_vector2		get_invalid_mapsize(void);
int				is_invalid_mapsize(t_vector2 map_size);
t_obj			new_obj(t_vector3 iso, t_vector3 cur, int color);
int				ft_count_words(char const *s, char c);
void			free_strs(char **strs);

int			close_window(t_vars *vars);
int				on_key_pressed(int keycode, t_vars *vars);
void			command_parallel(t_vars *vars, t_keycode code);
void			command_upscale(t_vars *vars);
void			command_downscale(t_vars *vars);
void			scale_height(t_map map, double a);
void			rotate_coordinate(t_map map, double phase, t_vector3 shaft);
void			free_objs(t_obj **objs, int n);

int				on_mouse_moved(int x, int y, t_vars *vars);
int				on_mouse_released(int button, int x, int y, t_vars *vars);
int				on_mouse_pressed(int button, int x, int y, t_vars *vars);
int				on_key_pressed(int keycode, t_vars *vars);
t_vector3		calc_center_window(void);
void			set_point_info(char *str, int *nbr, int *color);
void			command_init(t_vars *vars);
void			command_center(t_vars *vars);
void			command_shrink(t_vars *vars);
void			command_expand(t_vars *vars);
int				is_valid_map(char *path);
void			fresh_image(t_vars *vars);
void			hook_functions(t_vars *vars);
void			init(t_vars *vars);
void			free_map(t_map map);
void			terminate(t_vars *vars);
void			command_rotate(t_vars *vars, t_keycode keycode);

#endif
