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
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WINDOW_HEIGHT 540
# define WINDOW_WIDTH 960
# define STEP 1
# define CONTROL_MANUAL                                \
	"\n_____________________________________\n"       \
	"|                                   |\n"         \
	"|           Key Controls            |\n"         \
	"|===================================|\n"         \
	"|  + : Zoom in                      |\n"         \
	"|  - : Zoom out                     |\n"         \
	"|  →,←,↑,↓ : Move view              |\n" \
	"|  Space : Reset view               |\n"         \
	"|  0-9 : Center object              |\n"         \
	"|  h : Adjust height                |\n"         \
	"|  x/y/z : Rotate on axis           |\n"         \
	"|  Mouse : Free rotation            |\n"         \
	"|  a/b   : axometorical angles      |\n"         \
	"|-----------------------------------|\n"         \
	"|  Hold Shift for reverse controls  |\n"         \
	"|___________________________________|\n"

typedef struct s_obj
{
	t_vector3	axo;
	t_vector3	car;
	int			color;
}				t_obj;

typedef struct s_phases
{
	double		alpha;
	double		beta;
	double		gammma;
}				t_phases;

typedef struct s_map
{
	t_obj		**objs;
	t_vector2	map_size;
	t_phases	phases;
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
	int			on_shift;
	int			can_change_height;
	char		*map_path;
}				t_vars;

typedef enum e_keycode
{
	VK_ESCAPE = 65307,
	VK_UP = 65362,
	VK_LEFT = 65361,
	VK_DOWN = 65364,
	VK_RIGHT = 65363,
	VK_SPACE = ' ',
	VK_PLUS = 61,
	VK_MINUS = '-',
	VK_SHIFT = 65505,
	VK_0 = '0',
	VK_1 = '1',
	VK_2 = '2',
	VK_3 = '3',
	VK_4 = '4',
	VK_5 = '5',
	VK_6 = '6',
	VK_7 = '7',
	VK_8 = '8',
	VK_9 = '9',
	VK_X = 'x',
	VK_Y = 'y',
	VK_Z = 'z',
	VK_A = 'a',
	VK_B = 'b',
	VK_C = 'c',
	VK_H = 'h',
}				t_keycode;

typedef enum e_coordinate
{
	CAR,
	AXO,
}				t_coordinate;

void			translate(t_map map, t_vector3 offset, t_coordinate type);
void			upscale(t_map map, double a, t_coordinate type);
void			adjust_axo_scale(t_map map);
void			adjust_axo_position(t_map map);
void			adjust_map(t_map map);
void			fetch_coordinate(t_map map, t_coordinate to_fetch);
void			draw_axo(t_vars *vars);
void			draw_line(t_obj start, t_obj end, t_vars *vars);
void			put_pixel(t_vars *vars, int x, int y, int color);
t_vector3		axomax(t_map map);
t_vector3		axomin(t_map map);
t_vector3		axometoric_transform(t_vector3 pos, t_phases phases);
t_vector3		axometoric_rev_transform(t_vector3 pos, t_phases phases);
t_map			create_map(char *path);
t_vector2		get_map_size(char *path);
t_map			new_map(t_obj **objs, t_vector2 map_size, t_phases phases);
t_map			get_invalid_map(void);
t_vector2		get_invalid_mapsize(void);
int				is_invalid_mapsize(t_vector2 map_size);
t_obj			new_obj(t_vector3 axo, t_vector3 car, int color);
int				ft_count_words(char const *s, char c);
void			free_strs(char **strs);

int				close_window(t_vars *vars);
int				on_key_pressed(int keycode, t_vars *vars);
void			command_parallel(t_vars *vars, t_keycode code);
void			command_upscale(t_vars *vars);
void			command_downscale(t_vars *vars);
void			scale_height(t_map map, double a);
void			rotate_coordinate(t_map map, double phase, t_vector3 shaft);
void			free_objs(t_obj **objs, int n);
t_vector3		carmax(t_map map);
int				on_mouse_moved(int x, int y, t_vars *vars);
int				on_key_released(int keycode, t_vars *vars);
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
void			command_change_phases(t_vars *vars, t_keycode keycode);

#endif
