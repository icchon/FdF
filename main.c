/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 09:07:46 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 19:58:46 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2)
	{
		return (0);
	}
	if (is_invalid_map(vars.map))
	{
		ft_printf("map is invalid\n");
		return (0);
	}
	vars.map_path = argv[1];
	vars.on_mouse = 0;
	vars.map = create_map(vars.map_path);
	adjust_map(vars.map);
	printf("create map\n");
	init(&vars);
	draw_iso(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_hook(vars.win, KeyPress, KeyPressMask, on_key_pressed, &vars);
	mlx_hook(vars.win, ButtonPress, ButtonPressMask, on_mouse_pressed, &vars);
	mlx_hook(vars.win, ButtonRelease, ButtonReleaseMask, on_mouse_released,
		&vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, on_mouse_moved, &vars);
	mlx_loop(vars.mlx);
	return (1);
}
