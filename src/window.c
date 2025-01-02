/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:35:44 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/02 14:01:14 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_vars *vars)
{
	terminate(vars);
	return (1);
}

t_vector3	calc_center_window(void)
{
	t_vector3	center;

	center = ft_new_vec3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0);
	return (center);
}

void	fresh_image(t_vars *vars)
{
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
	return ;
}

void	hook_functions(t_vars *vars)
{
	mlx_hook(vars->win, KeyPress, KeyPressMask, on_key_pressed, vars);
	mlx_hook(vars->win, ButtonPress, ButtonPressMask, on_mouse_pressed, vars);
	mlx_hook(vars->win, ButtonRelease, ButtonReleaseMask, on_mouse_released,
		vars);
	mlx_hook(vars->win, MotionNotify, PointerMotionMask, on_mouse_moved, vars);
	mlx_hook(vars->win, DestroyNotify, StructureNotifyMask, close_window, vars);
	return ;
}
