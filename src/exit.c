/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaxobe <kaaxobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:40:52 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/02 10:56:57 by kaaxobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	terminate(t_vars *vars)
{
	free_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_loop_end(vars->mlx);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(EXIT_SUCCESS);
	return ;
}
