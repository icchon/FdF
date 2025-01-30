/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:17:26 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/31 07:29:32 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	command_shrink(t_vars *vars)
{
	const double	scalar = 0.95;

	if (!vars->can_change_height)
	{
		ft_printf("cannnot change height.Press Space\n");
		return ;
	}
	scale_height(vars->map, scalar);
	adjust_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_axo(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}

void	command_expand(t_vars *vars)
{
	const double	scalar = 1.05;

	if (!vars->can_change_height)
	{
		ft_printf("cannnot change height.Press Space\n");
		return ;
	}
	scale_height(vars->map, scalar);
	adjust_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_axo(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}

void	command_rotate(t_vars *vars, t_keycode keycode)
{
	t_vector3	shaft;
	int			sign;

	sign = 1;
	vars->can_change_height = 0;
	if (vars->on_shift)
		sign *= -1;
	shaft = ft_new_vec3(sign * 1, 0, 0);
	if (keycode == VK_X)
		shaft = ft_new_vec3(sign * 1, 0, 0);
	else if (keycode == VK_Y)
		shaft = ft_new_vec3(0, sign * 1, 0);
	else if (keycode == VK_Z)
		shaft = ft_new_vec3(0, 0, sign * 1);
	rotate_coordinate(vars->map, M_PI / 128, shaft);
	fetch_coordinate(vars->map, AXO);
	adjust_axo_position(vars->map);
	fetch_coordinate(vars->map, CAR);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_axo(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}

int	is_valid_phases(t_phases phases)
{
	const double	val_th = 0.01;

	if (fabs(tan(phases.beta)) > (1 / val_th) || fabs(sin(phases.alpha
				+ phases.beta)) < val_th)
		return (0);
	if (fabs(tan(phases.beta)) < val_th)
		return (0);
	if (fabs(cos(phases.alpha) + (sin(phases.alpha)
				/ tan(phases.beta))) < val_th)
		return (0);
	if (fabs(sin(phases.alpha) + (cos(phases.alpha)
				* tan(phases.beta))) < val_th)
		return (0);
	if (fabs(sin(phases.alpha) + (cos(phases.alpha)
				* tan(phases.beta))) < val_th)
		return (0);
	return (1);
}

void	command_change_phases(t_vars *vars, t_keycode keycode)
{
	const double	dphase = M_PI / 180;
	int				sign;

	sign = 1;
	vars->can_change_height = 0;
	if (vars->on_shift)
		sign *= -1;
	if (keycode == VK_A)
		vars->map.phases.alpha += dphase * sign;
	if (keycode == VK_B)
		vars->map.phases.beta += dphase * sign;
	while (!is_valid_phases(vars->map.phases))
	{
		if (keycode == VK_A)
			vars->map.phases.alpha += dphase * sign;
		if (keycode == VK_B)
			vars->map.phases.beta += dphase * sign;
	}
	fetch_coordinate(vars->map, AXO);
	adjust_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_axo(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return ;
}
