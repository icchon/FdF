/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:17:26 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 17:17:33 by kaisobe          ###   ########.fr       */
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
