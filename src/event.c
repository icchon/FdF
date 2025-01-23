/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaxobe <kaaxobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:15:57 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/02 13:33:28 by kaaxobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_key_pressed(int keycode, t_vars *vars)
{
	if (keycode == VK_ESCAPE)
		close_window(vars);
	if (ft_ismatch(keycode, 4, VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN))
		command_parallel(vars, keycode);
	if (keycode == VK_PLUS)
		command_upscale(vars);
	if (keycode == VK_MINUS || (keycode == VK_PLUS && vars->on_shift))
		command_downscale(vars);
	if (keycode == VK_SPACE)
		command_init(vars);
	if (VK_0 <= keycode && keycode <= VK_9)
		command_center(vars);
	if (keycode == VK_H && !vars->on_shift)
		command_expand(vars);
	if (keycode == VK_H && vars->on_shift)
		command_shrink(vars);
	if (ft_ismatch(keycode, 3, VK_X, VK_Y, VK_Z))
		command_rotate(vars, keycode);
	if (ft_ismatch(keycode, 3, VK_A, VK_B, VK_C))
		command_change_phases(vars, keycode);
	if (keycode == VK_SHIFT)
		vars->on_shift = 1;
	return (0);
}

int	on_key_released(int keycode, t_vars *vars)
{
	if (keycode == VK_SHIFT)
		vars->on_shift = 0;
	return (1);
}

int	on_mouse_pressed(int button, int x, int y, t_vars *vars)
{
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
		shaft = axometoric_rev_transform(shaft, vars->map.phases);
		shaft = ft_cross_vec3(ft_new_vec3(1, 1, 1), shaft);
		rotate_coordinate(vars->map, M_PI / 128, shaft);
		fetch_coordinate(vars->map, AXO);
		adjust_axo_position(vars->map);
		fetch_coordinate(vars->map, CAR);
		mlx_destroy_image(vars->mlx, vars->img);
		vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		draw_axo(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
		vars->can_change_height = 0;
	}
	return (1);
}
