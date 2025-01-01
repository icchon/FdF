/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:15:57 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 19:47:49 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_key_pressed(int keycode, t_vars *vars)
{
	if (keycode == VK_ESCAPE)
		close_window(vars);
	else if (ft_ismatch(keycode, 4, VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN))
		command_parallel(vars, keycode);
	else if (keycode == VK_PLUS)
		command_upscale(vars);
	else if (keycode == VK_MINUS)
		command_downscale(vars);
	else if (keycode == VK_SPACE)
		command_init(vars);
	else if (ft_ismatch(keycode, 8, VK_3, VK_4, VK_5, VK_6, VK_7, VK_8, VK_9,
			VK_0))
		command_center(vars);
	else if (keycode == VK_1)
		command_shrink(vars);
	else if (keycode == VK_2)
		command_expand(vars);
	return (0);
}

int	on_mouse_pressed(int button, int x, int y, t_vars *vars)
{
	(void)vars;
	(void)button;
	vars->on_mouse = 1;
	vars->mouse_pos = ft_new_vec2(x, y);
	mlx_mouse_move(vars->mlx, vars->win, x, y);
	return (1);
}

int	on_mouse_released(int button, int x, int y, t_vars *vars)
{
	(void)vars;
	(void)button;
	(void)x;
	(void)y;
	vars->on_mouse = 0;
	return (1);
}

int	on_mouse_moved(int x, int y, t_vars *vars)
{
	t_vector2		sub;
	const double	th = 10;
	t_vector3		shaft;

	if (!vars->on_mouse)
		return (0);
	sub = ft_sub_vec2(ft_new_vec2(x, y), vars->mouse_pos);
	if (ft_norm_vec2(sub) > th)
	{
		vars->mouse_pos = ft_new_vec2(x, y);
		shaft = ft_new_vec3(sub.x, sub.y, 0);
		shaft = isometoric_rev_transform(shaft);
		shaft = ft_cross_vec3(shaft, ft_new_vec3(1, 1, 1));
		rotate_coordinate(vars->map, M_PI / 128, shaft);
		fetch_coordinate(vars->map, ISO);
		adjust_iso_position(vars->map);
		fetch_coordinate(vars->map, CAR);
		mlx_destroy_image(vars->mlx, vars->img);
		vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		draw_iso(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	}
	return (1);
}
