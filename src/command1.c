/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaxobe <kaaxobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:16:49 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/01 17:17:39 by kaaxobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	command_parallel(t_vars *vars, t_keycode code)
{
	t_vector3		shift_vec;
	const double	scalar = 100;

	shift_vec = ft_new_vec3(scalar, 0, 0);
	if (code == VK_LEFT)
		shift_vec = ft_new_vec3(scalar, 0, 0);
	else if (code == VK_UP)
		shift_vec = ft_new_vec3(0, scalar, 0);
	else if (code == VK_RIGHT)
		shift_vec = ft_new_vec3(-1 * scalar, 0, 0);
	else if (code == VK_DOWN)
		shift_vec = ft_new_vec3(0, -1 * scalar, 0);
	translate(vars->map, shift_vec, AXO);
	fetch_coordinate(vars->map, CAR);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_axo(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}

void	command_upscale(t_vars *vars)
{
	const double	scalar = 1.1;

	upscale(vars->map, scalar, AXO);
	fetch_coordinate(vars->map, CAR);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_axo(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}

void	command_downscale(t_vars *vars)
{
	const double	scalar = 0.9;

	upscale(vars->map, scalar, AXO);
	fetch_coordinate(vars->map, CAR);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_axo(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}

void	command_init(t_vars *vars)
{
	vars->on_shift = 0;
	vars->can_change_height = 1;
	vars->map = create_map(vars->map_path);
	ft_printf(CONTROL_MANUAL);
	adjust_axo_position(vars->map);
	adjust_axo_scale(vars->map);
	fetch_coordinate(vars->map, CAR);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_axo(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}

void	command_center(t_vars *vars)
{
	adjust_axo_position(vars->map);
	fetch_coordinate(vars->map, CAR);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_axo(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}
