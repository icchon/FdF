/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:21:18 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/02 08:54:47 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init(t_vars *vars)
{
	vars->mlx = mlx_init();
	fresh_image(vars);
	draw_iso(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	hook_functions(vars);
	mlx_loop(vars->mlx);
	return ;
}
