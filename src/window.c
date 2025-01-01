/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:35:44 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 19:05:37 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

t_vector3	calc_center_window(void)
{
	t_vector3	center;

	center = ft_new_vec3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0);
	return (center);
}
