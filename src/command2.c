/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:17:26 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/02 12:41:13 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	command_shrink(t_vars *vars)
{
	double	scalar;

	scalar = 0.9;
	scale_height(vars->map, scalar);
	adjust_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_iso(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}

void	command_expand(t_vars *vars)
{
	double	scalar;

	scalar = 1.1;
	scale_height(vars->map, scalar);
	adjust_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_iso(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}

void	command_rotate(t_vars *vars, t_keycode keycode)
{
	t_vector3	shaft;

	shaft = ft_new_vec3(1, 0, 0);
	if (keycode == VK_X)
		shaft = ft_new_vec3(1, 0, 0);
	else if (keycode == VK_Y)
		shaft = ft_new_vec3(0, 1, 0);
	else if (keycode == VK_Z)
		shaft = ft_new_vec3(0, 0, 1);
	rotate_coordinate(vars->map, M_PI / 128, shaft);
	fetch_coordinate(vars->map, ISO);
	adjust_iso_position(vars->map);
	fetch_coordinate(vars->map, CAR);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_iso(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}
